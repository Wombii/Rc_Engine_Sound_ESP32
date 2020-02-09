void buttonSetupCalibration (void){
  //TTGO_DISPLAY: GPIO0 and GPIO35 buttons
  //Hold Left turn signal button on interface panel during power up to get here

  //Sets throttle and steering directions, sends radio setup variables to sound module.

  //release button
  //hold full throttle, click indicated button
  //hold left steering, click indicated button
  //click indicated button to finish. Sound module is then updated.

  static byte buttonSetupMenuSelection = 0;
  
  // TODO: neutralUpperOffset, neutralLowerOffset
  //move throttlefull here static?
  HUMANSERIAL.println("calibration");

  throttleAxis = pulseWidth[2];

  switch (buttonSetupMenuSelection)
  {
    case 0:
      while(digitalRead(35) == LOW)
      {
         //HUMANSERIAL.println(digitalRead(diagSwitchArray[7]));
         HUMANSERIAL.println("release");
         //flash cross
         #if defined TFT_DISPLAY
          tft.setCursor(0, 0, 2);
          tft.println("Release to calibrate");
         #endif
      }
       
      buttonSetupMenuSelection = 1;
      break;

    case 1:
      HUMANSERIAL.println("full throttle");
      //flash full throttle
      #if defined TFT_DISPLAY
          //tft.setCursor(0, 0, 2);
          tft.println("Hold throttle full and click button");
      #endif
      
      if(digitalRead(35) == 0)
      {
        throttleFull = throttleAxis;
  
        if (throttleFull > throttleCenter)  { throttleAxisReversed = 0; }
        else                                { throttleAxisReversed = 1; }

        #if defined TFT_DISPLAY
          //tft.setCursor(0, 0, 2);
          tft.print(throttleFull);
          tft.print("  Reversed:");
          tft.println(throttleAxisReversed);
        #endif  
  
        buttonSetupMenuSelection = 2;
        //** specialtiming phase to 255?

      }
      break;
    
    case 2:
      HUMANSERIAL.println("neutral upper");

      #if defined TFT_DISPLAY
          //tft.setCursor(0, 0, 2);
          tft.println("Hold throttle at the point motor engages");
      #endif  

      if(digitalRead(35) == 0)
      {
        
        throttleNeutralUpperLimit = throttleAxis;

        neutralUpperOffset = abs(throttleNeutralUpperLimit - throttleCenter);
        neutralLowerOffset = neutralUpperOffset;
        buttonSetupMenuSelection = 3;

        #if defined TFT_DISPLAY
          //tft.setCursor(0, 0, 2);
          tft.print("Neutral Offset: ");
          tft.println(neutralUpperOffset);
        #endif 
        
        //** specialtiming phase to 255?

      }
      break;

    case 3:
      HUMANSERIAL.println("done?");

      #if defined TFT_DISPLAY
          //tft.setCursor(0, 0, 2);
          tft.println("Click to save...");
      #endif  

      if(digitalRead(35) == 0)
      {
        //flash cross 2 seconds

        //eeprom save reversed

        //soundModuleCalibrate();
        SavePreferences();
        //ESP32soundModuleCalibrate();

        #if defined TFT_DISPLAY
          //tft.setCursor(0, 0, 2);
          tft.println("OK");
        #endif 

      
        buttonSetupCalibrationActive = 0;
  
        buttonSetupMenuSelection = 0;
        //** specialtiming phase to 255?

      }
      
      
      break;

  }
      
}