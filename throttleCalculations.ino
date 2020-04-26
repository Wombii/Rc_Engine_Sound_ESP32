//
// =======================================================================================================
// Throttle Calculations. Curves, mass simulation, scaling and converting to interval -W split up
// =======================================================================================================
// These functions replace mapThrottle and engineMassSimulation functions.
// They do the same, but are split up in modules to more easily change behaviour and reuse calculation methods.

// Input the mapped throttle value (0-500), modify, output scaled interrupt interval.

// pulseWidth[2]    (global)  = raw channel input
// currentThrottle  (global)  = 0-500 map of channel input
// mappedThrottle             = 0-500 processed channel input (speedbased if clutch engaged)

// currentRpm       (global)  = output from mass sim
// currentRpmScaled (global)  = converted to interrupt interval


void throttleCalculationsGearSim(void)
{

  static int32_t tempThrottleVariable = 0;          //this is only static because mappedThrottle was static in mass simulation?
  static int32_t positiveThrottleVariable = 0;
  static unsigned long throtMillis;
  static unsigned long printMillis;


  if (millis() - throtMillis > 2) { // Every 2ms
    throtMillis = millis();

    positiveThrottleVariable = mapInputToThrottle2();                            // (input = pulseWidth[2], output = currentThrottle)

    // - global currentThrottle is now set - 
    
    //volumeCalculation();                            //volume calculation  Move to bottom? (input = currentThrottle)
    volumeCalculation3(currentGlobalEngineRPM,positiveThrottleVariable);                            //volume calculation  Move to bottom? (input = currentThrottle)
    
    //tempThrottleVariable = rpmCurves();             //Clutch logic (input = clutch + gear info, currentThrottle, currentSpeed, output = mappedThrottle)
    tempThrottleVariable = currentGlobalEngineRPM; //reMap(curveLinear, currentSpeed);
    massSim(tempThrottleVariable);                  //Mass simulation, slows down rpm changes (output = currentRpm)

    // - global currentRpm is now set -
    
    currentRpmScaled = convertRPMtoInterval();      //scale to interrupt interval for sound playback
    
    // - global currentRpmScaled is now set -

    //Experimental, revving sound.
    #ifdef REV_SOUND
      currentRevRpmScaled = convertRPMtoREVInterval(tempThrottle);
    #endif

  }


  //turboOverPressureTrigger();                     //turbo blow off valve (input: currentThrottle)
  //turboOverPressureTrigger2();                     //turbo blow off valve with timer (input: currentThrottle)
  turboOverPressureTrigger3(positiveThrottleVariable);
  turboOverPressureTrigger4(currentGlobalEngineRPM);
  
  // switch between idle and rev sound, depending on rpm
  #ifdef REV_SOUND  
    if (currentRpm > revSwitchPoint) engineRevving =true;
    else engineRevving = false;
  #endif

  //One line debug printing:
    //Serial.printf("CH3: %d, THR: %d, map: %d, rpm: %d, INT: %d \n",pulseWidth[2], currentThrottle, tempThrottleVariable, currentRpm, currentRpmScaled);
    //if (wastegateTrigger) Serial.println("BOV-----------------");

  
}

//Throttle calculations for input from mapThrottle().
// Call mapThrottle(); normally first, then throttleCalculations(currentThrottle);
void throttleCalculations(int32_t tempThrottle)
{
  //static int32_t  tempThrottle = 0;
  static unsigned long throtMillis;
  static unsigned long printMillis;

  
  if (millis() - throtMillis > 2) { // Every 2ms
    throtMillis = millis();

    tempThrottle = rpmCurves();                   //shift points or linear
    massSim(tempThrottle);                        //Mass simulation
    currentRpmScaled = convertRPMtoInterval();    //scale to interval

  

    //Experimental, revving sound.
    #ifdef REV_SOUND
      currentRevRpmScaled = convertRPMtoREVInterval(tempThrottle);
    #endif

  }

  turboOverPressureTrigger();                     //turbo blow off valve
  //turboOverPressureTrigger2();                     //turbo blow off valve with timer

  // switch between idle and rev sound, depending on rpm
  #ifdef REV_SOUND  
    if (currentRpm > revSwitchPoint) engineRevving =true;
    else engineRevving = false;
  #endif
}


//Throttle calculations for complete replacement of mapThrottle and mass simulation.
//Includes volume calculations from mapThrottle() function.

// pulseWidth[2]    (global)  = raw channel input
// currentThrottle  (global)  = 0-500 map of channel input
// mappedThrottle             = 0-500 processed channel input (speedbased if clutch engaged)

// currentRpm       (global)  = output from mass sim
// currentRpmScaled (global)  = converted to interrupt interval

void throttleCalculations2(void)
{

  int32_t tempThrottleVariable = 0;          //this is only static because mappedThrottle was static in mass simulation?
  static unsigned long throtMillis;
  static unsigned long printMillis;


  if (millis() - throtMillis > 2) { // Every 2ms
    throtMillis = millis();

    mapInputToThrottle();                           // (input = pulseWidth[2], output = currentThrottle)

    // - global currentThrottle is now set - 
    
    //volumeCalculation();                            //volume calculation  Move to bottom? (input = currentThrottle)
    //volumeCalculation2();                            //volume calculation  Move to bottom? (input = currentThrottle)
    
    tempThrottleVariable = rpmCurves();             //Clutch logic (input = clutch + gear info, currentThrottle, currentSpeed, output = mappedThrottle)
    //tempThrottleVariable = reMap(curveLinear, currentSpeed);
    massSim(tempThrottleVariable);                  //Mass simulation, slows down rpm changes (output = currentRpm)

    // - global currentRpm is now set -
    
    currentRpmScaled = convertRPMtoInterval();      //scale to interrupt interval for sound playback
    
    // - global currentRpmScaled is now set -

    //Experimental, revving sound.
    #ifdef REV_SOUND
      currentRevRpmScaled = convertRPMtoREVInterval(tempThrottle);
    #endif

  }

  //turboOverPressureTrigger();                     //turbo blow off valve (input: currentThrottle)
  turboOverPressureTrigger2();                     //turbo blow off valve with timer (input: currentThrottle)

  // switch between idle and rev sound, depending on rpm
  #ifdef REV_SOUND  
    if (currentRpm > revSwitchPoint) engineRevving =true;
    else engineRevving = false;
  #endif

  //One line debug printing:
    //Serial.printf("CH3: %d, THR: %d, map: %d, rpm: %d, INT: %d \n",pulseWidth[2], currentThrottle, tempThrottleVariable, currentRpm, currentRpmScaled);
    //if (wastegateTrigger) Serial.println("BOV-----------------");

  
}



// ---- SUB FUNCTIONS ---- //
// ----------------------- //


// ---- Map input to throttle ---- //

// Make a throttle value (0-500) from throttle input.
// + Override throttle value when manual shifting is active.
int32_t mapInputToThrottle2() {

    int curThrottle = 0;

  // Input is around 1000 - 2000us, output 0-500 for forward and backwards
  // check if the pulsewidth looks like a servo pulse

   /*
    curThrottle = abs(currentGlobalShaftRPM);
    if (currentGlobalShaftRPM < 0 )
      throttleReverse = true;
    else
      throttleReverse = false;
    */
    
    
    // calculate a throttle value from the pulsewidth signal
    if (pulseWidth[2] > throttleCenter+1) {
      curThrottle = map(pulseWidth[2], throttleCenter+1, 2000, 0, 500);
      throttleReverse = false;
    }
    else if (pulseWidth[2] < throttleCenter-1) {
      curThrottle = map(pulseWidth[2], throttleCenter-1, 1000, 0, 500);
      throttleReverse = true;
    }
    else {
      //curThrottle = 0;
    }
  
  

  return curThrottle;

}


// Make a throttle value (0-500) from throttle input.
// + Override throttle value when manual shifting is active.
int32_t mapInputToThrottle() {

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

  // Auto throttle while gear shifting (synchronizing the Tamiya 3 speed gearbox)
  if (!escIsBraking && escIsDriving && shiftingAutoThrottle) {
    if (gearUpShiftingInProgress) currentThrottle = 0; // No throttle
    if (gearDownShiftingInProgress) currentThrottle = 500; // Full throttle
    currentThrottle = constrain (currentThrottle, 0, 500);
  }

  //return currentThrottle;

}



// --- VOLUME CALCULATION --- //


// Calculate sound volume, copied from mapThrottle()
void volumeCalculation3(int curRpm, int curThrottle)
{
    // Calculate throttle dependent engine idle volume
    // For automatic: proportional to rpm. + for shaftrpm: 0-30% added. + for throttle input: 30-50% added.
  //if (!escIsBraking && engineRunning) throttleDependentVolume = map(curThrottle, 0, 500, engineIdleVolumePercentage, 100);
  //else throttleDependentVolume = engineIdleVolumePercentage;


  // Calculate throttle dependent engine volume
    //Temp variables are necessary to prevent interrupt from using unconstrained values
  int tempVolume;
  int RPMDependentVolume = 100;
  int shaftRPMDependentVolume = 100;
  int loadDependentVolume = 100;
  int throttleInputDependentVolume = 100;

  int tempLoad = pulseWidth[2] - (throttleCenter + currentGlobalShaftRPM);

  if (!escIsBraking && engineRunning) 
  {
    //First calculate volume based on engine rpm. More volume at higher rpms.
    tempVolume = map(currentGlobalEngineRPM, 0, 350, engineIdleVolumePercentage, 100);
    RPMDependentVolume = constrain(tempVolume,engineIdleVolumePercentage, 100);

    //Calculate volume based on speed. More volume at higher speeds.
    tempVolume = map(currentGlobalShaftRPM, 0, 300, 80, 100);
    //shaftRPMDependentVolume = constrain(tempVolume,80, 100);

    //Lower volume based on throttle input to reduce volume when dropping throttle.
    //tempVolume = map(curThrottle, 0, 1, 50, 100);
    //throttleInputDependentVolume = constrain(tempVolume,50, 100);

    //Add extra sound based on difference between throttle and speed to simulate more sound when accelerating harder.
    //tempVolume = map(curThrottle-currentGlobalShaftRPM, -20, 100, 50, 100);
    //loadDependentVolume = constrain(tempVolume,50, 100);

    //Cut sound by half when off throttle
    //tempVolume = map(tempLoad,-5,3,50,100);
    tempVolume = map(tempLoad,-30,0,1,75);

    //coast: 20,idle:75,full:100
    
    //Cut sound by half when idle
    //tempVolume = tempVolume * map(curThrottle,0,30,50,100);
    //tempVolume = map(tempVolume,50*50,100*100,50,100);
    //loadDependentVolume = constrain(tempVolume,50, 100);

    loadDependentVolume = constrain(tempVolume,30, 100);

    if (escInReverse){
      RPMDependentVolume = engineIdleVolumePercentage;
      loadDependentVolume = constrain(tempVolume,30, 100);
    }
    
    
    //Calculate combined volume. Multiplying the values ensures volume is cut when releasing throttle.
    tempVolume = RPMDependentVolume * shaftRPMDependentVolume / 100 * loadDependentVolume / 100 * throttleInputDependentVolume/100;
    throttleDependentVolume = constrain(tempVolume,10, 100);

    //if (escInReverse)
    //  throttleDependentVolume = engineIdleVolumePercentage;
    
  }
  else throttleDependentVolume = engineIdleVolumePercentage; //Quick fix:

  //Knock volume debug printing (Use serial plotter for graph)
  //Serial.printf("plotmaxY: 400, max: 100, curThr: %d, Load: %d, RPMV: %d, thrV: %d, sftV: %d, ldV: %d, totV: %d \n",curThrottle, tempLoad, RPMDependentVolume, throttleInputDependentVolume, shaftRPMDependentVolume, loadDependentVolume,throttleDependentVolume);

 //Knock volume debug printing (Use serial plotter for graph)
  //Serial.printf("plotmaxY: 600, max: 100, kRpm: %d kThr: %d kLoad: %d =kVol: %d, rpm: %d\n",throttleDependentKnockVolume1,throttleDependentKnockVolume2,throttleDependentKnockVolume3,throttleDependentKnockVolume,currentRpm);
 
  


  
  if (!escIsBraking && engineRunning) 
  {
    
    //First calculate volume based on rpm. More volume at higher rpms.
    tempVolume = map(currentGlobalEngineRPM, 100, 350, dieselKnockIdleVolumePercentage, 100);
    RPMDependentVolume = constrain(tempVolume,dieselKnockIdleVolumePercentage, 110);

    //Lower knock volume based on throttle input to reduce knock when dropping throttle.
    //tempVolume = map(currentThrottle, 0, 450, dieselKnockIdleVolumePercentage, 70);
    //throttleInputDependentVolume = constrain(tempVolume,dieselKnockIdleVolumePercentage, 100);

    //Add extra knock based on difference between throttle and speed to simulate more knock when accelerating harder.
    //tempVolume = map(currentThrottle-currentSpeed, 0, 500, 100, 500);
    //loadDependentVolume = constrain(tempVolume,100, 500);

    //Cut sound by half when off throttle
    tempVolume = map(tempLoad,-15,0,20,75);
    //Cut sound by half when idle
    tempVolume = tempVolume * map(curThrottle,0,30,50,100);
    tempVolume = map(tempVolume,50*50,100*100,50,100);
    loadDependentVolume = constrain(tempVolume,20, 100);
    
    //Calculate combined knock volume. Multiplying the values ensures knock volume is cut when releasing throttle.
    tempVolume = RPMDependentVolume * shaftRPMDependentVolume / 100 * loadDependentVolume / 100 * throttleInputDependentVolume/100;
    throttleDependentKnockVolume = constrain(tempVolume,dieselKnockIdleVolumePercentage, 100);

    if (escInReverse)
      throttleDependentKnockVolume = dieselKnockIdleVolumePercentage;
    
  }
  else throttleDependentKnockVolume = dieselKnockIdleVolumePercentage;

  




  // Calculate engine rpm dependent turbo volume
  // (tempLoad > -10)
  if (engineRunning && !escInReverse && tempLoad > -10) 
  {
    tempVolume = map(curRpm, 150, 350, turboIdleVolumePercentage, 100);
    throttleDependentTurboVolume = constrain(tempVolume,turboIdleVolumePercentage,100);
  }
    
  else throttleDependentTurboVolume = turboIdleVolumePercentage;

  // Calculate engine rpm dependent wastegate volume
  if (engineRunning && !escInReverse) throttleDependentWastegateVolume = map(curRpm, 0, 350, 30, 100);
  else throttleDependentWastegateVolume = wastegateIdleVolumePercentage;

  
}







// Calculate sound volume, copied from mapThrottle()
void volumeCalculation()
{
    // Calculate throttle dependent engine idle volume
  if (!escIsBraking && engineRunning) throttleDependentVolume = map(currentThrottle, 0, 500, engineIdleVolumePercentage, 100);
  else throttleDependentVolume = engineIdleVolumePercentage;

  // Calculate throttle dependent engine rev volume
  if (!escIsBraking && engineRunning) throttleDependentRevVolume = map(currentThrottle, 0, 500, engineRevVolumePercentage, 100);
  else throttleDependentRevVolume = engineRevVolumePercentage;

  // Calculate throttle dependent Diesel knock volume
    //Temp variables are necessary to prevent interrupt from using unconstrained values
  int throttleDependentKnockVolume1 = dieselKnockIdleVolumePercentage;
  int throttleDependentKnockVolume2 = dieselKnockIdleVolumePercentage;
  
  // Calculate throttle dependent Diesel knock volume
  if (!escIsBraking && engineRunning) 
  {
    int tempthrottleDependentKnockVolume = map(currentThrottle, 150, 500, dieselKnockIdleVolumePercentage, 100);
    throttleDependentKnockVolume = constrain(tempthrottleDependentKnockVolume,dieselKnockIdleVolumePercentage, 100);
  }
  else throttleDependentKnockVolume = dieselKnockIdleVolumePercentage;

 
  // Calculate engine rpm dependent turbo volume
  if (engineRunning) throttleDependentTurboVolume = map(currentRpm, 0, 500, turboIdleVolumePercentage, 100);
  else throttleDependentTurboVolume = turboIdleVolumePercentage;

  // Calculate engine rpm dependent wastegate volume
  if (engineRunning) throttleDependentWastegateVolume = map(currentRpm, 0, 500, wastegateIdleVolumePercentage, 100);
  else throttleDependentWastegateVolume = wastegateIdleVolumePercentage;
}




// ---- RPM CURVES ---- //


//RPM curves. Safe to skip except the new if(escIsBraking) part? Copied from engineMassSimulation();
// NEW: Clutch logic! Swaps between currentThrottle (input based) and currentSpeed (output, speed of truck)
int32_t rpmCurves(void)
{
    int32_t  mappedThrottle = 0;
    // compute rpm curves
    if (currentSpeed < clutchEngagingPoint || gearUpShiftingInProgress || gearDownShiftingInProgress) { // Clutch disengaged: Engine revving allowed during low speed
      if (shifted) mappedThrottle = reMap(curveShifting, currentThrottle);
      else mappedThrottle = reMap(curveLinear, currentThrottle);
      if (escIsBraking) mappedThrottle = 0;
    }
    else { // Clutch engaged: Engine rpm synchronized with ESC power (speed)
      if (shifted) mappedThrottle = reMap(curveShifting, currentSpeed);
      else mappedThrottle = reMap(curveLinear, currentSpeed);
    }
    return mappedThrottle;
}


// ---- MASS SIMULATION ---- //

//Mass simulation, copied from engineMassSimulation()
int32_t massSim(int32_t mappedThrottle)
{
    // Accelerate engine
    //if (mappedThrottle > (currentRpm + acc) && (currentRpm + acc) < maxRpm && engineState == 2 && !escIsBraking && engineRunning) {
    if (mappedThrottle > (currentRpm + acc) && (currentRpm + acc) < maxRpm && engineState == 2 && engineRunning) {
      if (!airBrakeTrigger) { // No acceleration, if brake release noise still playing
        currentRpm += acc;
        if (currentRpm > maxRpm) currentRpm = maxRpm;
      }
    }

    // Decelerate engine
    //if (mappedThrottle < currentRpm || escIsBraking) { // TODO
    if (mappedThrottle < currentRpm) {
      currentRpm -= dec;
      if (currentRpm < minRpm) currentRpm = minRpm;
    }

    //return currentRpm;
}


// ---- TURBO OVERPRESSURE RELEASE ---- //

//Dropping the throttle rapidly causes overpressure in turbo intake turbine,
// triggering the blow off valve or causing a fluttering sound.
void turboOverPressureTrigger ()
{
  // Trigger -Wastegate *Blow off valve, if throttle rapidly dropped
  static int32_t lastThrottle = 0;
  
  if (lastThrottle - currentThrottle > 200) {
    //if (lastThrottle > 400 && (lastThrottle - currentThrottle) > 200) {
    //if (lastThrottle > 400 && currentThrottle < 200) {
    wastegateTrigger = true;
  }
  lastThrottle = currentThrottle;

}

//Dropping the throttle rapidly causes overpressure in turbo intake turbine,
// triggering the blow off valve or causing a fluttering sound.
void turboOverPressureTrigger2 ()
{
  // Trigger -Wastegate *Blow off valve, if throttle rapidly dropped
  static int32_t lastThrottle = 0;
  static unsigned long lastThrottleTime = 0;

  //If the throttle drops y points in x ms
  if (millis() - lastThrottleTime > 60)  
  {
    if (lastThrottle - currentThrottle > 200) {
      //if (lastThrottle > 400 && (lastThrottle - currentThrottle) > 200) {
      //if (lastThrottle > 400 && currentThrottle < 200) {
      wastegateTrigger = true;
    }
    lastThrottle = currentThrottle;
    lastThrottleTime = millis();
  }
}

//Dropping the throttle rapidly causes overpressure in turbo intake turbine,
// triggering the blow off valve or causing a fluttering sound.
void turboOverPressureTrigger3 (int positiveThrottle)
{
  // Trigger -Wastegate *Blow off valve, if throttle rapidly dropped
  static int32_t lastThrottle = 0;
  static unsigned long lastThrottleTime = 0;

  //positiveThrottle = currentGlobalEngineRPM;

  //Serial.println(positiveThrottle);

  //If the throttle drops y points in x ms
  if (millis() - lastThrottleTime > 60)  
  {
    if (lastThrottle - positiveThrottle > 200) {
      //if (lastThrottle > 400 && (lastThrottle - currentThrottle) > 200) {
      //if (lastThrottle > 400 && currentThrottle < 200) {
      wastegateTrigger = true;
      Serial.print("-Wastegate");
    }
    lastThrottle = positiveThrottle;
    lastThrottleTime = millis();
  }
  

}

//Experimental: engine rpm based, to auto trigger on automatic gear shifts
void turboOverPressureTrigger4 (int positiveThrottle)
{
  // Trigger -Wastegate *Blow off valve, if throttle rapidly dropped
  static int32_t lastThrottle = 0;
  static unsigned long lastThrottleTime = 0;

  //positiveThrottle = currentGlobalEngineRPM;

  

  //If the throttle drops y points in x ms
  if (millis() - lastThrottleTime > 100)  
  {
    if (lastThrottle - positiveThrottle > 100) {
      //if (lastThrottle > 400 && (lastThrottle - currentThrottle) > 200) {
      //if (lastThrottle > 400 && currentThrottle < 200) {
      wastegateTrigger = true;
      //Serial.print("-Wastegate");
    }
    lastThrottle = positiveThrottle;
    lastThrottleTime = millis();
  }
  

}


// ---- RPM TO INTERRUPT INTERVAL ---- //

//Convert RPM to interrupt interval. Copied from engineMassSimulation()
uint32_t convertRPMtoInterval()
{
  // Speed (sample rate) output
  return map(currentRpm, minRpm, maxRpm, maxSampleInterval, minSampleInterval);
}

#ifdef REV_SOUND 
//Convert RPM to Revving sound interrupt interval. Copied from engineMassSimulation()
uint32_t convertRPMtoREVInterval()
{
  // Speed (sample rate) output
  return map(currentRpm, minRpm, maxRpm, maxSampleInterval, minRevSampleInterval); // Rev
}
#endif
