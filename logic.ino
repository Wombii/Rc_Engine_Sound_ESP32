//SBUS channels

 #define channelTurnSignals       4
 #define channelEMFLashers        10 //9
 #define channelHeadlights        5 //6
 #define channelHeadlightstoggle  6 //3
 #define channelFullBeam2         7
 #define channelFloodLights       8 //11
 #define channelIgnition          9 //8
 #define channelAmberflash        11
 #define channelAudioSwitch       12 //14

 byte ignitionState = 0;
 byte sirenNumber = 0;

void logicstuff()
{

    // ---- SETTING FLAGS ---- //
    // ----------------------- //

    //Read throttleAxis and set flags. Also check flag for reversed throttle channel.
    // |  brake    | neutral | forward
    // | reverse   |
    //-------------------------------------------------------------------------------
    byte forwardFlag = 0, brakeFlag = 0, reverseFlag = 0, neutralFlag = 0; 

    throttleAxis = pulseWidth[2];

    if (throttleAxisReversed)
    {
        if (throttleAxis < throttleNeutralLowerLimit)
        forwardFlag = 1;
        
        else if (throttleAxis > throttleNeutralUpperLimit){
        brakeFlag = 1;
        reverseFlag = 1;
        }  
        
        else //if (throttleAxis < throttleNeutralUpperLimit && throttleAxis > throttleNeutralLowerLimit)
        neutralFlag = 1;

    }
    else //if not reversed
    {
        if (throttleAxis > throttleNeutralUpperLimit)
        forwardFlag = 1;
        

        else if (throttleAxis < throttleNeutralLowerLimit){
        brakeFlag = 1;
        reverseFlag = 1; 
        } 
        
        else //if (throttleAxis < throttleNeutralUpperLimit && throttleAxis > throttleNeutralLowerLimit)
        neutralFlag = 1;
    }

    // --- USING FLAGS --- //
    // ------------------- //

    //Enable or disable reverselights and brakelights based on axis flags.
    //--------------------------------------------------------------------
    if (forwardFlag){
      //Serial.println("FWD");
      //reverseLight = 0;
      escInReverse = 0;
      escIsBraking = 0;
      //brakeLight = 0;
    }

    if (neutralFlag){
      //Serial.println("N");
      escIsBraking = 0;
      //brakeLight = 0;
    }

    if (brakeFlag){
      //Serial.println("BRK");
      escIsBraking = 1;
      //brakeLight = 1;
    }

    //Reverse logic
    //-------------------------------
    //Set reverseType2 to match your esc. 1 is double pump reverse, 0 is time delay reverse.
    static byte reverseFlag2 = 0;
    
    //Double pump reverse
    if (reverseType2){
        static byte reverseFlagCount = 0;
        static byte lastWasReverseFlag = 0;
        if (reverseFlag)// && !lastReverseFlag)
        {
            if (lastWasReverseFlag == 0){
            reverseFlagCount++;
            lastWasReverseFlag =1;
            }
        }
        else // if reverseflag
            lastWasReverseFlag = 0;
        if (forwardFlag)
            reverseFlagCount = 0;
        if (reverseFlagCount >= 2){
            //Serial.println("rev");
            reverseFlagCount = 2; //prevent overflow
            //reverseLight = 1;
            //brakeLight = 0;
            //reverseFlag2 = 1;
            escInReverse = 1;
            escIsBraking = 0;
            //Serial.println("REV");
        }
    }

    //Delayed reverse
    //reverseDelayTicks is a number of loops corresponding to the time delay for reverse activation
    else
    {   
        static byte reverseFlagCount = 0;
        if (reverseFlag)
        {
            reverseFlagCount++;
            if (reverseFlagCount > reverseDelayTicks){
                //reverseLight = 1;
                escInReverse = 1;
                //brakeLight = 0;
                escIsBraking = 0;
                reverseFlagCount = reverseDelayTicks; //prevent overflow
                }
        }
        else
        {
            reverseFlagCount = 0;
            //reverseLight = 0;
        }
    } 

    //Brake logic
    //----------------------

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

    //large air noise when releasing brakes (actually when going reverse -> forward)
    static byte wasReversing = 0;

    if (escInReverse)
      wasReversing = 1;
    if (wasReversing && forwardFlag)
    {
      Serial.println("----ptsssshhhhhh");
      airBrakeTrigger = 1;
      wasReversing = 0;
    }
/*
    static byte wasReversing2 = 0;

    if (escInReverse)
      wasReversing2 = 1;
    if (wasReversing2 && !reverseFlag)
    {
      Serial.println("----piiew");
      airPuffTrigger = 1;
      wasReversing2 = 0;
    }

*/
    //Small airpuff when applying brakes
    static byte wasNotBraking = 0;

    if (!escIsBraking)
      wasNotBraking = 1;
    if (wasNotBraking && escIsBraking && !escInReverse)
    {
      Serial.println("----piiew");
      //airBrakeTrigger = 1;
      airPuffTrigger = 1;
      wasNotBraking = 0;
    }


    

    
}

void SBUSthrottle (void){
  pulseWidth[2] = map(SBUS.channels[0],0,2000,1000,2000);
  
}

void SBUSswitches (void){
    
    // ----  ignition switch  ---- //
    // --------------------------- //

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


    //Horn and siren with latching transmitter switches
    //One channel split into 4 events. off / horn / horn + siren / siren
    if (SBUS.channels[channelAudioSwitch-1] < 700)      
    {
      hornSwitch = 0;
      sirenSwitch = 0;  
    }
    else if(SBUS.channels[channelAudioSwitch-1] > 700 && SBUS.channels[channelAudioSwitch-1] < 1200) 
    { 
      hornSwitch = 1;
      sirenSwitch = 0;
    }
    else if(SBUS.channels[channelAudioSwitch-1] > 1200 && SBUS.channels[channelAudioSwitch-1] < 1700) 
    {
      hornSwitch = 1;
      sirenSwitch = 1;
    }
    else
    {
      hornSwitch = 0;
      sirenSwitch = 1;
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

void serialSwitches (void)
{
  sirenSwitch = sirenAxis;
  hornSwitch = hornAxis;
  engineOn = ignitionAxis;
}



void audioLogic (void)
{
  if (ignitionState == 2)
    {
      engineOn = 1;
      sirenOn = sirenSwitch;
      hornOn = hornSwitch;
    }
    else if (ignitionState == 0)
    {
      sirenOn = 0;
      hornOn = 0;
    }
    else
    {
      engineOn = 0;
    }
}

void sirenTimerSwitch (void)
{
  static unsigned long sirenTime = 0;
  //static byte sirenNumber = 0;
  if (millis() - sirenTime >5000)
  {
    sirenNumber ^= 1;
    sirenTime = millis();
  }

  soundNo = 1+sirenNumber;  // 1 = siren
}


//
// =======================================================================================================
// HORN TRIGGERING, SIREN TRIGGERING, SOUND1 TRIGGERING BY CH4 (POT)
// =======================================================================================================
//

void triggerHorn() {
  if (pwmSoundTrigger) { // PWM RC signal mode --------------------------------------------

    // detect horn trigger ( impulse length > 1700us) -------------
    if (hornAxis){//pulseWidth[3] > (pulseMaxNeutral[3] + 180) && pulseWidth[3] < pulseMaxLimit[3]) {
      hornSwitch = true;
      //sirenSwitch = false;
      soundNo = 4;  // 0 = horn
    }
    else hornSwitch = false;

    // detect siren trigger ( impulse length < 1300us) ----------
    if (sirenAxis){//pulseWidth[3] < (pulseMinNeutral[3] - 180) && pulseWidth[3] > pulseMinLimit[3]) {
      sirenSwitch = true;
      //hornSwitch = false;
      
      static unsigned long sirenTime = 0;
      static byte sirenNumber = 0;
      if (millis() - sirenTime >5000)
      {
        sirenNumber ^= 1;
        sirenTime = millis();
      }

      soundNo = 1+sirenNumber;  // 1 = siren
    }
    else sirenSwitch = false;

    // Sound 1 triggered via momentary1 button (Micro RC in serial mode only) ---------
    if (momentary1  && !hornSwitch  && !sirenSwitch) {
      sound1Switch = true;
      soundNo = 0; // 2 = sound1
    }
    else sound1Switch = false;

  }
  else { // High level triggering mode ---------------------------------------------------

    // detect horn trigger (constant high level)
    if (digitalRead(SERVO4_PIN)) {
      hornSwitch = true;
      soundNo = 4;  // 0 = horn
    }
    else hornSwitch = false;
  }

  // Latches (required to prevent sound seams from popping) --------------------------------

  if (hornSwitch) {
    //hornOn = true;
    sirenOn = false;
    sound1On = false;
  }
  if (sirenSwitch) {
    sirenOn = true;
    //hornOn = false;
    sound1On = false;
  }
  if (sound1Switch) {
    sound1On = true;
    sirenOn = false;
    //hornOn = false;
  }
}

//
// =======================================================================================================
// INDICATOR (TURN SIGNAL) TRIGGERING BY CH1 (STEERING)
// =======================================================================================================
//
/*
void triggerIndicators() {

  // detect left indicator trigger ( impulse length > 1700us) -------------
  if (pulseWidth[0] > (pulseMaxNeutral[0] + 30) && pulseWidth[0] < pulseMaxLimit[0]) indicatorLon = true;
  if (pulseWidth[0] < pulseMaxNeutral[0]) indicatorLon = false;


  // detect right indicator trigger ( impulse length < 1300us) ----------
  if (pulseWidth[0] < (pulseMinNeutral[0] - 30) && pulseWidth[0] > pulseMinLimit[0]) indicatorRon = true;
  if (pulseWidth[0] > pulseMinNeutral[0]) indicatorRon = false;
}
*/
//
// =======================================================================================================
// MAP PULSEWIDTH TO THROTTLE CH3
// =======================================================================================================
//

void mapThrottle() {

  static unsigned long reversingMillis; // TODO

  // Input is around 1000 - 2000us, output 0-500 for forward and backwards

  // check if the pulsewidth looks like a servo pulse
  if (pulseWidth[2] > pulseMinLimit[2] && pulseWidth[2] < pulseMaxLimit[2]) {
    if (pulseWidth[2] < pulseMin[2]) pulseWidth[2] = pulseMin[2]; // Constrain the value
    if (pulseWidth[2] > pulseMax[2]) pulseWidth[2] = pulseMax[2];

    // calculate a throttle value from the pulsewidth signal
    if (pulseWidth[2] > pulseMaxNeutral[2]) {
      currentThrottle = map(pulseWidth[2], pulseMaxNeutral[2], pulseMax[2], 0, 500);
      throttleReverse = false;
    }
    else if (pulseWidth[2] < pulseMinNeutral[2]) {
      currentThrottle = map(pulseWidth[2], pulseMinNeutral[2], pulseMin[2], 0, 500);
      throttleReverse = true;
    }
    else {
      currentThrottle = 0;
    }
  }

  // Calculate throttle dependent engine volume
  if (!escIsBraking && engineRunning) throttleDependentVolume = map(currentThrottle, 0, 500, engineIdleVolumePercentage, 100);
  else throttleDependentVolume = engineIdleVolumePercentage;

  // Calculate engine rpm dependent turbo volume
  if (!escIsBraking && engineRunning) throttleDependentTurboVolume = map(currentRpm, 0, 500, turboIdleVolumePercentage, 100);
  else throttleDependentTurboVolume = turboIdleVolumePercentage;

  // reversing sound trigger signal (TODO)
  /*if (reverseSoundMode == 1) {
    if (pulseWidth[2] <= pulseMaxNeutral[2]) {
      reversingMillis = millis();
    }

    if (millis() - reversingMillis > 200) {
      reversingSoundOn = true;
    }
    else reversingSoundOn = false;
    }

    if (reverseSoundMode == 2) {
    if (pulseWidth[2] >= pulseMinNeutral[2]) {
      reversingMillis = millis();
    }

    if (millis() - reversingMillis > 200) {
      reversingSoundOn = true;
    }
    else reversingSoundOn = false;
    }

    if (reverseSoundMode == 0) {
    reversingSoundOn = false;
    }*/
}


//
// =======================================================================================================
// Throttle Calculations. Curves, mass simulation, scaling and converting to interval -W split up
// =======================================================================================================
// Input the mapped throttle value (0-500), modify, output scaled interrupt interval.
// W: Split it up into separate functions to easily enable or disable specific items.

void throttleCalculations(int32_t tempThrottle)
{
  //static int32_t  tempThrottle = 0;
  static unsigned long throtMillis;
  static unsigned long printMillis;

  if (millis() - throtMillis > 2) { // Every 2ms
    throtMillis = millis();

    tempThrottle = rpmCurves(tempThrottle);                   //shift points or linear
    tempThrottle = massSim(tempThrottle);                     //Mass simulation
    currentRpmScaled = convertRPMtoInterval(tempThrottle);    //scale to interval

  }
}
    

int32_t rpmCurves(int32_t curThrottle)
{
  int32_t mappedThrottle = 0;
  // compute rpm curves
  if (shifted) mappedThrottle = reMap(curveShifting, curThrottle);
  else mappedThrottle = reMap(curveLinear, curThrottle);
  return mappedThrottle;
}

int32_t massSim(int32_t mappedThrottle)
{
  //int acc = 3;
  // Accelerate engine
    if (mappedThrottle > (currentRpm + acc) && (currentRpm + acc) < maxRpm && engineState == 2 && !escIsBraking && engineRunning) {
      if (!airBrakeTrigger) { // No acceleration, if brake release noise still playing
        currentRpm += acc;
        if (currentRpm > maxRpm) currentRpm = maxRpm;
      }
    }

    // Decelerate engine
    if (mappedThrottle < currentRpm || escIsBraking) {
      currentRpm -= dec;
      if (currentRpm < minRpm) currentRpm = minRpm;
    }
    return currentRpm;
}

uint32_t convertRPMtoInterval(int32_t currentRpm)
{
  // Speed (sample rate) output
  return map(currentRpm, minRpm, maxRpm, maxSampleInterval, minSampleInterval);
}





//
// =======================================================================================================
// ENGINE MASS SIMULATION
// =======================================================================================================
// W: Edited to accept throttle value when calling

uint32_t engineMassSimulation() {

  static int32_t  mappedThrottle = 0;
  static unsigned long throtMillis;
  static unsigned long printMillis;

  if (millis() - throtMillis > 2) { // Every 2ms
    throtMillis = millis();

    // compute rpm curves
    if (shifted) mappedThrottle = reMap(curveShifting, currentThrottle);
    else mappedThrottle = reMap(curveLinear, currentThrottle);


    // Accelerate engine
    if (mappedThrottle > (currentRpm + acc) && (currentRpm + acc) < maxRpm && engineState == 2 && !escIsBraking && engineRunning) {
      if (!airBrakeTrigger) { // No acceleration, if brake release noise still playing
        currentRpm += acc;
        if (currentRpm > maxRpm) currentRpm = maxRpm;
      }
    }

    // Decelerate engine
    if (mappedThrottle < currentRpm || escIsBraking) {
      currentRpm -= dec;
      if (currentRpm < minRpm) currentRpm = minRpm;
    }


    // Speed (sample rate) output
    currentRpmScaled = map(currentRpm, minRpm, maxRpm, maxSampleInterval, minSampleInterval);
    //return map(currentRpm, minRpm, maxRpm, maxSampleInterval, minSampleInterval);
  }

  // Brake light trigger TODO
  /*if (mappedThrottle < (currentRpm - 200)) slowingDown = true;
    if (mappedThrottle >= (currentRpm - 10)) slowingDown = false;*/

  // Print debug infos
#ifdef DEBUG // can slow down the playback loop!
  if (millis() - printMillis > 1000) { // Every 1000ms
    printMillis = millis();

    Serial.println("CH1");
    Serial.println(pulseWidth[0]);
    Serial.println(pulseMinNeutral[0]);
    Serial.println(pulseMaxNeutral[0]);
    Serial.println("CH2");
    Serial.println(pulseWidth[1]);
    Serial.println(pulseMinNeutral[1]);
    Serial.println(pulseMaxNeutral[1]);
    Serial.println("CH3");
    Serial.println(pulseWidth[2]);
    Serial.println(pulseMinNeutral[2]);
    Serial.println(pulseMaxNeutral[2]);
    Serial.println("CH4");
    Serial.println(pulseWidth[3]);
    Serial.println(pulseMinNeutral[3]);
    Serial.println(pulseMaxNeutral[3]);
    Serial.println(" ");
    /*Serial.println(currentThrottle);
    Serial.println(mappedThrottle);
    Serial.println(currentRpm);
    Serial.println(currentRpmScaled);
    Serial.println(engineState);
    Serial.println(" ");
    Serial.println(loopTime);
    Serial.println(" ");
    Serial.println(airBrakeTrigger);
    Serial.println(EngineWasAboveIdle);
    Serial.println(throttleDependentVolume);
    Serial.println(sound1On);
    Serial.println(soundNo);
    Serial.print("PPM Failsafe Counter ");
    Serial.println(ppmFailsafeCounter);
    Serial.print("failSafe ");
    Serial.println(failSafe);*/

  }
#endif
}

//
// =======================================================================================================
// SWITCH ENGINE ON OR OFF, AIR BRAKE TRIGGERING
// =======================================================================================================
//

void engineOnOff() {

  static unsigned long pulseDelayMillis;
  static unsigned long idleDelayMillis;

  if (engineManualOnOff) { // Engine manually switched on or off depending on presence of servo pulses
    if (pulseAvailable) pulseDelayMillis = millis(); // reset delay timer, if pulses are available

    if (millis() - pulseDelayMillis > 100) {
      engineOn = false; // after delay, switch engine off
    }
    else engineOn = true;
  }

  else { // Engine automatically switched on or off depending on throttle position and 15s delay timne
    if (currentThrottle > 80 || driveState != 0) idleDelayMillis = millis(); // reset delay timer, if throttle not in neutral

    if (millis() - idleDelayMillis > 15000) {
      engineOn = false; // after delay, switch engine off
    }

    if (millis() - idleDelayMillis > 10000) {
      lightsOn = false; // after delay, switch light off
    }

    // air brake noise trigggering TODO
    /*if (millis() - idleDelayMillis > 1000) {
      if (EngineWasAboveIdle) {
        airBrakeTrigger = true; // after delay, trigger air brake noise
      }
      }*/

    // Engine start detection
    if (currentThrottle > 100 && !airBrakeTrigger) {
      engineOn = true;
      lightsOn = true;
      EngineWasAboveIdle = true;
    }
  }
}
