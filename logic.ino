

 byte ignitionState = 0;
 byte sirenNumber = 0;





//
//================================================================
//  READING SBUS CHANNELS
//================================================================
//

//Save SBUS throttle channel as pulseWidth[2]
void SBUSthrottle (void){
  pulseWidth[2] = map(SBUS.channels[channelThrottleESC-1],0,2000,1000,2000);
}

//Save SBUS gear channel as pulseWidth[1]
void SBUSgear (void){
  pulseWidth[1] = map(SBUS.channels[channelGear-1],0,2000,1000,2000);
}

//Save SBUS reverse gear switch channel?

//Read incremental gear switch?
// P/R/N/D/1/2/3
void SBUSincrementalGear (void){
  //988
  //1244
  //1500
  //1756
  //2012
  /*
   currentGear = map(SBUS.channels[channelIncrementalGear-1],0,2000,-1,3);
   */
  
}


//Read additional SBUS channels.
void SBUSswitches (void){
    
    // ----  ignition switch  ---- //
    // --------------------------- //

    //Standard 3 position switch. off / electrics / engine

    if (SBUS.channels[channelIgnition-1] < 700)
    {
        ignitionState = 0;
    }
    else if(SBUS.channels[channelIgnition-1] > 1300)
    {
        ignitionState = 2;
    }
    else // centered
    {
        ignitionState = 1;
    }

    // ----  Horn + siren switch  ---- //
    // ------------------------------- //
    //Horn and siren with latching transmitter switch
    //4 position switch (or virtual 4 position switch controlled with trim tabs)
    //One channel split into 4 parts. off / horn / horn + siren / siren

    if (SBUS.channels[channelAudioSwitch-1] < 700)      
    {
      hornSwitch = 0;
      sirenSwitch = 0;  
      //Serial.println(0);
    }
    else if(SBUS.channels[channelAudioSwitch-1] > 700 && SBUS.channels[channelAudioSwitch-1] < 1200) 
    { 
      hornSwitch = 1;
      sirenSwitch = 0;
      //Serial.println("horn");
    }
    else if(SBUS.channels[channelAudioSwitch-1] > 1200 && SBUS.channels[channelAudioSwitch-1] < 1700) 
    {
      hornSwitch = 1;
      sirenSwitch = 1;
      //Serial.println("h+s");
    }
    else
    {
      hornSwitch = 0;
      sirenSwitch = 1;
      //Serial.println("siren");
    }

/*
    //Horn and siren if momentary switches
    if (SBUS.channels[channelAudioSwitch-1] < 700)      
    {
      hornSwitch ^= 1;  
    }
    else if(SBUS.channels[channelAudioSwitch-1] > 1200 && SBUS.channels[channelAudioSwitch-1] < 1600) 
    { 
      //siren1
      sirenSwitch ^= 1;
      sirenNumber = 0;
      
    }
    else if(SBUS.channels[channelAudioSwitch-1] > 1600)
    {
      //siren2
      sirenSwitch ^= 1;
      sirenNumber = 1;
    }

    //sirenTimerSwitch();
    soundNo = 1+sirenNumber;  // 1 = siren
  */  

    
}


//
//================================================================
//  Sound logic
//================================================================
//


//Enable/disable sounds, and switch engine on/off based on an ignition switch
void audioLogic (void)
{
  if (ignitionState == 2)
    {
      engineOn = 1;
      sirenOn = sirenSwitch;
      hornOn = hornSwitch;
      //if (sirenOn) Serial.println("siren");
      //if (hornOn) Serial.println("horn");
    }
    else if (ignitionState == 0)
    {
      sirenOn = 0;
      hornOn = 0;
      
    }
    else
    {
      engineOn = 0;
      sirenOn = sirenSwitch;
      hornOn = hornSwitch;
      //if (sirenOn) Serial.println("siren");
      //if (hornOn) Serial.println("horn");
    }
}


//Switch between two siren sounds based on timer.
//Uses soundNo 1 and 2 to switch between siren sounds.
void sirenTimerSwitch (void)
{
  static unsigned long sirenTime = 0;
  //static byte sirenNumber = 0;
  if (sirenNumber == 0 && millis() - sirenTime >10000)
  {
    sirenNumber ^= 1;
    sirenTime = millis();
  }

  if (sirenNumber == 1 && millis() - sirenTime >20000)
  {
    sirenNumber ^= 1;
    sirenTime = millis();
  }

  //Switch to fast when beeping the horn.
  if (hornOn) {
    sirenNumber = 0;
    sirenTime = millis();
  }
  soundNo = 1+sirenNumber;  // 1 = siren

  
  //Serial.println(soundNo);
}



//
// ===========================================================================================
// Gear simulation
// ===========================================================================================
// -W

//THIS DESCRIPTION MAY BE INACCURATE WITH CURRENT BUILD!
//Automatic gear simulation. Reads radio input and generates engineRPM, shaftRPM, gear and ESCspeed
//Currently reads a specific SBUS channel
// Required global variable: currentGlobalEngineRPM (0-500)
//Usage: call gearSim() in the main loop and use currentGlobalEngineRPM instead of throttle for the throttle/sound calculations.
//Use throttleCalculations2(currentGlobalEngineRPM); in main loop instead of mapThrottle() and engineMassSimulation()

//last gear ratio must be 1 to have maxEngineRPM in top gear at the top of the throttle stick.
//Make sure shift points and ratios work by calculating rpms:
//gear up: engineShiftRPMup / ratio[n1-1] = shaftRPM. shaftRPM * ratio[n2-1] must then be larger than minEngineRPM.
//example with ratio 4 and 2: 4000/4 = 1000. 1000*2 = 2000 > 1400, OK

#define NumberOfGears 4
//const int NumberOfGears = 6;
const int maxEngineRPM = 5000;  //always 5000 to make scaling to sound input easier. 0-5000 rpm = 0-500 throttle input.
//const int minEngineRPM = 1400;  //Shift down rpm
const int engineShiftDownRPM = 1400;
const int engineShiftUpRPM = engineShiftDownRPM*2.2; //shift up rpm

//The final gear ratio in the array is now reverse. 
#if NumberOfGears==6
const float ratio[NumberOfGears+1] = {7,4.3,2.4,1.8,1.3,1,5};//{10,7,5,3,2,1}; 7,4,3,2,1.5,1 
#elif NumberOfGears==4
const float ratio[NumberOfGears+1] = {7,3.5,1.8,1,1};
#elif NumberOfGears==2
const float ratio[NumberOfGears+1] = {1.8,1,1.5};
#endif

const int maxAcceleration = 10;
const int maxNegativeAcceleration = -10;

static int modifiedShiftUpRPM = engineShiftUpRPM;
static int modifiedShiftDownRPM = engineShiftDownRPM;


// ----  Main gear function   ---- //
// ------------------------------- //

//Shaft RPM is the output from the gearbox and controls the speed of the truck.
//Engine RPM and shaft RPM is connected through a gear ratio.
//To simplify tuning of the algorithm, we accelerate and decelerate shaftRPM and then calculate engine rpm for sound.
//In an automated gearbox with clutch, the shaft RPM would decrease a bit while coasting with cluctch disengaged,
//but in the allison torque converter gearbox, the coast time is minimal to zero.

//This version works with ESC speed being managed based on shaftRPM.

int gearSim()
{
  static int currentEngineRPM = 0;
  static int positive_currentEngineRPM = 0;
  static int requestedAcceleration = 0; //= stickInputToRequestedAcceleration();
  static int requestedBrake = 0;
  static int requestedGear = 1;         //autoGearSelection(currentEngineRPM);
  static int ESCspeed = 0;
  static int shaftRPM = 0;


  // - Throttle input to requestedAcceleration -
  // In this case, requested acceleration is the difference between throttle stick and current ESC signal.
  requestedAcceleration = stickInputToRequestedAcceleration3(shaftRPM);

  // - Dynamic shift points
  moveShiftPoints(requestedAcceleration);

  
    
  // - Gear up or down -
  requestedGear = autoGearSelection(currentEngineRPM);

  // - Accelerate or decelerate the shaft RPM -
  shaftRPM = accelerationToShaftRPM(shaftRPM,requestedGear,requestedAcceleration);

  // - Calculate the new engine RPM from the current gear and shaft RPM - 
  // Engine RPM is always positive
  currentEngineRPM = (int)(shaftRPM * ratio[requestedGear-1]);
  currentEngineRPM = constrain(currentEngineRPM,0,maxEngineRPM); //constrain it positive

  //Since we're doing everything backwards now, we have to limit shaftRPM to the point where engine rpm would exceed max engine rpm.
  int maxShaftRPM = (int)(maxEngineRPM/ratio[requestedGear-1]);
  shaftRPM = constrain(shaftRPM,-5000,maxShaftRPM); //shaft RPM can be negative
  
  //The acceleration/deceleration calculation is very simplified and lags a bit. Make sure RPM actually reduces to zero.
  if (abs(shaftRPM) < 10)
    shaftRPM = 0;

  // - Convert shaft RPM to ESC speed -
  //Customized for combination of 1060WP ESC and reverse gear switching code.
  
  //If normal driving mode: limit output between max forward and max back(brake).
  //If reverse driving mode: limit output between neutral and max back (reverse).
  if (reverseGear)
  {
    shaftRPM = constrain(shaftRPM,-100,2000);
  }
  else
  {
    shaftRPM = constrain(shaftRPM,-5000,3000); //top is limited by esc. my esc has max rpm at 1800 us which matches 3000 rpm. TODO do this better.
  }

  //max rpm = 5000. ESC pulse is neutral +/- 500 us.
  int ESCspeedDelta = shaftRPM;
  ESCspeedDelta = ESCspeedDelta/10;

  //if reverse: subtract a number from neutral to use range 1000-1500 us.
  if (reverseGear)
  {
    ESCspeed = throttleCenter - ESCspeedDelta;
  }
  //if forward: 
  else
  {
    //ESCspeed = throttleCenter+ESCspeedDelta;
    if (ESCspeedDelta > 0)
      ESCspeed = throttleNeutralUpperLimit+ESCspeedDelta;
    else if (ESCspeedDelta < 0)
      ESCspeed = throttleNeutralLowerLimit+ESCspeedDelta;
    else
      ESCspeed = throttleCenter;
  }

  // - ESC signal is shaftRPM (0-5000) mapped to rc signal (1500-2000) -
  //ESCspeed = (int)map(shaftRPM,0,maxEngineRPM*ratio[NumberOfGears-1],throttleCenter,2000);


  // ----  Debug to display     ---- //
  unsigned long debugPrintTime = 0;
  if (millis() - debugPrintTime > 100)
  {
    #if defined TFT_DISPLAY
    //tft.fillScreen(0x5AEB);//TFT_GREY);
    tft.setCursor(180, 0, 4);
    tft.print("G: ");
    tft.print(requestedGear);

    tft.setCursor(130,0,2);
    int debugSpeed = map(shaftRPM,0,3000,0,120);
    tft.print("km/h:");
    tft.print(debugSpeed);
/*
    //Throttle
    int THRx = 50;
    int THRy = 25;
    tft.drawRect(THRx,THRy,110,12,TFT_BLACK);
    int fillTHR = map(pulseWidth[2],throttleCenter,2000,1,100);
    fillTHR = constrain(fillTHR,1,100);
    tft.fillRect(THRx+5,THRy+2,fillTHR,8,TFT_BLACK);
    tft.fillRect(THRx+5+fillTHR,THRy+2,100-fillTHR,8,0x5AEB); //grey
    
*/
    /*
    //RPM with shift:
    int RPMx = 50;
    int RPMy = 40;
    tft.drawRect(RPMx,RPMy,110,12,TFT_BLACK);
    int fillRPM = map(currentEngineRPM,0,4500,1,100);
    tft.fillRect(RPMx+5,RPMy+2,fillRPM,8,TFT_BLACK);
    tft.fillRect(RPMx+5+fillRPM,RPMy+2,100-fillRPM,8,0x5AEB); //grey

    int markerUp = map(modifiedShiftUpRPM,0,4500,1,100);
    tft.drawRect(RPMx+markerUp,RPMy,4,12,TFT_RED);
    int markerDown = map(modifiedShiftDownRPM,0,4500,1,100);
    tft.drawRect(RPMx+markerDown,RPMy,4,12,TFT_GREEN);
    */

    //Throttle vertical
    int THRx = 170;
    int THRy = 30;
    int THRxSize = 12;
    int THRySize = 100;
    
    tft.drawRect(THRx,   THRy,   THRxSize,   THRySize,   TFT_BLACK);
    tft.fillRect(THRx+2, THRy+2, THRxSize-4, THRySize-4, 0x5AEB);
    int fillTHR = map(pulseWidth[2],throttleCenter,1900,1,100);
    fillTHR = constrain(fillTHR,1,100);
    tft.fillRect(THRx+2, THRy+THRySize-2-fillTHR, 8,fillTHR,TFT_BLACK); //grey0x5AEB
    //tft.fillRect(THRx+2, THRy+2, 8,THRySize-fillRPM,0x5AEB);
    
    //RPM vertical with shift:
    int RPMx = 200;
    int RPMy = 30;
    int RPMxSize = 12;
    int RPMySize = 100;
    
    tft.drawRect(RPMx ,RPMy ,RPMxSize ,RPMySize ,TFT_BLACK);
    tft.fillRect(RPMx+2, RPMy+2, RPMxSize-4, RPMySize-4, 0x5AEB);
    int fillRPM = map(currentEngineRPM,0,4500,1,90);

    tft.fillRect(RPMx+2, RPMy+RPMySize-2-fillRPM, 8,fillRPM,TFT_BLACK); //grey0x5AEB
    //tft.fillRect(RPMx+2, RPMy+2, 8,RPMySize-fillRPM,0x5AEB);

    int markerUp = map(modifiedShiftUpRPM,0,4500,1,90);
    tft.drawRect(RPMx,RPMy+RPMySize-markerUp,12,4,TFT_RED);
    int markerDown = map(modifiedShiftDownRPM,0,4500,1,90);
    tft.drawRect(RPMx,RPMy+RPMySize-markerDown,12,4,TFT_GREEN);

    //modifiedShiftUpRPM
    //modifiedShiftDownRPM
    #endif
    debugPrintTime = millis();
  }
  

  // ----  Debug to Serial      ---- //

  // - Optional print to serial (Serial plotter compatible) - 
  //HUMANSERIAL.printf("maxRPM:5000, minRPM:-5000, center: %d input: %d, acc: %d, G: %d RPM: %d SFHT: %d, SPD: %d\n", throttleCenter, pulseWidth[2],requestedAcceleration,requestedGear, currentEngineRPM, shaftRPM, ESCspeed);
  //HUMANSERIAL.printf("center: %d input: %d, G: %d RPM: %d SFHT: %d, SPD: %d\n", throttleCenter, pulseWidth[2],requestedGear, currentEngineRPM, shaftRPM, ESCspeed);
  //HUMANSERIAL.printf("eRPM: %d, modUp: %d, modDN: %d, G: %d\n",currentEngineRPM,modifiedShiftUpRPM,modifiedShiftDownRPM,requestedGear);

  
  // ----  Output variables     ---- //

  // - Convert engine RPM 0-5000 to a variable usable in throttleCalculations2() for sound math - 
  currentGlobalEngineRPM = currentEngineRPM/10;//constrain(currentEngineRPM,0,500);
  currentGlobalShaftRPM = shaftRPM/10;
  

  return ESCspeed; //ESCspeed is a value ready to be used as pulsewidth for ESC.
}




// ----  Throttle input       ---- //
// ------------------------------- //

//Compares stick input to current truck speed and uses the difference as acceleration variable.
//Because gear ratio is currently a variable in the ESCspeed calculation, req acc is much higher in lower gears.
int stickInputToRequestedAcceleration (int currentESCspeed)
{
  int stickInput = pulseWidth[2];
  int reqAcceleration = stickInput - currentESCspeed;
  reqAcceleration = reqAcceleration ;

  
  
  return reqAcceleration;
}


int stickInputToRequestedAcceleration2 (int currentESCspeed)
{
  int stickInput = pulseWidth[2];
  int reqAcceleration = stickInput - currentESCspeed;
  reqAcceleration = reqAcceleration ;

  //if (stickInput < throttleNeutralLowerLimit);
    //requestedBrake = 1;

  
  return reqAcceleration;
}

int stickInputToRequestedAcceleration3 (int RPM)
{
  int stickInput = pulseWidth[2];
  RPM = RPM/10;
  int reqAcceleration = stickInput - (throttleCenter + RPM);
  //int reqAcceleration = stickInput - currentESCspeed;
  //reqAcceleration = reqAcceleration ;

  //if (stickInput < throttleNeutralLowerLimit);
    //requestedBrake = 1;

  
  return reqAcceleration;
}


// ----  Gearing              ---- //
// ------------------------------- //

//Move shift points up under acceleration, relax them back down under constant speed.
//Allows automatic downshift when punching throttle and upshift for better economy when steady throttle.
void moveShiftPoints(int reqAcceleration)
{
  static unsigned long lastTimeStamp = 0;
  int addValue = 0;

  
  if (reqAcceleration > 10)
  {
    addValue = 600;//reqAcceleration*8; //600
    addValue = constrain(addValue,0,600);
    //modifiedShiftUpRPM =  engineShiftUpRPM + addValue;
    modifiedShiftDownRPM = engineShiftDownRPM + addValue;
    modifiedShiftUpRPM = modifiedShiftDownRPM * 2.2;
  }
  else
  {
    if (modifiedShiftDownRPM > engineShiftDownRPM)
    {
      addValue = -20;
      if(millis()-lastTimeStamp > 200)
      {
        //modifiedShiftUpRPM += addValue;
        modifiedShiftDownRPM += addValue;
        modifiedShiftUpRPM = modifiedShiftDownRPM * 2.2;
        lastTimeStamp = millis();
      }
    }
    //modifiedShiftUpRPM = modifiedShiftDownRPM * 2.2;
    
  }

  
}



//Automatic gear selector. Gear up if engine RPM is more than max, gear down if engine RPM is less than min RPM.
int autoGearSelection (int engineRPM)
{
  static int reqGearValue = 1;
  

    if (engineRPM > modifiedShiftUpRPM)
    {
      reqGearValue++;
    }
    if (engineRPM < modifiedShiftDownRPM)
    {
      reqGearValue--;
    }
    reqGearValue = constrain(reqGearValue,1,NumberOfGears); //stick to allowed gear values

    if (reverseGear)
      reqGearValue = NumberOfGears+1;
  

 
  return reqGearValue;
}


// ---- RPM Calculations      ---- //
// ------------------------------- //

//This is the one currently in use
int accelerationToShaftRPM(int outputRPM, int reqGearValue, int reqAcceleration)
{
  
  //If input stick is moving forward:
  if(reqAcceleration > 0)
  {
    //if (outputRPM < 0 && !reverseGear) //Special case: if braking return to zero faster.
    //  reqAcceleration = reqAcceleration;
    //else
    {
      //If releasing brake input while esc brake is active:
      if (outputRPM < 0)
      {
        //Serial.println("relbrk");
        reqAcceleration = reqAcceleration;
      }
      //If acceleration, positive throttle input:
      else
      {
        reqAcceleration = reqAcceleration/reqGearValue;
        reqAcceleration = constrain(reqAcceleration,1,maxAcceleration);
        
      }
      
    }
  }
  //If input stick is moving backward
  else if (reqAcceleration < 0)
  {
    int brakeValue = 0;
    //If braking, input stick below center
    if (pulseWidth[2] < throttleNeutralLowerLimit)
    {
      brakeValue = (throttleCenter - pulseWidth[2]);
      brakeValue = map(brakeValue, 0, 500, 0,-500);
    }
    //If coasting, input stick above center
    reqAcceleration = constrain(reqAcceleration,maxNegativeAcceleration,-1); //limiting negative acceleration gives the vehicle inertia when coasting.
    reqAcceleration = reqAcceleration + brakeValue;                          //adding negative acceleration from braking.
  }


  //Serial.println(reqAcceleration);
  //Update engine RPM every x millisecond. Can include gear value in calculation to slow down acceleration in higher gears.
  static unsigned long outputRPMUpdateTime = millis();
  if (millis() - outputRPMUpdateTime > 10)//(reqGearValue * 10) )//= acceleration is slower for higher gears
  {
    outputRPM = outputRPM + reqAcceleration; //alternative: engineRPM + reqAcceleration * inverted gearmodifier
    outputRPMUpdateTime = millis();
  }
  //Serial.println(outputRPM);
  return outputRPM;
}



//averaging over time with low memory usage
//Need a new function for each variable
//smoothingB(throttleInput,3)
int smoothingB(int smoothingTarget, byte smoothingStrength)
{
  //const int smoothingStrength = 3; // (0-4)
  static int smoothingValue = 0;

  smoothingValue = smoothingValue + ((smoothingTarget - smoothingValue) >> smoothingStrength);

  return smoothingValue;
  
}

//Convert engine RPM to ESC signal value? TODO?
int engineRPMtoESCspeed(int engineRPM,int reqGearValue)
{
  static int reqESCspeed = throttleCenter;
  
  reqESCspeed = engineRPM;// * reqGearValue;
  
  return reqESCspeed;
}




//
//================================================================
//  BRAKE AND REVERSE DETECTION / ACTIVATION + Brake and reverse sound trigger
//================================================================
// -W

// -- TRICK STANDARD RC ESC INTO REVERSE MODE WITH A TRANSMITTER SWITCH -- 
// Requires one switch for FWD/REV switching
// FWD mode: Throttle forward: esc drive, Throttle backward: esc brake.
// REV mode: Throttle forward: esc drive in reverse, throttle backward: coast to a stop?

// Example: Quickrun 1060 ESC. Forward/Brake/Reverse ESC with double pump to activate reverse.
//  It has a neutral deadzone of roughly +/- 30 around center.
//  Throttle axis:
//  | -------------- | -----(C)----- | ---------------- |
//  (MIN)   back   (A)   neutral   (B)   forward    (MAX)
//
//  MIN = ~1000. A = Center - 30. C = throttle center ~1500. B = Center + 30. MAX = ~2000.
//
//  To activate brake mode:   Move from <forward>, through <neutral> and into <back>.
//  To exit brake mode:       Move from <back> into <neutral>.
//  To activate reverse mode: Move from <back> into <neutral> and back into <back>.
//  To exit reverse mode:     Move from <back> into <forward>.
//  Note that reverse mode stays activated in <neutral> and doesn't exit until hitting (B) or center + 30.


// ---- PROCESS INPUTS        ---- //
// ------------------------------- //

void inputProcessing (void)
{
  // ---- WAIT FOR ESC --- //
  //Send a throttleCenter signal at startup to initialise ESC

  if (millis() < 2000)
  {
    //escSignal = map(throttleCenter, 1000, 2000, 3278, 6553); // 1 - 2ms (5 - 10% pulsewidth of 65534)
    //escOut.pwm(escSignal);
    //Serial.println("WAIT");
    ;
  }
  else
  {
  
    // --- DETECT THROTTLE  --- //

    //changed to local. Reads SBUS channel to throttle info, but can read pulseWidth[2] instead.
    int throttleAxis = pulseWidth[2]; //map(SBUS.channels[channelThrottleAudio-1],0,2000,1000,2000);//
    int throttleDeviationFromCenter = (throttleAxis-throttleCenter); // = -500 to +500



    // --- DETECT REVERSE GEAR SWITCH --- //
    
    //static byte reverseGear = 0;
    
    #if defined INCREMENTALGEAR
    if (currentGear == -1)
      reverseGear = 1;
    else
      reverseGear = 0;
    #else
    if (map(SBUS.channels[channelReverseGear-1],0,2000,1000,2000) < 1100 )
      reverseGear = 1;
    else
      reverseGear = 0;
    #endif

    
    // --- TRICK ESC WITH INPUT SEQUENCE --- //

    ESCmodeControl(reverseGear, (escCommand - throttleCenter));//throttleDeviationFromCenter);

    // --- TRIGGER SOUNDS BASED ON THROTTLE COMMANDS --- //

    throttleSoundTriggering(reverseGear, escCommand);
  }
}

// ---- ESC SIGNAL SEQUENCING ---- //
// ------------------------------- //

//  This function overrides the esc commands made in other functions.
//  Quickrun 1060 ESC: Forward to go forward, back to brake, back-neutral-back to reverse.
//  When shifting to reverse, we have to output back -> neutral -> back to trick the ESC into reverse mode.
//  In forward mode we have to blip the throttle forward when going from brake to neutral, to avoid reversing if pushing back a second time.

void ESCmodeControl (byte reverseGear, int throttleDeviationFromCenter)
{

    // --- TRICK ESC INTO CORRECT MODE --- //

    const int commandSequencePause = 50;
    static unsigned long commandSequenceTime = 0;

    static byte reverseGearSet = 0;
    static byte forwardGearSet = 0;

    static int escOverrideCommand = throttleCenter; //doesn't need to be static?


    //int throttleDeviationFromCenter = (escCommand - throttleCenter);

    //default to input
    escOverrideCommand = escCommand;
    
    if(reverseGear) //if reverseGear Switch active
    {
      forwardGearSet = 0;
      
      if (!reverseGearSet)
      {
        static byte selection = 0;
        
        switch(selection)
        {
          case 0:
            break;
          case 1: //Start by blipping forward to enter a known state.
            escOverrideCommand = throttleNeutralUpperLimit;
            break;
          case 2: //Go just past the lower end of the ESC's neutral deadband.
            escOverrideCommand = throttleNeutralLowerLimit;
            break;
          case 3: //Return to center (or anywhere in the neutral deadband).
            escOverrideCommand = throttleCenter;
            break;
          case 4: //Go back to the <back> zone again to activate reverse mode.
            escOverrideCommand = throttleNeutralLowerLimit;
            break;
          case 5: //Return to center and return control to human.
            escOverrideCommand = throttleCenter;
            break;
          case 6:
            Serial.println("REV");
            reverseGearSet = 1;
            selection = 0;
            break;
          default:
            selection = 0;
            break;
          
        }
        //Allow each command a few milliseconds to be caught by the ESC. Remember the ESC expects a pulse every 5-20ms.
        if (millis() - commandSequenceTime > commandSequencePause)
        {
          //escSignal = map(escOverrideCommand, 1000, 2000, 3278, 6553); // 1 - 2ms (5 - 10% pulsewidth of 65534)
          //escOut.pwm(escSignal);
          selection++;
          commandSequenceTime = millis();
        }
      }/*
      else //if reverseGearSet
      {
        //If we have tricked the ESC into reverse mode, the throttle input is inverted, but only on the forward side of center.
        //esc 1000-1500 -- throttle 1500-2000.
        escOverrideCommand = throttleCenter - throttleDeviationFromCenter;
        if (escOverrideCommand < throttleCenter)
        {
          ;
        }
        else
        {
          escOverrideCommand = throttleCenter;
        }
        //escSignal = map(escOverrideCommand, 1000, 2000, 3278, 6553); // 1 - 2ms (5 - 10% pulsewidth of 65534)
        //escOut.pwm(escSignal);
      }*/
    }

    //If not reverseGear, if drive
    else
    {
      reverseGearSet = 0;

      static byte output_escBrakeCorrection = 0;
      static byte escBrakeCorrectionNeeded = 0;
        
      if (!forwardGearSet)
      {
        static byte selection = 0;
        
        switch(selection)
        {
          case 0:
            break;
          case 1:
            escOverrideCommand = throttleNeutralUpperLimit;
            break;
          case 2:
            escOverrideCommand = throttleCenter;
            break;
          case 3:
            Serial.println("FWD");
            forwardGearSet = 1;
            selection = 0;
            break;
          default:
            selection = 0;
            break;
          
        }
        if (millis() - commandSequenceTime > commandSequencePause)
        {
          //escSignal = map(escOverrideCommand, 1000, 2000, 3278, 6553); // 1 - 2ms (5 - 10% pulsewidth of 65534)
          //escOut.pwm(escSignal);
          selection++;
          commandSequenceTime = millis();
        }
      }
      else //if forwardGearSet
      {
        //esc 1000-1500 -- throttle 1500-2000.
        //escCommand = throttleCenter + throttleDeviationFromCenter;
        //If escCommand is in back zone, forward blip will be needed when entering neutral zone.
        if (escCommand < throttleNeutralLowerLimit)
        {
          escBrakeCorrectionNeeded = 1;
          commandSequenceTime = millis(); // time mark for holding the output
        }
        //If escCommand is within neutral zone
        else if(escCommand >= throttleNeutralLowerLimit && escCommand < throttleNeutralUpperLimit)
        {
          if (escBrakeCorrectionNeeded)
            output_escBrakeCorrection = 1;
        }
        //if escCommand is in forwardZone we can skip the forward blip.
        else
        {
          escBrakeCorrectionNeeded = 0;
          output_escBrakeCorrection = 0;
        }

        //hold output for the required time while overriding with a forward blip
        if (output_escBrakeCorrection)
        {
          escOverrideCommand = throttleNeutralUpperLimit;
          //updateESC(escCommand);
          if (millis() - commandSequenceTime > 90)//commandSequencePause)
          {
            escBrakeCorrectionNeeded = 0;
            output_escBrakeCorrection = 0;
            //commandSequenceTime = millis();
           
            
            Serial.println("ESCcorrected");
          }
        }
        
       
        
      }
    }

    escCommand = escOverrideCommand;
    updateESC(escCommand);
}


// ---- SOUND TRIGGERING      ---- //
// ------------------------------- //
// Trigger reverse and brake sounds

void throttleSoundTriggering (byte reverseGear, int throttleAxis)
{
    
    //Read throttleAxis and set flags.
    // |  brake    | neutral | forward
    // | reverse   |
    //-------------------------------------------------------------------------------
    byte forwardFlag = 0, backFlag = 0, reverseFlag = 0, neutralFlag = 0; //delete reverseFlag
    
    //NOT COMPATIBLE WITH REVERSED THROTTLE. HIGHER VALUE FOR FORWARD ONLY!
    //else //if not reversed
    {
        if (throttleAxis > throttleNeutralUpperLimit)
        forwardFlag = 1;
        

        else if (throttleAxis < throttleNeutralLowerLimit){
        backFlag = 1;
        } 
        
        else //if (throttleAxis < throttleNeutralUpperLimit && throttleAxis > throttleNeutralLowerLimit)
        neutralFlag = 1;
    }

    // --- Determine brake and reverse for sound triggering ---
    if (reverseGear)
    {
      escInReverse = 1;         
      if (backFlag)
        escIsBraking = 0; 
      if (neutralFlag)
        escIsBraking = 0;
      if (pulseWidth[2] < throttleNeutralLowerLimit)
        escIsBraking = 1;    
    }
    else
    {
      //Serial.print("Rev:0, ");
      escInReverse = 0; ;//turn off light and beep
      if (backFlag)
      {
        //Serial.print("back:1, ");
        escIsBraking = 1; 
      }
      if (neutralFlag)
        escIsBraking = 0;
      if (forwardFlag)
        escIsBraking = 0;   
    }

    //large air noise when releasing brakes
    static byte wasBraking = 0;

    if (escIsBraking)
      wasBraking = 1;
    if (wasBraking && !escIsBraking)
    {
      Serial.println("----ptsssshhhhhh");
      airBrakeTrigger = 1;
      wasBraking = 0;
    }

    //Small airpuff when applying brakes
    static byte wasNotBraking = 0;

    if (!escIsBraking)
      wasNotBraking = 1;
    if (wasNotBraking && escIsBraking)// && !escInReverse)
    {
      Serial.println("----piiew");
      //airBrakeTrigger = 1;
      //airPuffTrigger = 1;
      wasNotBraking = 0;
    }
    //Serial.printf("back:%d, neutral:%d, fwd:%d, - brk: %d\n",backFlag,neutralFlag,forwardFlag,escIsBraking);
}



//
//================================================================
//  SHORTCUTS FOR ESC AND SERVO PIN OUTPUTS
//================================================================
// -W


//updateESC(escCommand);
void updateESC (int escCommand)
{
  escSignal = map(escCommand, 1000, 2000, 3278, 6553); // 1 - 2ms (5 - 10% pulsewidth of 65534)
  escOut.pwm(escSignal);
  return;
}

//update(escCommand);
void updateCH2 (int CH2Command)
{
  int ch2Signal = map(CH2Command, 1000, 2000, 3278, 6553); // 1 - 2ms (5 - 10% pulsewidth of 65534)
  ch2Out.pwm(ch2Signal);
  return;
}

//updateESC(escCommand);
void updateCH3 (int CH3Command)
{
  int ch3Signal = map(CH3Command, 1000, 2000, 3278, 6553); // 1 - 2ms (5 - 10% pulsewidth of 65534)
  ch3Out.pwm(ch3Signal);
  return;
}
