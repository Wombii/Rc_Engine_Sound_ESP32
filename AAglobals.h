//includes and definitions


#include <Preferences.h> //For non-volatile storage

/* create an instance of Preferences library */
Preferences preferences;


#define TFT_DISPLAY 1
#if defined TFT_DISPLAY
  #include <TFT_eSPI.h> // Graphics and font library for ILI9341 driver chip
  
  TFT_eSPI tft = TFT_eSPI();  // Invoke library
#endif

#define SBUSserial Serial2
#define HUMANSERIAL Serial


//SBUS channels
 #define channelThrottleESC       1
 #define channelThrottleAudio     11
 #define channelTurnSignals       4
 #define channelEMFLashers        10 //9
 #define channelHeadlights        5 //6
 #define channelHeadlightstoggle  6 //3
 #define channelFullBeam2         7
 #define channelFloodLights       8 //11
 #define channelIgnition          9 //8
 #define channelAmberflash        11
 #define channelAudioSwitch       12 //14

//GLOBAL VARIABLES


byte buttonSetupCalibrationActive = 0;

struct sbusdata
{
  unsigned int channels[18];
  uint8_t failsafe;
  byte channelsReady = 0;
  byte centerValuesSaved = 0;
  byte tempArray[25];
} SBUS;

struct remoteconfig
{
  int Neutral;
  int UpperNeutral;
  int LowerNeutral;
  int Max;
  int AxisReversed;
  int reverseType2;
} throttleSettings;

uint8_t inputArray[25] = { 0xF,0xFF,0xFB,0xDF,0xFF,0xFE,0xF7,0xBF,0xFF,0xFD,0xEF,0x7F,0xFF,0xFB,0xDF,0xFF,0xFE,0xF7,0xBF,0xFF,0xFD,0xEF,0x7F,0x9,0x0 };


// - W
int32_t throttleAxis;                                  // Temporary variables for serial command parsing
int32_t hornAxis;                                  
int32_t sirenAxis;
int32_t ignitionAxis = 1;


  byte throttleAxisReversed = 1;          //User setting. Overwritten by value stored in eeprom. Set in buttonSetupMenu.
  //byte steeringAxisReversed = 0;          //User setting. Overwritten by value stored in eeprom. Set in buttonSetupMenu.

  byte reverseType2 = 1;                  //User setting. Overwritten by value stored in eeprom, need a way to change it. Delayed or double pump reverse. 

  int neutralUpperOffset = 80;           //User setting. Overwritten by value stored in eeprom, need a way to change it. Dead band setting for throttle.
  int neutralLowerOffset = 80;           //User setting. Overwritten by value stored in eeprom, need a way to change it. Dead band setting for throttle.
  
  int throttleNeutralUpperLimit = 1440;   //Calculated on startup.
  int throttleNeutralLowerLimit = 1415;   //Calculated on startup.
  int throttleCenter = 1430;              //Recorded on startup.
  int throttleFull = 1800;                //Used for soundmodule? Set in buttonSetupMenu.

  //int steeringCenter = 1500;              //Recorded on startup. 

  byte reverseDelayTicks = 200;


  int currentGlobalEngineRPM = 2000;

// - 
