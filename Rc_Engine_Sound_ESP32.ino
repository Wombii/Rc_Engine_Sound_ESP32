/* RC engine sound simulator for Arduino ESP32. Based on the code for ATmega 328: https://github.com/TheDIYGuy999/Rc_Engine_Sound

 *  ***** ESP32 CPU frequency must be set to 240MHz! *****

   Sound files converted with: https://bitluni.net/wp-content/uploads/2018/01/Audio2Header.html
   converter code by bitluni (send him a high five, if you like the code)

*/

/*
 * Butchered by Wombii to accept SBUS and a simpler Serial as input.
 * Changed sound setup to use 2 siren sounds instead of indicators
 * Completely changed sound triggering
 * Moved soundfiles to subfolder
 * Rearranged functions to separate files
 * Added a sound for applying brakes
 * Disabled LED and shaker
 * SBUS preparechannels function based on methods from SBUS library from https://github.com/mikeshub/FUTABA_SBUS
 */

//version = 2.4 - W-SBUS-2Siren-BEFORECLEANUP1
//const float codeVersion = 2.4 with escpulse int fix from 2.5; // Software revision.

//
// =======================================================================================================
// SETTINGS (ADJUST THEM BEFORE CODE UPLOAD)
// =======================================================================================================
//

// All the required vehicle specific settings are done in Adjustments.h!
#include "Adjustments.h" // <<------- ADJUSTMENTS TAB

#include "AAglobals.h"

// DEBUG options can slow down the playback loop! Only comment them out for debugging
//#define DEBUG // uncomment it for general debugging informations
//#define SERIAL_DEBUG // uncomment it to debug the serial command interface on pin 36
//#define DRIVE_STATE_DEBUG // uncomment it to debug the drive state statemachine

// TODO = Things to clean up!

//
// =======================================================================================================
// LIRBARIES & HEADER FILES (TABS ABOVE)
// =======================================================================================================
//

#include "curves.h" // load nonlinear throttle curve arrays
//#include <statusLED.h> // https://github.com/TheDIYGuy999/statusLED <<------- Install the newest version!



//
// =======================================================================================================
// PIN ASSIGNMENTS & GLOBAL VARIABLES (Do not play around here)
// =======================================================================================================
//
// Pin assignment and wiring instructions

// ------------------------------------------------------------------------------------
// Use a 330Ohm resistor in series with all I/O pins! allows to drive LED directly and
// provides short circuit protection. Also works on the serial Rx pin "VP" (36)
// ------------------------------------------------------------------------------------



// Serial command pins (active, if "SERIAL_COMMUNICATION" in Adjustments.h is not commented out)
// see "sendSerialCommands()" in Micro RC Receiver code: https://github.com/TheDIYGuy999/Micro_RC_Receiver
// This is still experimental! It works, but the sound quality is not perfect.
#define COMMAND_RX 36 // pin 36, labelled with "VP", connect it to "Micro RC Receiver" pin "TXO"
#define COMMAND_TX 39 // pin 39, labelled with "VN", only used as a dummy, not connected

// PPM signal pin (multiple channel input with only one wire)
#define PPM_PIN 34

// RC signal pins (active, if "SERIAL_COMMUNICATION" is commented out)
// Channel numbers may be different on your recveiver!
#define SERVO1_PIN 14//13 // connect to RC receiver servo output channel 1 (aileron, steering)
#define SERVO2_PIN 12 // connect to RC receiver servo output channel 2 (elevator, 3 pos. switch)
#define SERVO3_PIN 13//14 // connect to RC receiver servo output channel 3 (throttle)
#define SERVO4_PIN 27 // connect to RC receiver servo output channel 4 (rudder, pot)

//#define ESC_OUT_PIN 33 // connect crawler  ESC here (experimental, use it at your own risk!)

//#define HEADLIGHT_PIN 0 // White headllights
//#define TAILLIGHT_PIN 15 // Red tail- & brake-lights
//#define INDICATOR_LEFT_PIN 2 // Orange left indicator (turn signal) light
//#define INDICATOR_RIGHT_PIN 4 // Orange right indicator (turn signal) light
//#define FOGLIGHT_PIN 16 // (RX2) Fog lights
//#define REVERSING_LIGHT_PIN 17 // (TX2) White reversing light
//#define ROOFLIGHT_PIN 5 // Roof lights
//#define SIDELIGHT_PIN 18 // Side lights

//#define BEACON_LIGHT2_PIN 19 // Blue beacons light
//#define BEACON_LIGHT1_PIN 21 // Blue beacons light

//#define SHAKER_MOTOR_PIN 23 // Shaker motor (shaking truck while idling)

#define DAC1 25 // connect pin25 (do not change the pin) to a 10kOhm resistor
#define DAC2 26 // connect pin26 (do not change the pin) to a 10kOhm resistor
// both outputs of the resistors above are connected together and then to the outer leg of a
// 10kOhm potentiometer. The other outer leg connects to GND. The middle leg connects to both inputs
// of a PAM8403 amplifier and allows to adjust the volume. This way, two speakers can be used.
/*
// Status LED objects (also used for PWM shaker motor and ESC control)
statusLED headLight(false); // "false" = output not inversed
statusLED tailLight(false);
statusLED indicatorL(false);
statusLED indicatorR(false);
statusLED fogLight(false);
statusLED reversingLight(false);
statusLED roofLight(false);
statusLED sideLight(false);
statusLED beaconLight1(false);
statusLED beaconLight2(false);
statusLED shakerMotor(false);
statusLED escOut(false);
*/


// Define global variables


boolean serialInit = false;

volatile boolean failSafe = false;              // Triggered in emergency situations like: serial signal lost etc.
volatile int8_t ppmFailsafeCounter = 0;

volatile uint8_t engineState = 0; // 0 = off, 1 = starting, 2 = running, 3 = stopping

volatile uint8_t soundNo = 0; // 0 = horn, 1 = siren, 2 = sound1

volatile boolean engineOn = false;              // Signal for engine on / off
volatile boolean engineStart = false;           // Active, if engine is starting up
volatile boolean engineRunning = false;         // Active, if engine is running
volatile boolean engineStop = false;            // Active, if engine is shutting down
volatile boolean hornOn = false;                // Signal for horn on / off
volatile boolean sirenOn = false;               // Signal for siren  on / off
volatile boolean sound1On = false;              // Signal for sound1  on / off
volatile boolean reversingSoundOn = false;      // active during backing up TODO
volatile boolean indicatorSoundOn = false;      // active, if indicator bulb is on

volatile boolean lightsOn = false;              // Lights on

volatile boolean airBrakeTrigger = false;       // Trigger for air brake noise
volatile boolean airPuffTrigger = false; 
volatile boolean EngineWasAboveIdle = false;    // Engine RPM was above idle
//volatile boolean slowingDown = false;           // Engine is slowing down TODO

volatile boolean escIsBraking = false;          // ESC is in a braking state
volatile boolean escInReverse = false;          // ESC is driving or braking backwards
int8_t driveState = 0;                          // for ESC state machine

volatile boolean hornSwitch = false;            // Switch state for horn triggering
volatile boolean sirenSwitch = false;           // Switch state for siren triggering
volatile boolean sound1Switch = false;          // Switch state for sound1 triggering

boolean indicatorLon = false;                   // Left indicator
boolean indicatorRon = false;                   // Right indicator

uint32_t currentThrottle = 0;                   // 0 - 500
boolean throttleReverse;                        // false = forward, true = reverse
uint32_t pulseWidth[4];                         // Current RC signal pulse width [0] = steering, [1] = 3p. switch, [2] = throttle, [4] = pot

uint16_t pulseMaxNeutral[4];                    // PWM input signal configuration storage variables
uint16_t pulseMinNeutral[4];
uint16_t pulseMax[4];
uint16_t pulseMin[4];
uint16_t pulseMaxLimit[4];
uint16_t pulseMinLimit[4];

int16_t escPulseMax;                           // ESC calibration variables
int16_t escPulseMin;

volatile boolean pulseAvailable;                // RC signal pulses are coming in

uint16_t pulseZero[4] = {1500,1500,1500,1500};                           // Usually 1500 (range 1000 - 2000us) Autocalibration active, if "engineManualOnOff" = "false"
uint16_t pulseLimit = 700; // pulseZero +/- this value (700)

int32_t axis1;                                  // Temporary variables for serial command parsing (for signals from "Micro RC" receiver)
int32_t axis2;                                  // See: https://github.com/TheDIYGuy999/Micro_RC_Receiver
int32_t axis3;
int32_t axis4;
int32_t pot1;
boolean mode1;
boolean mode2;
boolean momentary1;
boolean hazard;
boolean left;
boolean right;



const int32_t maxRpm = 500;                     // always 500
const int32_t minRpm = 0;                       // always 0
int32_t currentRpm = 0;                         // 0 - 500 (signed required!)
volatile uint32_t currentRpmScaled = 0;
volatile uint8_t throttleDependentVolume = 0;   // engine volume according to throttle position
volatile uint8_t throttleDependentTurboVolume = 0;   // turbo volume according to throttle position

// Our main tasks
TaskHandle_t Task1;

// Loop time (for debug)
uint16_t loopTime;

// PPM signal processing variables
volatile int valuesInt[NUM_OF_CHL + 1] = {0}; // Input values
volatile int valuesBuf[NUM_OF_CHL + 1] = {0}; // Buffered values
volatile byte counter = NUM_OF_CHL;
volatile byte average  = NUM_OF_AVG;
volatile boolean ready = false;
volatile unsigned long timelast;
unsigned long timelastloop;

// Sampling intervals for interrupt timer (adjusted according to your sound file sampling rate)
uint32_t maxSampleInterval = 4000000 / sampleRate;
uint32_t minSampleInterval = 4000000 / sampleRate / TOP_SPEED_MULTIPLIER;

// Interrupt timer for variable sample rate playback (engine sound)
hw_timer_t * variableTimer = NULL;
portMUX_TYPE variableTimerMux = portMUX_INITIALIZER_UNLOCKED;
volatile uint32_t variableTimerTicks = maxSampleInterval;

// Interrupt timer for fixed sample rate playback (horn etc., playing in parallel with engine sound)
hw_timer_t * fixedTimer = NULL;
portMUX_TYPE fixedTimerMux = portMUX_INITIALIZER_UNLOCKED;
volatile uint32_t fixedTimerTicks = maxSampleInterval;


//
// =======================================================================================================
// INTERRUPT FOR VARIABLE SPEED PLAYBACK (Engine sound, brake sound)
// =======================================================================================================
//

void IRAM_ATTR variablePlaybackTimer() {

  static uint32_t attenuatorMillis;
  static uint32_t curEngineSample;              // Index of currently loaded engine sample
  static uint32_t curTurboSample;              // Index of currently loaded turbo sample
  static uint32_t curBrakeSample;               // Index of currently loaded brake sound sample
  static uint32_t curBrakePuffSample;
  static uint32_t curStartSample;               // Index of currently loaded start sample
  static uint16_t attenuator;                   // Used for volume adjustment during engine switch off
  static uint16_t speedPercentage;              // slows the engine down during shutdown
  static int32_t a, b, c;                         // Two input signals for mixer: a = engine, b = additional sound, c = turbo sound

  portENTER_CRITICAL_ISR(&variableTimerMux);

  switch (engineState) {

    case 0: // Engine off ----
      variableTimerTicks = 4000000 / startSampleRate; // our fixed sampling rate
      timerAlarmWrite(variableTimer, variableTimerTicks, true); // // change timer ticks, autoreload true

      a = 128; // volume = zero
      if (engineOn) {
        engineState = 1;
        engineStart = true;
      }
      break;

    case 1: // Engine start ----
      variableTimerTicks = 4000000 / startSampleRate; // our fixed sampling rate
      timerAlarmWrite(variableTimer, variableTimerTicks, true); // // change timer ticks, autoreload true

      if (curStartSample < startSampleCount) {
        a = (startSamples[curStartSample] * throttleDependentVolume / 100 * startVolumePercentage / 100) + 128;
        curStartSample ++;
      }
      else {
        curStartSample = 0;
        engineState = 2;
        engineStart = false;
        engineRunning = true;
        airBrakeTrigger = true;
      }
      break;

    case 2: // Engine running ----
      variableTimerTicks = currentRpmScaled;  // our variable sampling rate!
      timerAlarmWrite(variableTimer, variableTimerTicks, true); // // change timer ticks, autoreload true

      // Engine sound
      if (curEngineSample < sampleCount) {
        a = (samples[curEngineSample] * throttleDependentVolume / 100 * idleVolumePercentage / 100) + 128;
        curEngineSample ++;
      }
      else {
        curEngineSample = 0;
      }

      // Turbo sound
      if (curTurboSample < turboSampleCount) {
        c = (turboSamples[curTurboSample] * throttleDependentTurboVolume / 100 * turboVolumePercentage / 100) + 128;
        curTurboSample ++;
      }
      else {
        curTurboSample = 0;
      }

      // Air brake release sound, triggered after stop

      // If I understand correctly, there is a popping sound if b goes directly from 0 to 128, and the original sound files fixes this
      // by starting and ending at -128. To avoid having to modify the soundfiles, I ramp up and down b at the start and end when necessary.
      
      if (airBrakeTrigger) {
        airPuffTrigger = false;
        if (curBrakeSample == 0){           //fix popping if soundfile doesn't start at -128. -W
          if ( brakeSamples[0] + 128 < b )
            b--;
          else if ( brakeSamples[0] + 128 > b )
            b++;
          else
            curBrakeSample ++;
        }
        if (curBrakeSample < brakeSampleCount) {
          b = (int)brakeSamples[curBrakeSample] + 128;
          curBrakeSample ++;
        }
        else {
          airBrakeTrigger = false;
          EngineWasAboveIdle = false;
        }
      }
      /*
      else {
        b = 0; // Ensure full engine volume, so 0!!
        curBrakeSample = 0; // ensure, next sound will start @ first sample
      }
*/
      // Air brake engage sound, triggered when braking -W
      else if (airPuffTrigger) {
        if (curBrakePuffSample == 0){           //fix popping if soundfile doesn't start at -128. -W
          if ( brakePuffSamples[0] + 128 > b )
            b++;
          else if ( brakePuffSamples[0] + 128 < b )
            b--;
          else
            curBrakePuffSample ++;
        }
        else if (curBrakePuffSample < brakePuffSampleCount) {
          b = (brakePuffSamples[curBrakePuffSample] * brakePuffVolumePercentage / 100) + 128;
          b = (int)b;
          curBrakePuffSample ++;
        }
        else {
          airPuffTrigger = false;
          EngineWasAboveIdle = false;
        }
      }
      else {
        //b = 0; // Ensure full engine volume, so 0!!
        if (b>0)//-128) //fixes pop if soundfile doesn't end at -128. -W
          b--;
        curBrakeSample = 0;
        curBrakePuffSample = 0; // ensure, next sound will start @ first sample
      }
      
  /*   
      if (airPuffTrigger) {
        if (curBrakePuffSample < brakePuffSampleCount) {
          b = (brakePuffSamples[curBrakePuffSample] * brakePuffVolumePercentage / 100) + 128;//(int)brakePuffSamples[curBrakePuffSample] + 128;
          curBrakePuffSample ++;
        }
        else {
          airPuffTrigger = false;
          //EngineWasAboveIdle = false;
          b = 0; // Ensure full engine volume, so 0!!
          curBrakePuffSample = 0; // ensure, next sound will start @ first sample
        }
      }
      //else {
      //  b = 0; // Ensure full engine volume, so 0!!
      //  curBrakePuffSample = 0; // ensure, next sound will start @ first sample
      //}
*/

      if (!engineOn) {
        speedPercentage = 100;
        attenuator = 1;
        engineState = 3;
        engineStop = true;
        engineRunning = false;
      }
      break;

    case 3: // Engine stop ----
      variableTimerTicks = 4000000 / sampleRate * speedPercentage / 100; // our fixed sampling rate
      timerAlarmWrite(variableTimer, variableTimerTicks, true); // // change timer ticks, autoreload true

      if (curEngineSample < sampleCount) {
        a = (samples[curEngineSample] * throttleDependentVolume / 100 * idleVolumePercentage / 100 / attenuator) + 128;
        curEngineSample ++;
      }
      else {
        curEngineSample = 0;
      }

      // fade engine sound out
      if (millis() - attenuatorMillis > 100) { // Every 50ms
        attenuatorMillis = millis();
        attenuator ++; // attenuate volume
        speedPercentage += 20; // make it slower (10)
      }

      if (attenuator >= 50 || speedPercentage >= 500) { // 50 & 500
        a = 128;
        speedPercentage = 100;
        engineState = 4;
        engineStop = false;
      }
      break;

    case 4: // brake bleeding air sound after engine is off ----
      variableTimerTicks = 4000000 / brakeSampleRate; // our fixed sampling rate
      timerAlarmWrite(variableTimer, variableTimerTicks, true); // // change timer ticks, autoreload true

      if (curBrakeSample < brakeSampleCount) {
        b = (brakeSamples[curBrakeSample] * brakeVolumePercentage / 100) + 128;
        curBrakeSample ++;
      }
      else {
        curBrakeSample = 0;
        engineState = 0;
      }
      break;

  } // end of switch case

  //dacWrite(DAC1, (int) (a + b - a * b / 255)); // Write mixed output signals to DAC: http://www.vttoth.com/CMS/index.php/technical-notes/68
  //dacWrite(DAC1, (int) ((a + b) / 2)); // Write mixed output signals to DAC
  //dacWrite(DAC1, (int) (constrain((a + (b / 2)), 0, 255))); // Write mixed output signals to DAC
  dacWrite(DAC1, (int) (constrain(((a * 8 / 10) + (b / 2) + (c / 5)), 0, 255))); // Write mixed output signals to DAC


  portEXIT_CRITICAL_ISR(&variableTimerMux);
}

//
// =======================================================================================================
// INTERRUPT FOR FIXED SPEED PLAYBACK (Horn etc., played in parallel with engine sound)
// =======================================================================================================
//

void IRAM_ATTR fixedPlaybackTimer() {

  static uint32_t curHornSample;                // Index of currently loaded horn sample
  static uint32_t curSirenSample;               // Index of currently loaded siren sample
  static uint32_t curSiren2Sample;               // Index of currently loaded siren sample
  static uint32_t curSound1Sample;              // Index of currently loaded sound1 sample
  static uint32_t curReversingSample;           // Index of currently loaded reversing beep sample
  static uint32_t curIndicatorSample;           // Index of currently loaded indicator tick sample
  static int32_t a, b, b1, b2,c;                 // Two input signals for mixer: a = horn or siren, b = reversing sound, indicator sound

  static uint8_t hornsequence = 0;

  portENTER_CRITICAL_ISR(&fixedTimerMux);

  switch (soundNo) {

    // Group "a" (never more than one active at a time) ----------------------------------------------

    // Modified to alternate between two siren sounds.

    // soundNo=1 and soundNo=2 selects between the two siren sounds.

    case 2: // Siren sound 2
      fixedTimerTicks = 4000000 / siren2SampleRate; // our fixed sampling rate
      timerAlarmWrite(fixedTimer, fixedTimerTicks, true); // // change timer ticks, autoreload true
      curSirenSample = 0;
      curSound1Sample = 0;

      if (sirenOn) {
        if (curSiren2Sample < siren2SampleCount) {
          a = (siren2Samples[curSiren2Sample] * siren2VolumePercentage / 100) + 128;
          curSiren2Sample ++;
        }
        else {
          curSiren2Sample = 0;
          a = 128;
          if (!sirenSwitch) sirenOn = false; // Latch required to prevent it from popping
        }
      }
      break;

    case 1: // Siren sound 1
      fixedTimerTicks = 4000000 / sirenSampleRate; // our fixed sampling rate
      timerAlarmWrite(fixedTimer, fixedTimerTicks, true); // // change timer ticks, autoreload true
      //curHornSample = 0;
      curSound1Sample = 0;
      curSiren2Sample = 0;

      if (sirenOn) {
        if (curSirenSample < sirenSampleCount) {
          a = (sirenSamples[curSirenSample] * sirenVolumePercentage / 100) + 128;
          curSirenSample ++;
        }
        else {
          curSirenSample = 0;
          a = 128;
          if (!sirenSwitch) sirenOn = false; // Latch required to prevent it from popping
        }
      }
      break;

    case 0: // Sound 1 "a" ----
      fixedTimerTicks = 4000000 / sound1SampleRate; // our fixed sampling rate
      timerAlarmWrite(fixedTimer, fixedTimerTicks, true); // // change timer ticks, autoreload true
      curSirenSample = 0;
      //curHornSample = 0;

      if (sound1On) {
        if (curSound1Sample < sound1SampleCount) {
          a = (sound1Samples[curSound1Sample] * sound1VolumePercentage / 100) + 128;
          curSound1Sample ++;
        }
        else {
          curSound1Sample = 0;
          a = 128;
          if (!sound1Switch) sound1On = false; // Latch required to prevent it from popping
        }
      }
      break;

  } // end of switch case

  // Group "b" (multiple sounds are mixed together) ----------------------------------------------

  // Reversing beep sound "b1" ----
  if (engineRunning && escInReverse) {
    //if (reversingSoundOn && !escIsBraking) { TODO
    fixedTimerTicks = 4000000 / reversingSampleRate; // our fixed sampling rate
    timerAlarmWrite(fixedTimer, fixedTimerTicks, true); // // change timer ticks, autoreload true

    if (curReversingSample < reversingSampleCount) {
      b1 = (reversingSamples[curReversingSample] * reversingVolumePercentage / 100) + 128;
      curReversingSample ++;
    }
    else {
      curReversingSample = 0;
    }
  }
  else {
    curReversingSample = 0;
    b1 = 128;
  }
/*
  // Indicator tick sound "b2" ----
  if (indicatorSoundOn) {
    fixedTimerTicks = 4000000 / indicatorSampleRate; // our fixed sampling rate
    timerAlarmWrite(fixedTimer, fixedTimerTicks, true); // // change timer ticks, autoreload true

    if (curIndicatorSample < indicatorSampleCount) {
      b2 = (indicatorSamples[curIndicatorSample] * indicatorVolumePercentage / 100) + 128;
      curIndicatorSample ++;
    }
    else {
      curIndicatorSample = 0;
      indicatorSoundOn = false;
    }
  }
  else {
    curIndicatorSample = 0;
    b2 = 128;
  }
*/    
/*
  if hornon
    if hornsequence 0
      hornsequence=1
    if hornsequence 1
      play intro
      if intro end
        hornsequence 2
    if hornsequence 2
      play loop
  else
    if hornsequence >0 //(horn was playing
      play outro
      if outro end
        hornsequence 0
*/
  //  Looping horn -W
  //  Always plays start of file and end of file, but also loops the middle for as long as the switch is held.

  //  plays the start of the file, then loops the middle of the file and ends with the end of the file
  #define HORNLOOPSTART hornSampleCount/3 //8000     //Sample number that marks start of looping section
  #define HORNLOOPEND   hornSampleCount/2 //10000    //Sample number that marks end of looping section
  if (hornOn) {
    switch(hornsequence){
      case 0:
        //if we just started, go to intro
        hornsequence = 1;
  
      case 1:
        //play intro
        fixedTimerTicks = 4000000 / hornSampleRate; // our fixed sampling rate
        timerAlarmWrite(fixedTimer, fixedTimerTicks, true); // // change timer ticks, autoreload true
       
        if (curHornSample < HORNLOOPSTART){
          b2 =  (hornSamples[curHornSample] * hornVolumePercentage / 100) + 128;
          curHornSample ++;
        }
        else {
          //curHornSample = 10000; //play from middle of the file
          //b2 = 128;
          hornsequence = 2;
          //if (!hornSwitch) hornOn = false; // Latch required to prevent it from popping
        }
        break;
  
      case 2:
        //play loop
        fixedTimerTicks = 4000000 / hornSampleRate; // our fixed sampling rate
        timerAlarmWrite(fixedTimer, fixedTimerTicks, true); // // change timer ticks, autoreload true
       
        if (curHornSample < HORNLOOPEND){
          b2 =  (hornSamples[curHornSample] * hornVolumePercentage / 100) + 128;
          curHornSample ++;
        }
        else {
          curHornSample = HORNLOOPSTART;
          //b2 = 128;
          //if (!hornSwitch) hornOn = false; // Latch required to prevent it from popping
        }
        break;
  
    }
  }
  else
  {
    if (hornsequence)
    {
      fixedTimerTicks = 4000000 / hornSampleRate; // our fixed sampling rate
      timerAlarmWrite(fixedTimer, fixedTimerTicks, true); // // change timer ticks, autoreload true
     
      if (curHornSample < hornSampleCount) {
        b2 =  (hornSamples[curHornSample] * hornVolumePercentage / 100) + 128;
        curHornSample ++;
      }
      else {
        curHornSample = 0;
        b2 = 128;
        hornsequence = 0;
        //if (!hornSwitch) hornOn = false; // Latch required to prevent it from popping
      }
    }
  }
    
    
/*
  if (hornOn) {
    fixedTimerTicks = 4000000 / hornSampleRate; // our fixed sampling rate
    timerAlarmWrite(fixedTimer, fixedTimerTicks, true); // // change timer ticks, autoreload true
   
    if (curHornSample < hornSampleCount) {
      b2 =  (hornSamples[curHornSample] * hornVolumePercentage / 100) + 128;
      curHornSample ++;
    }
    else {
      curHornSample = 0;
      b2 = 128;
      //if (!hornSwitch) hornOn = false; // Latch required to prevent it from popping
    }
  }
  else {
    curIndicatorSample = 0;
    b2 = 128;
  }*/

  // Mixing "b1" + "b2" together ----
  //b = (b1 + b2 - b1 * b2 / 255);
  //b = b1 + b2 / 2;
  c = a + b1 / 2; //W: A different volume balance. 

  // DAC output (groups a + b mixed together) ----------------------------------------------------

  //dacWrite(DAC2, (int) (a + b - a * b / 255)); // Write mixed output signals to DAC: http://www.vttoth.com/CMS/index.php/technical-notes/68
  //dacWrite(DAC2, (int) ((a + b) / 2)); // Write mixed output signals to DAC
  dacWrite(DAC2, (int) ((c + b2) / 2)); // Write mixed output signals to DAC


  portEXIT_CRITICAL_ISR(&fixedTimerMux);
}

//
// =======================================================================================================
// PPM SIGNAL READ INTERRUPT
// =======================================================================================================
//

void IRAM_ATTR readPpm() {
  unsigned long timenew = micros();
  unsigned long timediff = timenew - timelast;
  timelast = timenew;

  // reset ppm failsafe trigger signals
  ppmFailsafeCounter = 0;
  failSafe = false;

  if (timediff > 2500) {  // Synch gap detected:
    valuesInt[NUM_OF_CHL] = valuesInt[NUM_OF_CHL] + timediff; // add time
    counter = 0;
    if (average == NUM_OF_AVG) {
      for (int i = 0; i < NUM_OF_CHL + 1; i++) {
        valuesBuf[i] = valuesInt[i] / average;
        valuesInt[i] = 0;
      }
      average = 0;
      ready = true;
    }
    average++;
  }
  else {
    if (counter < NUM_OF_CHL) {
      valuesInt[counter] = valuesInt[counter] + timediff;
      counter++;
    }
  }
}



//
// =======================================================================================================
// MAIN ARDUINO SETUP (1x during startup)
// =======================================================================================================
//

void setup() {

 
 


  // Watchdog timers need to be disabled, if task 1 is running without delay(1)
  disableCore0WDT();
  disableCore1WDT();

  // Pin modes
  //pinMode(SERVO1_PIN, INPUT_PULLDOWN);
  //pinMode(SERVO2_PIN, INPUT_PULLDOWN);
  pinMode(SERVO3_PIN, INPUT_PULLDOWN);
  //pinMode(SERVO4_PIN, INPUT_PULLDOWN);

  pinMode(35,INPUT);//_PULLDOWN); //GPIO 35 button on TTGO_display esp32 module

  pinMode(PPM_PIN, INPUT_PULLDOWN);
/*
  // LED & shaker motor setup (note, that we only have timers from 0 - 15)
  headLight.begin(HEADLIGHT_PIN, 1, 500); // Timer 1, 500Hz
  tailLight.begin(TAILLIGHT_PIN, 2, 500); // Timer 2, 500Hz
  indicatorL.begin(INDICATOR_LEFT_PIN, 3, 500); // Timer 3, 500Hz
  indicatorR.begin(INDICATOR_RIGHT_PIN, 4, 500); // Timer 4, 500Hz
  fogLight.begin(FOGLIGHT_PIN, 5, 500); // Timer 5, 500Hz
  reversingLight.begin(REVERSING_LIGHT_PIN, 6, 500); // Timer 6, 500Hz
  roofLight.begin(ROOFLIGHT_PIN, 7, 500); // Timer 7, 500Hz
  sideLight.begin(SIDELIGHT_PIN, 8, 500); // Timer 8, 500Hz
  beaconLight1.begin(BEACON_LIGHT1_PIN, 9, 500); // Timer 9, 500Hz
  beaconLight2.begin(BEACON_LIGHT2_PIN, 10, 500); // Timer 10, 500Hz

  shakerMotor.begin(SHAKER_MOTOR_PIN, 13, 500); // Timer 13, 500Hz

  escOut.begin(ESC_OUT_PIN, 15, 50, 16); // Timer 15, 50Hz, 16bit (experimental)
*/
  // Serial setup
  Serial.begin(115200); // USB serial

  Serial2.begin(100000, SERIAL_8N1, 17,33,true); //true = inverted serial

//#ifdef SERIAL_COMMUNICATION
//  Serial2.begin(115200, SERIAL_8N1, COMMAND_RX, COMMAND_TX);
//#endif

  // --- Read saved preferences from non-volatile storage ---
  ReadSavedPreferences();

  //SavePreferences();


  // PPM Setup
  //attachInterrupt(digitalPinToInterrupt(PPM_PIN), readPpm, RISING);
  timelast = micros();
  timelastloop = timelast;

  // DAC
  dacWrite(DAC1, 128); // 128 = center / neutral position = 1.65V
  dacWrite(DAC2, 128);

  // Task 1 setup (running on core 0)
  TaskHandle_t Task1;
  //create a task that will be executed in the Task1code() function, with priority 1 and executed on core 0
  xTaskCreatePinnedToCore(
    Task1code,   /* Task function. */
    "Task1",     /* name of task. */
    100000,       /* Stack size of task (10000) */
    NULL,        /* parameter of the task */
    1,           /* priority of the task (1 = low, 3 = medium, 5 = highest)*/
    &Task1,      /* Task handle to keep track of created task */
    0);          /* pin task to core 0 */

  // Interrupt timer for variable sample rate playback
  variableTimer = timerBegin(0, 20, true);  // timer 0, MWDT clock period = 12.5 ns * TIMGn_Tx_WDT_CLK_PRESCALE -> 12.5 ns * 20 -> 250 ns = 0.25 us, countUp
  timerAttachInterrupt(variableTimer, &variablePlaybackTimer, true); // edge (not level) triggered
  timerAlarmWrite(variableTimer, variableTimerTicks, true); // autoreload true
  timerAlarmEnable(variableTimer); // enable

  // Interrupt timer for fixed sample rate playback
  fixedTimer = timerBegin(1, 20, true);  // timer 1, MWDT clock period = 12.5 ns * TIMGn_Tx_WDT_CLK_PRESCALE -> 12.5 ns * 20 -> 250 ns = 0.25 us, countUp
  timerAttachInterrupt(fixedTimer, &fixedPlaybackTimer, true); // edge (not level) triggered
  timerAlarmWrite(fixedTimer, fixedTimerTicks, true); // autoreload true
  timerAlarmEnable(fixedTimer); // enable


  


  
  // wait for RC receiver to initialize
  while (millis() <= 1000);

  // Read RC signals for the first time (used for offset calculations)
#if defined SERIAL_COMMUNICATION
  while (!serialInit) { // We need to read the entire buffer, so we do it until the end mark was detected!
    readSerialCommands(); // serial communication (pin 36)
  }
#elif defined PPM_COMMUNICATION
  readPpmCommands();
#else
  // measure RC signals mark space ratio
  readRcSignals();
#endif

#if defined TFT_DISPLAY
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(0x5AEB);//TFT_GREY);
#endif

  // then compute the RC channel offsets:

  // CH1
  //if (indicators) pulseZero[0] = pulseWidth[0]; // store steering offset (only, if "indicators" active)
  //else pulseZero[0] = 1500;

  // CH2
  //pulseZero[1] = 1500; // This channel is controlled by a 3 position switch, so we don't want auto calibration!

  // CH3
  if (!engineManualOnOff) pulseZero[2] = pulseWidth[2]; // store throttle offset (only, if "engineManualOnOff" inactive)
  else pulseZero[2] = 1500;

  // CH4
  //pulseZero[3] = 1500; // This channel is controlled by a potentiometer, so we don't want auto calibration!

  // Calculate RC signal ranges for all channels (0, 1, 2, 3)
  for (uint8_t i = 0; i <= 3; i++) {
    // Input signals
    pulseMaxNeutral[i] = pulseZero[i] + pulseNeutral;
    pulseMinNeutral[i] = pulseZero[i] - pulseNeutral;
    pulseMax[i] = pulseZero[i] + pulseSpan;
    pulseMin[i] = pulseZero[i] - pulseSpan;
    pulseMaxLimit[i] = pulseZero[i] + pulseLimit;
    pulseMinLimit[i] = pulseZero[i] - pulseLimit;
  }
  // ESC output
  escPulseMax = pulseZero[2] + escPulseSpan;
  escPulseMin = pulseZero[2] - escPulseSpan;


  // First loop: set center values for throttle and steering
        static byte haveReadCenterValues = 0;
        if (!haveReadCenterValues){
          //int throttleCenter;
          throttleCenter = pulseZero[2];
          Serial.println(throttleCenter);
          //steeringCenter = SBUS.channels[1];
          haveReadCenterValues = 1;
          //set neutral range?
          throttleNeutralLowerLimit = throttleCenter - neutralLowerOffset;
          throttleNeutralUpperLimit = throttleCenter + neutralUpperOffset;
        }


  // Hold down button 2 to enter calibration.
      if (digitalRead(35) == LOW)
      {
        HUMANSERIAL.println("low");
        buttonSetupCalibrationActive = 1;
      }
    
        
    
}

// Read variables saved to non-volatile memory
void ReadSavedPreferences()
{
  Serial.println("reading:");
  preferences.begin("settings", false);


  throttleCenter = preferences.getUInt("tC", 1500);
  neutralUpperOffset = preferences.getUInt("tNUL", 80);
  neutralLowerOffset = preferences.getUInt("tNLL", 80);
  throttleFull = preferences.getUInt("tFull", 2000);
  throttleAxisReversed = preferences.getUInt("trev", 0);
  reverseType2 = preferences.getUInt("revtype", 1);  
  //Serial.println(preferences.getUInt("test",9));

  preferences.end();
  Serial.printf("center:%d  upper:%d  lower:%d  full:%d  reversed:%d revtype:%d\n",throttleCenter,neutralUpperOffset,neutralLowerOffset,throttleFull,throttleAxisReversed,reverseType2);
}

// Save variables to non-volatile memory
// This fails with a core panic if an interrupt happens while writing, so we have to disable interrupts temporarily.
// I'm no expert, but read that mutex would work. It didn't. timerAlarmDisable worked for me though.
//static portMUX_TYPE my_mutex;
void SavePreferences()
{
  //vPortCPUInitializeMutex(&my_mutex);
  //portENTER_CRITICAL(&my_mutex);
  timerAlarmDisable(variableTimer);     //core 1 panics if interrupt happens while writing to nvs
  timerAlarmDisable(fixedTimer);
  preferences.begin("settings", false);

  Serial.println("saving:");
  Serial.printf("center:%d  upper:%d  lower:%d  full:%d  reversed:%d revtype:%d\n",throttleCenter,neutralUpperOffset,neutralLowerOffset,throttleFull,throttleAxisReversed,reverseType2);


  preferences.putUInt("tC", throttleCenter);
  preferences.putUInt("tNUL", neutralUpperOffset);
  preferences.putUInt("tNLL", neutralLowerOffset);
  preferences.putUInt("tFull", throttleFull);
  preferences.putUInt("trev", throttleAxisReversed);
  preferences.putUInt("revtype", reverseType2); 
  //preferences.putUInt("test",throttleAxisReversed); 

  preferences.end();

  ReadSavedPreferences();
  
  timerAlarmEnable(variableTimer);
  timerAlarmEnable(fixedTimer);
  //portEXIT_CRITICAL(&my_mutex);
}




//
// =======================================================================================================
// LOOP TIME MEASUREMENT
// =======================================================================================================
//

unsigned long loopDuration() {
  static unsigned long timerOld;
  unsigned long loopTime;
  unsigned long timer = millis();
  loopTime = timer - timerOld;
  timerOld = timer;
  return loopTime;
}

//
// =======================================================================================================
// MAIN LOOP, RUNNING ON CORE 1
// =======================================================================================================
//

void loop() {
/*
  #if defined  SERIAL_COMMUNICATION
    readSerialCommands(); // Serial communication (pin 36)
    showParsedData();
  #elif defined PPM_COMMUNICATION
    readPpmCommands(); // PPM communication (pin 34)
  #else
    readSerialCommands2();
    // measure RC signals mark space ratio
    readRcSignals();
  #endif
  

  #if defined DIRECT_SERIAL_INPUT
    readSerialCommands2();
  #elif defined SBUS_INPUT*/
    //Read from serial port to buffer
    SBUSinput();

    //if all channels are in and ready
    if (SBUS.channelsReady)
    {
      //SBUSpreparechannels();
      //SBUSprintstuff();
      //SBUSpreparechannels_M();  //convert buffer to channels. Called from SBUS_input()
      SBUS.channelsReady = 0;   
      SBUSthrottle();           //copy throttle channel to pulseWidth[2]
      SBUSswitches();           //process horn and siren switches
      //displayRefresh();
      //Serial.println(pulseWidth[2]);

      #if defined TFT_DISPLAY
        tft.setCursor(0, 0, 2);
        tft.print("thrESC:");
        tft.print(map(SBUS.channels[channelThrottleESC-1],0,2000,1000,2000));
        tft.print("thrAudio:");
        tft.print(map(SBUS.channels[channelThrottleAudio-1],0,2000,1000,2000));
      #endif
  
    }
  //#else
    //readRcSignals();
  //#endif

  if (buttonSetupCalibrationActive)   //buttonSetupCalibration should only run if radio is active, so don't move this to donoradioStuffList
  {
    buttonSetupCalibration();
  }

  readSerialCommands2();        //read inputs from serial port 1. <0,thr,sir,hor,eng> or <1,*config*>
  //serialSwitches();             //set (override) switches based on serial 1 input
  audioLogic();                 //engine switch and turn off horn and siren if engine off
  sirenTimerSwitch();           //switch between siren 1 and 2 every x seconds.

  //--
  //End up here with pulseWidth[2], sirenOn, hornOn, engineOn.
  //--
  
  // Horn triggering
  //triggerHorn();

  // Indicator (turn signal) triggering
  //triggerIndicators();
  //Serial.printf("ignCh: %d\t eOn: %d\t estate: %d\n",SBUS.channels[9-1],engineOn,engineState);
  //Serial.printf("audioCh: %d\t hornSwitch: %d\t sirenSwitch: %d\t hornOn: %d\t sirenOn: %d\t soundNo: %d\n",SBUS.channels[12-1],hornSwitch,sirenSwitch,hornOn,sirenOn,soundNo);
  //Serial.println(engineOn);
}

//
// =======================================================================================================
// 1st MAIN TASK, RUNNING ON CORE 0 (Interrupts are running on this core as well)
// =======================================================================================================
//

void Task1code(void *pvParameters) {
  for (;;) {

    // Map pulsewidth to throttle. Calculate engine volume. 1500-2000 and 1500-1000 to 0-500.
      //mapThrottle();

    //Automatic gear simulation. Reads radio input and generates engineRPM, shaftRPM, gear and ESCspeed
      gearSim();

    // Simulate engine mass, generate RPM signal. Map throttle 0-500 to interrupt interval.
      //engineMassSimulation();



    //throttleCalculations replaces engineMassSimulation
    //It does the same thing, but split up.
    //Only use one of the following:
      //throttleCalculations(currentThrottle);                //requires mapThrottle() to run first.
      throttleCalculations2(currentGlobalEngineRPM);          //replace mapThrottle() with gearSim() if using this.
    

    // Switch engine on or off
      //engineOnOff();

    // LED control
      //led();

    // Shaker control
      //shaker();

    // ESC control (Crawler ESC with direct brake on pin 33)
    // Wombii: some functions moved to logicstuff()
      //esc();

    //Reverse and brake sounds
      logicstuff();

      

    

    

    // measure loop time
    loopTime = loopDuration();
  }
}
