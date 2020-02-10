
//
// =======================================================================================================
// LED
// =======================================================================================================
//
/*
void led() {

  // Reversing light ----
  //if (reversingSoundOn) reversingLight.on();
  if (engineRunning && escInReverse) reversingLight.on();
  else reversingLight.off();

  // Beacons (blue light) ----
  if (sirenOn) {
    if (doubleFlashBlueLight) {
      beaconLight2.flash(30, 80, 380, 2); // Simulate double flash lights
      beaconLight1.flash(30, 80, 400, 2); // Simulate double flash lights
    }
    else {
      beaconLight2.flash(30, 400, 0, 0); // Simulate rotating beacon lights with short flashes
      beaconLight1.flash(30, 420, 0, 0); // Simulate rotating beacon lights with short flashes
    }
  }
  else {
    beaconLight2.off();
    beaconLight1.off();
  }

  // Headlights, tail lights ----
  if (lightsOn) {
    headLight.on();
    //if (slowingDown) tailLight.on();  // Brake lights (full brightness) TODO
    if (escIsBraking) tailLight.on();  // Brake lights (full brightness)
    else tailLight.pwm(50); // Taillights (reduced brightness)
  }
  else {
    headLight.off();
    tailLight.off();
  }

  if (!hazard) {
    // Indicators (turn signals, blinkers) ----
    if (indicatorLon) {
      if (indicatorL.flash(375, 375, 0, 0)) indicatorSoundOn = true; // Left indicator
    }
    else indicatorL.off();

    if (indicatorRon) {
      if (indicatorR.flash(375, 375, 0, 0)) indicatorSoundOn = true; // Right indicator
    }
    else indicatorR.off();
  }
  else { // Hazard lights on, if no connection to transmitter (serial control mode only)
    if (indicatorL.flash(375, 375, 0, 0)) indicatorSoundOn = true;
    indicatorR.flash(375, 375, 0, 0);
  }

  // Foglights (serial control mode only) ----
  if (lightsOn && !mode2) fogLight.on();
  else fogLight.off();

  // Roof lights (serial control mode only) ----
  if (lightsOn && !mode1) roofLight.on();
  else roofLight.off();

  // Sidelights ----
  if (engineOn) sideLight.on();
  else sideLight.off();

}

//
// =======================================================================================================
// SHAKER (simulates engine vibrations)
// =======================================================================================================
//

void shaker() {
  int32_t shakerRpm;

  // Set desired shaker rpm
  if (engineRunning) shakerRpm = map(currentRpm, minRpm, maxRpm, shakerIdle, shakerFullThrottle);
  if (engineStart) shakerRpm = shakerStart;
  if (engineStop) shakerRpm = shakerStop;

  // Shaker on
  if (engineRunning || engineStart || engineStop) shakerMotor.pwm(shakerRpm);
  else shakerMotor.off();
}


//
// =======================================================================================================
// ESC CONTROL
// =======================================================================================================
//

// If you connect your ESC to pin 33, the vehicle inertia is simulated. Direct brake (crawler) ESC required
// *** WARNING!! Do it at your own risk!! There is a falisafe function in case, the signal input from the
// receiver is lost, but if the ESP32 crashes, the vehicle could get out of control!! ***

void esc() {
  static uint32_t escPulseWidth = 1500;
  static uint32_t escSignal;
  static unsigned long escMillis;
  static unsigned long lastStateTime;
  static int8_t pulse; // -1 = reverse, 0 = neutral, 1 = forward
  static int8_t escPulse; // -1 = reverse, 0 = neutral, 1 = forward
  static int8_t driveRampRate;
  static int8_t brakeRampRate;

  if (millis() - escMillis > escRampTime) { // About very 2 - 6ms
    escMillis = millis();

    // calulate throttle dependent brake steps
    brakeRampRate = map (currentThrottle, 0, 500, 1, escBrakeSteps);

    // Emergency ramp rates for falisafe
    if (failSafe) {
      brakeRampRate = escBrakeSteps;
      driveRampRate = escBrakeSteps;
    }
    else driveRampRate = 1;

    // Comparators
    if (pulseWidth[2] > pulseMaxNeutral[2] && pulseWidth[2] < pulseMaxLimit[2]) pulse = 1; // 1 = Forward
    else if (pulseWidth[2] < pulseMinNeutral[2] && pulseWidth[2] > pulseMinLimit[2]) pulse = -1; // -1 = Backwards
    else pulse = 0; // 0 = Neutral

    if (escPulseWidth > pulseMaxNeutral[2] && escPulseWidth < pulseMaxLimit[2]) escPulse = 1; // 1 = Forward
    else if (escPulseWidth < pulseMinNeutral[2] && escPulseWidth > pulseMinLimit[2]) escPulse = -1; // -1 = Backwards
    else escPulse = 0; // 0 = Neutral

#ifdef DRIVE_STATE_DEBUG
    if (millis() - lastStateTime > 300) { // Print the data every 300ms
      lastStateTime = millis();
      Serial.println(driveState);
      Serial.println(pulse);
      Serial.println(escPulse);
      Serial.println(escPulseMin);
      Serial.println(escPulseMax);
      Serial.println(brakeRampRate);
      Serial.println("");
    }
#endif

    // Drive state state machine
    switch (driveState) {

      case 0: // Standing still ---------------------------------------------------------------------
        escIsBraking = false;
        escInReverse = false;
        escPulseWidth = pulseZero[2];  // ESC to neutral position

        if (pulse == 1 && engineRunning) driveState = 1; // Driving forward
        if (pulse == -1 && engineRunning) driveState = 3; // Driving backwards
        break;

      case 1: // Driving forward ---------------------------------------------------------------------
        escIsBraking = false;
        escInReverse = false;
        if (escPulseWidth < pulseWidth[2]) escPulseWidth += driveRampRate;
        if (escPulseWidth > pulseWidth[2] && escPulseWidth > pulseZero[2]) escPulseWidth -= driveRampRate;

        if (pulse == -1 && escPulse == 1) driveState = 2; // Braking forward
        if (pulse == 0 && escPulse == 0) driveState = 0; // standing still
        break;

      case 2: // Braking forward ---------------------------------------------------------------------
        escIsBraking = true;
        escInReverse = false;
        if (escPulseWidth > pulseZero[2]) escPulseWidth -= brakeRampRate; // brake with variable deceleration

        if (pulse == 0 && escPulse == 1) {
          driveState = 1; // Driving forward
          airBrakeTrigger = true;
        }
        if (pulse == 0 && escPulse == 0) {
          driveState = 0; // standing still
          airBrakeTrigger = true;
        }
        break;

      case 3: // Driving backwards ---------------------------------------------------------------------
        escIsBraking = false;
        escInReverse = true;
        if (escPulseWidth > pulseWidth[2]) escPulseWidth -= driveRampRate;
        if (escPulseWidth < pulseWidth[2] && escPulseWidth < pulseZero[2]) escPulseWidth += driveRampRate;

        if (pulse == 1 && escPulse == -1) driveState = 4; // Braking backwards
        if (pulse == 0 && escPulse == 0) driveState = 0; // standing still
        break;

      case 4: // Braking backwards ---------------------------------------------------------------------
        escIsBraking = true;
        escInReverse = true;
        if (escPulseWidth < pulseZero[2]) escPulseWidth += brakeRampRate; // brake with variable deceleration

        if (pulse == 0 && escPulse == -1) {
          driveState = 3; // Driving backwards
          airBrakeTrigger = true;
        }
        if (pulse == 0 && escPulse == 0) {
          driveState = 0; // standing still
          airBrakeTrigger = true;
        }
        break;

    } // End of state machine


    // ESC control
    escSignal = map(escPulseWidth, escPulseMin, escPulseMax, 3278, 6553); // 1 - 2ms (5 - 10% pulsewidth of 65534)
    escOut.pwm(escSignal);
  }
}
*/
