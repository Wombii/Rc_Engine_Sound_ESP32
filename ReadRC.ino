/*
//
// =======================================================================================================
// READ PPM MULTI CHANNEL COMMMANDS (compatible with many receivers)
// =======================================================================================================
//

void readPpmCommands() {
  pulseWidth[0] = valuesBuf[0]; // CH1 Steering
  pulseWidth[1] = 1500; // CH2
  pulseWidth[2] = valuesBuf[1]; // CH3 Throttle
  pulseWidth[3] = valuesBuf[2]; // Pot1 Horn

  // Invert RC signals
  invertRcSignals();

  // Falisafe for RC signals
  failsafeRcSignals();
}
*/

//
// =======================================================================================================
// READ PWM RC SIGNALS
// =======================================================================================================
//

void readRcSignals() {
  // measure RC signal pulsewidth:

  // CH1 Steering
  //if (indicators) pulseWidth[0] = pulseIn(SERVO1_PIN, HIGH, 50000);
  //else pulseWidth[0] = 1500;

  // CH2 (not used, gearbox servo)
  //pulseWidth[1] = pulseIn(SERVO2_PIN, HIGH, 50000);

  // CH3 Throttle
  pulseWidth[2] = pulseIn(SERVO3_PIN, HIGH, 50000);
  if (pulseWidth[2] == 0) failSafe = true; // 0, if timeout (signal loss)
  else failSafe = false;

  // CH4 Additional sound trigger (RC signal with 3 positions)
  //if (pwmSoundTrigger) pulseWidth[3] = pulseIn(SERVO4_PIN, HIGH, 50000);
  //else pulseWidth[3] = 1500;

  // Invert RC signals
  //invertRcSignals();

  // Falisafe for RC signals
  failsafeRcSignals();
}

//
// =======================================================================================================
// INVERT RC SIGNALS (if your signals are inverted)
// =======================================================================================================
//

void invertRcSignals() {
  if (INDICATOR_DIR) pulseWidth[0] = map(pulseWidth[0], 0, 3000, 3000, 0); // invert steering direction
}

//
// =======================================================================================================
// RC SIGNAL FAILSAFE POSITIONS (if serial signal lost)
// =======================================================================================================
//

void failsafeRcSignals() {

  // PPM signal surveillance (serial & PWM communication does not need any actions here) --------
#if defined PPM_COMMUNICATION
  static unsigned long ppmFailsafeMillis;

  if (millis() - ppmFailsafeMillis > 50) { // Every 50ms
    ppmFailsafeMillis = millis();

    if (ppmFailsafeCounter < 10) ppmFailsafeCounter ++ ; //it will be reset in the ppm interrupt
  }
  if (ppmFailsafeCounter > 5) failSafe = true;
#endif

  // Failsafe actions --------
  if (failSafe) pulseWidth[2] = pulseZero[2]; // Throttle to zero position!
}
