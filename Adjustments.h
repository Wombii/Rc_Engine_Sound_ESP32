/* ******* RECOMMENDED Audacity Settings: 22'050 Hz, 8 bit PCM **********

// Sound files converted with: https://bitluni.net/wp-content/uploads/2018/01/Audio2Header.html
// converter code by bitluni (send him a high five, if you like the code)

Recommended parts & settings for TAMIYA King Hauler:

ESC: HOBBYWING QUICRUN WP Crawler Brushed with the following settings:
1: 3
2: 1
3: 3
4: 3
5: 4
6: 2
7: 9
8: 1
9: 8 (change it, important)
10: 4
11: 4
12: 5
13: 4
14: 1 (be careful here!!)
15: 1 (change it, important)

Motor: 540 size, 35 turns, stock pinion

// ********************************************************************************************************************* */
// Choose the receiver communication mode (never uncomment both! If both commented out, classic PWM RC signal communication)--
// Serial communication --------
//#define SERIAL_COMMUNICATION // control signals are coming in via the serial interface (comment it out for classic RC signals)
// Only for my "Micro RC" receiver! See: https://github.com/TheDIYGuy999/Micro_RC_Receiver

// PPM communication --------
//#define PPM_COMMUNICATION // control signals are coming in via the PPM interface (comment it out for classic RC signals)
#define NUM_OF_CHL 8          // The number of channels inside our PPM signal (usually max. 8)
#define NUM_OF_AVG 1          // Number of averaging passes (usually one, more will be slow)

// Sound files (22'050 Hz, 8 bit PCM recommended) -----------------------------------------------------------------------
// Choose the start sound (uncomment the one you want) --------
volatile int startVolumePercentage = 130; // Adjust the start volume (usually = 100%)
//#include "sounds/UnionPacific2002Start.h" // Union Pacific 2002 SD70M Locomotive Start
//#include "sounds/ScaniaV8Start.h" // Scania V8 Start
//#include "sounds/ScaniaR500V8Start.h" // Scania R500 V8 Start
//#include "sounds/ScaniaV8StartNew.h" // Scania V8 Start
//#include "sounds/UralV8Start.h" // Ural 4320 V8 Start (use it for Diesel trucks, if no other is available) use it for King Hauler
//#include "sounds/HgP408Start.h" // HG P408 Humvee Diesel (only for small speakers)
//#include "sounds/DefenderV8Start.h" // Land Rover Defender V8 Start
//#include "sounds/JaguarXjsHeStart.h" // Jaguar XJS HE Starts
//#include "sounds/KenworthW900Start.h" // Kenworth W900 Truck Start
//#include "sounds/MackStart.h" // Mack Truck Start
//#include "sounds/DetroitDieselStart.h" // Detroit Diesel generic Truck Start
//#include "sounds/InternationalDT-466Start.h" // International DT-466 Start
//#include "sounds/Cat3404BStart.h" // Caterpillar 3406B start
//#include "sounds/ActrosV8Start.h" // MB Actros V8 Truck Start
//#include "sounds/VWBeetleStart.h" // VW Beetle or Bug
#include "usersounds/v8soundteststart.h" // Scania V8 Start

// Choose the motor idle sound (uncomment the one you want) --------
volatile int idleVolumePercentage = 90; // Adjust the idle volume (usually = 100%, more also working, depending on sound, 50% if diesel knock sound is used)
volatile int engineIdleVolumePercentage = 50; // the engine volume will be throttle dependent (usually = 40%, never more than 100%!)
//#include "sounds/UnionPacific2002Idle.h" // Union Pacific 2002 SD70M Locomotive with 16 cylinder Diesel (set volume to 60%)
//#include "sounds/ScaniaV8Idle.h" // Scania V8 (bad quality)
//#include "sounds/ScaniaR500V8Idle.h" // Scania R500 V8
//#include "sounds/ScaniaV8IdleNew.h" // Scania V8 (Volume 100%, 35%, Turbo 70%, 10%, Wastegate 50%, 1%, CEP 100, TSM 2)
//#include "sounds/ScaniaV8IdleNewWarm.h" // Scania V8 (Volume 100%, 35%, Turbo 70%, 10%, Wastegate 50%, 1%, CEP 100, TSM 2) a good one!
//#include "sounds/ScaniaR620V8Idle2.h" // Scania R620 V8 (a bit thin, add about 80% turbo volume)
//#include "sounds/ScaniaR620Uphill.h" // Scania R620 V8 going uphill, typical knock - knock under load
//#include "sounds/ScaniaR620Uphill2.h" // Scania R620 V8 going uphill, typical knock - knock under load (this one is better, Volume 180%, 20%, Turbo 60%, 10%, Wastegate 50%, 1%, CEP 100, TSM 2)
//#include "sounds/UralV8Idle.h" // Ural 4320 V8
//#include "sounds/HumveeDieselIdle.h" // "Humvvee" (Hummer H1) V8 Diesel
//#include "sounds/HgP408Idle.h" // HG P408 Humvee Diesel (only for small speakers)
//#include "sounds/DetroitDieselIdle.h" // Detroit Diesel generic Truck (Volume 80%, 30%, Turbo 60%, 10%, Wastegate 50%, 1%, CEP 100, TSM 3)
//#include "sounds/DetroitDieselStraightPipeIdle.h" // Detroit Diesel Truck with straight pipes (use multiplier = 2, acc = 2, dec = 1)
//#include "sounds/DetroitDieselBassBoost15db.h" // Detroit Diesel Truck with straight pipes. Bass 100-200Hz + 15dB
//#include "sounds/DetroitDieselBassBoost7db.h" // Detroit Diesel Truck with straight pipes. Bass 100-200Hz + 7dB (use it for King Hauler, Volume 130%, 35%, Turbo 70%, 10%)
//#include "sounds/DetroitDieselPeterbiltCabover.h" // Detroit Diesel Peterbilt cabover truck
//#include "sounds/DetroitDieselKenworth.h" // Detroit Diesel Kenworth truck (use Ural V8 Start & 100% turbo)
//#include "sounds/DetroitDieselJohnDeereTractor.h" // Detroit Diesel John Deere tractor
//#include "sounds/InternationalDT-466Idle.h" // International DT-466 idle (Volume 100%, 35%, Turbo 60%, 10%, Wastegate 30%, 1%, CEP 100, TSM 3)
//#include "sounds/Cat3406BIdle.h" // Caterpillar 3406B idle (Volume 100%, 35%, Turbo 70%, 10%, Wastegate 30%, 1%, CEP 100, TSM 3)
//#include "sounds/M35Idle.h" // AM General M35 Truck
//#include "sounds/M35BassBoost7db.h" // AM General M35 Truck Bass 100-200Hz + 7dB (Volume 100%, 35%, Turbo 100%, 30%)
//#include "sounds/UnimogU1000TurboFullLoad.h" // Unimog U1000 Turbo (Volume 100%, 35%, Turbo 50%, 10%, Wastegate 150%, 1%)
//#include "sounds/ActrosV8Idle.h" // MB Actros V8 Truck Idle (very noisy)
//#include "sounds/KenworthW900Idle.h" // Kenworth W900 Truck Idle (Volume 80%, 30%, Turbo 60%, 10%, Wastegate 50%, 1%, CEP 100, TSM 2)
//#include "sounds/MackIdle.h" // Mack Truck Idle (very thin)
//#include "sounds/DefenderV8Idle.h" // Land Rover Defender V8
//#include "sounds/Mustang68Idle.h" // Ford Mustang 1968
//#include "sounds/DodgeChallenger70Idle.h" // 1970 Dodge Challenger
//#include "sounds/MgBGtV8Idle.h" // MG B GT V8
//#include "sounds/LaFerrariIdle.h" // Ferrari "LaFerrari"
//#include "sounds/chevyNovaV8Idle.h" // Chevy Nova Coupe 1975
//#include "sounds/V8TrophyTruckIdle.h" // V8 Trophy Truck
//#include "sounds/JaguarXjsHeIdle.h" // Jaguar XJS HE (bad quality)
//#include "sounds/VWBeetleIdle.h" // VW Beetle or Bug
//#include "sounds/20Hz.h" // 20Hz test tone
//#include "sounds/100Hz.h" // 100Hz test tone
//#include "sounds/1000Hz.h" // 1000Hz test tone
#include "usersounds/v8soundtestidle.h"

// Choose the motor revving sound (experimental, uncomment the one you want) --------
//#define REV_SOUND // uncomment this, if you want to use the separate, optional rev sound
volatile int revVolumePercentage = 150; // Adjust the idle volume (usually = 100%, more also working, depending on sound)
volatile int engineRevVolumePercentage = 30; // the engine volume will be throttle dependent (usually = 40%, never more than 100%!)
const uint8_t revSwitchPoint = 250; // The rev sound is played instead of the idle sound above this point
#ifdef REV_SOUND
//#include "sounds/ScaniaV8Rev.h" // Scania V8
#include "sounds/ScaniaV8Rev2.h" // Scania V8
#endif

// Choose the Diesel ignition "knock" sound (played in the fixed sampling rate interrupt, uncomment the one you want) --------
volatile int dieselKnockVolumePercentage = 250; // Adjust the Diesel knock volume (usually = 200 - 500%)
volatile int dieselKnockIdleVolumePercentage = 15; // Diesel knock volume while idling (usually = 20%)
volatile int dieselKnockInterval = 4; // Idle sample length divided by this number (2 -4, depending on sound files)
//#include "sounds/DieselKnockDummy.h" // If you don't want Diesel knock sound
//#include "sounds/ScaniaR620UphillKnock.h" // Scania R620 V8
//#include "sounds/LanzBulldogDieselKnock.h" // Lanz Bulldog tractor (Interval = 2)
#include "sounds/ScaniaDieselKnock.h" // Strong Scania V8 diesel knock while highwyway race against Volvo truck (,500%, 20%, Interval = 2 possible, for slow running V8 engines)
//#include "sounds/ScaniaDieselKnock2.h" // Strong, short Scania V8 diesel knock while highwyway race against Volvo truck (Interval = 4 possible, for faster running engines)

// Adjust the additional turbo sound (set "turboVolumePercentage" to "0", if you don't want it) --------
volatile int turboVolumePercentage = 20; // Adjust the turbo volume (usually = 70%)
volatile int turboIdleVolumePercentage = 10; // the turbo volume will be throttle dependent (usually = 10%)
#include "sounds/TurboWhistle.h" // Turbo sound, playing in parallel with engine sound!

// Adjust the additional turbo wastegate valve  sound (set "wastegateVolumePercentage" to "0", if you don't want it)--------
volatile int wastegateVolumePercentage = 90; // Adjust the wastegate volume (usually = 70%, up to 250%)
volatile int wastegateIdleVolumePercentage = 1;
#include "sounds/UnimogU1000TurboWastegate.h" // Wastegate sound is played, after rapid throttle drop with engaged clutch

// Choose the horn sound (uncomment the one you want) --------
volatile int hornVolumePercentage = 100; // Adjust the horn volume (usually = 100%)
//#include "sounds/TrainHorn.h" // American train horn
//#include "sounds/HornblastersOUTLAWTrainHornLong.h" // Hornblasters outlaw train horn long
//#include "sounds/HornblastersOUTLAWTrainHornShort.h" // Hornblasters outlaw train horn short
//#include "sounds/ManTgeHorn.h" // MAN TGE truck horn (King Hauler)
//#include "sounds/westinghouseHorn.h" // American truck horn
//#include "sounds/FireTruckAirHorn.h" // US fire truck air horn
//#include "sounds/CarHorn.h" // A boring car horn
#include "sounds/TruckHorn.h" // A generic truck horn
//#include "sounds/PeterbiltHorn.h" // A Peterbilt truck horn
//#include "sounds/2ToneTruckHorn.h" // A 2 tone truck horn

// Choose the siren / additional horn sound (uncomment the one you want) --------
volatile int sirenVolumePercentage = 50; // Adjust the siren volume (usually = 100%)
//#include "sounds/sirenDummy.h" // If you don't want siren sound
//#include "sounds/UsPoliceSiren.h" // US Police siren
//#include "sounds/FireTruckAirSiren.h" // US fire truck air siren (King Hauler)
//#include "sounds/FeuerwehrMartinshorn.h" // European Feuerwehr Martinshorn
//#include "sounds/IrishFireEngineHorn.h" // Irish fire truck horn
#include "sounds/siren01norskere22.h" // Norwegian siren
//#include "sounds/PostAutoHorn.h" // The typical Swiss post bus horn

volatile int siren2VolumePercentage = 50; // Adjust the siren volume (usually = 100%, never more!)
#include "usersounds/siren02Norsk.h"

// Choose the air brake release sound (uncomment the one you want) --------
volatile int brakeVolumePercentage = 200; // Adjust the brake volume (usually = 200%)
//#include "sounds/AirBrakeDummy.h" // If you don't want air brake sound
#include "sounds/TruckAirBrakes.h" // Short truck air brake sound
//#include "sounds/TruckAirBrakesLong.h" // Long truck air brake sound
//#include "sounds/TruckAirBrakes2.h" // Another truck air brake sound
//#include "sounds/AirBrakeSqueak.h" // Squeaky air brake sound

// Choose the parking brake engaging sound (uncomment the one you want) --------
volatile int parkingBrakeVolumePercentage = 150; // Adjust the brake volume (usually = 200%)
//#include "sounds/ParkingBrakeDummy.h" // If you don't want parking brake sound
#include "sounds/ParkingBrake.h" // Parking brake sound

// Choose the pneumatic gear shifting sound (uncomment the one you want) --------
volatile int shiftingVolumePercentage = 200; // Adjust the shifting volume (usually = 100%)
//#include "sounds/AirShiftingDummy.h" // If you don't want pneumatic shifting sound
#include "sounds/AirShifting.h" // Pneumatic shifting sound

// Choose the additional "sound1" (uncomment the one you want) --------
volatile int sound1VolumePercentage = 100; // Adjust the sound1 volume (usually = 100%)
//#include "sounds/EMDLocomotiveBell.h" // American EMD locomotive bell
//#include "sounds/007JamesBond.h" // James Bond melody
//#include "sounds/M2Fire.h" // M2 salve
//#include "sounds/GlenCanyon.h" // Glen Canyon country song for truckers ;-)
#include "sounds/door.h" // opening and closing the door

// Choose the reversing beep sound --------
volatile int reversingVolumePercentage = 30; // Adjust the reversing sound volume (usually = 70%)
#include "sounds/TruckReversingBeep.h" // 1000Hz peep sound

// Choose the indicator / turn signal options --------
const boolean indicators = true; // "true", if you want to trigger indicator lights (turn signals)
volatile int indicatorVolumePercentage = 100; // Adjust the indicator sound volume (usually = 100%)
const uint16_t indicatorOn = 300; // The indicator will be switched on above +/- this value, if wheels are turned
const boolean INDICATOR_DIR = true; // adjust indicator direction with true or false
#include "sounds/Indicator.h" // "Tick-Tack" sound

// Choose the blue light opions -----------------------------------------------------------------------------------------
const boolean doubleFlashBlueLight = true; // double flash blue lights if "true", "rotating" beacons if "false"

// PWM input signal range calibration ------------------------------------------------------------------------------------
const uint16_t pulseNeutral = 30; // pulseZero +/- this value (30) is the neutral range
const uint16_t pulseSpan = 450; // pulseZero +/- this value (150 for JMT 10A ESC, otherwise around 450)

// PWM ESC output signal range calibration (connect crawler type ESC to pin 33)-------------------------------------------
const int16_t escPulseSpan = 1000; // pulseZero +/- this value (> 500 = limited top speed, about 1600 (new ESC = 1000) for King Hauler)
const uint8_t escRampTimeFirstGear = 20; // determines, how fast the acceleration and deceleration happens (about 15 - 25, 25 for King Hauler)
const uint8_t escRampTimeSecondGear = 50; // 50 for King Hauler
const uint8_t escRampTimeThirdGear = 75; // 75 for King Hauler
const uint8_t escBrakeSteps = 30; // determines, how fast the ESC is able to brake down (20 - 30, 30 for King Hauler)
const uint8_t escAccelerationSteps = 3; // determines, how fast the ESC is able to accelerate (2 - 3, 3 for King Hauler)

// Horn trigger signal type (true / false)-------------------------------------------------------------------------------
const boolean pwmSoundTrigger = true; // horn triggered by RC PWM signal instead of constant high level signal, if "true"
// Do NOT enable this boolean, if no PWM signal is connected or you will experience huge engine RPM resopnse delays

// Gearbox parameters ---------------------------------------------------------------------------------------------------
const boolean shifted = false; // false = linear rpm curve, true = shifting points (experimental old stuff, do not use it)
const boolean shiftingAutoThrottle = true; // For Tamiya 3 speed tansmission, throttle is altered for synchronizing, if "true"

// Clutch parameters ---------------------------------------------------------------------------------------------------
const uint16_t clutchEngagingPoint = 1; // CEP. The "clutch" is engaging above this point = engine rpm sound in synch with ESC power

// Shaker parameters (simulating engine vibrations) ---------------------------------------------------------------------
const uint8_t shakerStart = 100; // Shaker power while engine start (max. 255, about 100)
const uint8_t shakerIdle = 49; // Shaker power while idling (max. 255, about 49)
const uint8_t shakerFullThrottle = 40; // Shaker power while full throttle (max. 255, about 40)
const uint8_t shakerStop = 60; // Shaker power while engine stop (max. 255, about 60)

// Engine parameters ----------------------------------------------------------------------------------------------------
//Activate for "engine on off" functionality in combination with "Micro RC" Receiver from TheDIYGuy999. No Pulse Zero auto calibration in this case!!
const boolean engineManualOnOff = false;

// Engine RPM range (2 for big Diesels, 4 for fast running motors)
const uint32_t TOP_SPEED_MULTIPLIER = 3; // TSM. RPM multiplier: the bigger the number, the larger the rev range, 2 - 4 is a good place to start. ESP32 will crash, if > 5 @ 22'050Hz!

// Engine mass simulation
const int8_t acc = 2; // Acceleration step (2) 1 = slow for locomotive engine, 9 = fast for trophy truck
const int8_t dec = 1; // Deceleration step (1) 1 = slow for locomotive engine, 5 = fast for trophy truck
