void SetupFunctions (void)
{
  
  pinMode(27,INPUT_PULLDOWN); //GPIO 35 button on TTGO_display esp32 module

  pinMode(CH1_ESC_PIN,INPUT_PULLDOWN);  //Make sure ESC output pin stays low until we start
  pinMode(CH2_PIN,INPUT_PULLDOWN);
  pinMode(CH3_PIN,INPUT_PULLDOWN);

  //Start SBUS input serial (inverted). TX pin is set to 37, even though 37 is an input pin only, because we don't need TX on this serial.
  Serial2.begin(100000, SERIAL_8N1, SBUS_IN_PIN,37,true); //true = inverted serial
  //Start SBUS passthrough serial pin (uninverted), 
  Serial1.begin(100000, SERIAL_8N1, 12,SBUS_OUT_PIN);
  //Pull 27 to a LOW level to avoid having imaginary data coming in on the unconnected Serial1 (SBUS output serial) RX pin.
  pinMode(12,INPUT_PULLDOWN);
  
  //Serial.println("Wsetup()"); //debug print

  //Also output channel 2 and 3 directly to servos (from SBUS).
  ch2Out.begin(CH2_PIN, 2, 50, 16); // Timer 15, 50Hz, 16bit (experimental)
  updateCH2(map(SBUS.channels[2-1],0,2000,1000,2000));
  
  ch3Out.begin(CH3_PIN, 3, 50, 16); // Timer 15, 50Hz, 16bit (experimental)
  updateCH3(map(SBUS.channels[3-1],0,2000,1000,2000));
  
   
   // --- Read saved preferences from non-volatile storage ---
  //ReadSavedPreferences();

  //SavePreferences();


  //Start up lcd display on the TTGO-Display
  //#if defined TFT_DISPLAY
  #if defined TFT_DISPLAYtest
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(0x5AEB);//TFT_GREY);
  tft.setCursor(0, 60, 2);
  tft.println("ESP32 soundkit");
  #endif


  
  //Make sure currentRpmScaled is a sensible value so the sound interrupt doesn't crash if SBUS is too slow to initialize
  currentRpm = 0;
  currentRpmScaled = convertRPMtoInterval();


  if (!digitalRead(27))
  {
    OTAactive = 1;
    tft.setCursor(0, 80, 2);
    tft.println("ready for OTA");
  }



  //If button on 35 is held at boot prepare for Wifi OTA update instead of SBUS and sound interrupts
  if (OTAactive)
  {
    OTAsetup();

    #if defined TFT_DISPLAYtest
    
    tft.println("Hello!");
    #endif
  }
  else
  {
    Serial.println(SBUS.failsafe);
    //Serial.println(millis());
    //Wait for up to x milliseconds to get a full set of SBUS data and set throttle neutral zone
    while((SBUS.failsafe > 0) && (millis() < 10000))
    {
      //Serial.println(millis());
      SBUSinput();  //Should be called more frequently than the receiver sends a full data set.
                    //When a full data set is received, SBUS.channelsReady will be 1 or true and channels updated in the SBUS. struct.
    
      //if all channels are in and ready:
      if (SBUS.channelsReady)
      {
        //SBUSpreparechannels_M();  //convert buffer to channels. Now called directly from SBUSinput().
        SBUS.channelsReady = 0;     //reset the channelsReady flag.
    
        //Do stuff with the updated channel info:
        SBUSthrottle();             //copy throttle channel to pulseWidth[2]
        SBUSgear();
        //SBUSswitches();             //process horn and siren switches
        //When first starting, set throttle/ESC deadband.
        //SBUS.OK = 1;
        throttleCenter = pulseWidth[2];
        throttleNeutralUpperLimit = throttleCenter + neutralUpperOffset;
        throttleNeutralLowerLimit = throttleCenter - neutralLowerOffset;
        Serial.printf("THRcenter: %d, Deadzone: %d-%d\n",throttleCenter, throttleNeutralUpperLimit, throttleNeutralLowerLimit);
      }
    }
    Serial.println("SETUP POST");
    Serial.println(SBUS.failsafe);

    //Print startup values to display if TTGO-Display
    #if defined TFT_DISPLAYtest
    if (SBUS.failsafe == 0)
    {
      tft.println("SBUS OK");
      tft.printf("THRcenter: %d, \nDeadzone: %d-%d",throttleCenter, throttleNeutralUpperLimit, throttleNeutralLowerLimit);  
    }
    //tft.println("Hello!");
    //tft.printf("Failsafe status: %d\n",SBUS.failsafe);
    #endif
    
    
    
    
    
    
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

  }

  //Start ESC output @ throttleCenter. ESC initializes when it starts receiving pulses, and the first pulses are used to determine throttle neutral position.
  escOut.begin(CH1_ESC_PIN, 15, 50, 16); // Timer 15, 50Hz, 16bit (experimental)
  updateESC(throttleCenter);

  
  
}
