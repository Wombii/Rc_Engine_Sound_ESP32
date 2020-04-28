
# ALLISON GEARBOX + SBUS MOD BY Wombii
 - https://www.youtube.com/watch?v=9ex9XDmr8_Q
 - For ESP32 TTGO_display

## WARNING: You should not use this code directly. It's highly specialized for my specific truck and transmitter setup!
Shared for inspiration only!

 * Butchered to accept SBUS.
 *   - Outputs steering and gear channels directly to servo output pins.
 *   - Outputs managed esp32 signal based on automatic gearbox logic and inertia.
 * Engine sound, inertia and gearbox logic mostly replaced to simulate automatic gearbox.
 * Logic to trick standard ESC into reverse mode.
 *   - Reverse gear selected by separate transmitter switch.
 * WIFI OTA update possible.
 * Changed sound setup to use 2 siren sounds instead of indicators.
 * Completely changed sound triggering.
 * Moved soundfiles to subfolder.
 * Rearranged functions to separate files.
 *  //Added a sound for applying brakes// Not active
 * Disabled LED and shaker.
 * SBUS preparechannels function based on methods from SBUS library from https://github.com/mikeshub/FUTABA_SBUS

version = 3.4 - W-SBUS-2Siren-ALLISONGEARBOX

## Current protoboard:
- Connectors top to bottom: ESC, Steering, Gear, SBUS out, SBUS in (Power and ground from ESC). Power connector for amplifier and esp32 (GND,+5V). Connector for amplifier (GND,+5V,sound).
- ~1k resistors on all signal pins. Pulldown resistors on servo and gear signal. ~10k resistors between DAC and sound out. Please check TheDiyGuy999's original schematic at the bottom.
![](https://github.com/Wombii/Rc_Engine_Sound_ESP32/blob/master/board+esp32.jpg)

![](https://github.com/Wombii/Rc_Engine_Sound_ESP32/blob/master/boardfront.jpg)

![](https://github.com/Wombii/Rc_Engine_Sound_ESP32/blob/master/boardback.jpg)

# - Original Readme below -

# This is an Arduino RC engine sound & light controller for ESP32
It's based on the ATmega 328 version: https://github.com/TheDIYGuy999/Rc_Engine_Sound
and on bitlunis Halloween example: https://github.com/bitluni/MotionPumpkin

## Features:
- Unique vehicle mass inertia simulation (connect your crawler type ESC to pin 33). Throttle output is altered during shifting of a mechanical 3 speed transmission for smooth shifting, gear protection and realistic sound. Works just fine with TAMIYA 3 speed transmissions. Should work as well with crawler 2 speed transmissions. The ESC is controlled by a state machine with the following states: driving forward & reverse (varible acceleration, depending on throttle position), neutral, braking forward & reverse (variable deceleration with fine granularity, according to "reverse throttle" position). It also allows to control the brake lights, the brake sound, the reversing light & the reversing beep sound properly. Acceleration & deceleration (coasting & braking) are adjustable separately for ech gear to ensure maximum realism.
- Unique "virtual clutch" allows to rev the engine below an adjustable ESC output speed. Above, the clutch engages and ensures, that the engine sound is in synch with the wheel RPM. Sounds and behaves just great in combination with a shifting transmission!
- Many selectable sounds: engine cranking, engine idling, engine revving, turbo whining, diesel ignition "knock", wastegate valve, horns, sirens, reversing beep, air brake, parking brake, gear shifting etc.
- Realistic engine sound is mixed together on the fly from up to 4 sounds: engine idling, turbo, wastegate (all with variable sampling rate), Diesel ignition knock (fixed sampling rate, so it does not vary in pitch)
- Load (throttle position) dependent volume sounds: idle, rev, Diesel knock
- Engine RPM dependent volume sounds: turbo, wastegate
- Dozens of engine & other sounds included, you can also compose your own, using Audacity and bitlunis conversion tool (link above)
- Engine RPM range and inertia adjustable, volume of all sounds adjustable, engine sounds separatly for load and idling.
- Many other paramerets can be adjusted. All adjustments are easily accessible in "Adjustments.h"
- Sound files up to 22'050Hz, 8bit, mono can be used
- Compatible input signals: PWM, PPM, Serial (Micro RC Receiver only)
- Works best with a PAM8403 amplifier module, connected to pin 25 & 26, via 10kOhm resistors & a 10kOhm potentiometer (see schematic below)
- The engine RPM is calculated according to RC signal input on pin 13 *** CAUTION, 3.3V max. on all pins! *** 330 Ohm resistors on all I/O pins recommended!
- Non linear throttle curves can be generated in "curves.h"
- Light effects: headlights, tail lights, brake lights, fog lights, roof lights, cab lights, reversing light, indicators (turn signals), hazard lights, blue light etc. (max. 12 outputs)
- Engine vibration simulation, using a shaker motor with excentric weight: Strong vibration while cranking, medium wlile idling, slight while revving
- Use an ESP32, CPU frequency must be set to 240MHz

## New in V 0.1:
- Runs on an ESP32 (240MHz)
- It's still quick and dirty, but works with the included V8 short course truck idle sound
- sounds way better than the ATmega 328 version, thanks to  22'050Hz sampling rate (instead of 8'000Hz)

## New in V 0.2:
- Many new 22'050Hz, 8bit sound files generated, mostly the same as in the ATmega 328 version, but in better quality :-)

## New in V 0.3:
- Engine start / stop implemented, including starter sounds
- Three different start sounds available
- Horn implemented. It is played on pin 26 (see wiring instructions in code) triggered by switch on input 12
- Two different horn sounds available
- The horn can play in parallel with the variable speed engine sound!
- For easier access, the "settings.h" file was renamed in "Adjustments.h"

## New in V 0.4:
- volume offset bug fixed
- added the typical Swisss post bus horn, an American police siren, a European Feuerwehr Martinshorn and a car horn
- added the varible "shifted", which allows to select between linear and shifted engine rpm response
- added schematic

## New in V 0.5:
- added idle sound volume adjustment variable "idleVolumePercentage" in "Adjustments.h"
- added Union Pacific 2002 SD70M 16 cylinder Diesel locomotive sounds
- added Jaguar XJS HE car sound (bad quality)
- added "pwmHornTrigger" variable in Adjustments.h", which allows to trigger the horn, using a PWM signal. Allows to use standard receivers

## New in V 0.6:
- fixed slow engine RPM response: The RC signal pulsewidth is now only read every 100ms, so much more processing time is available for other things

## New in V 0.7:
- fixed auto throttle zero calibration bug
- fixed "gap" bug, if sounds were triggered in PWM mode
- PWM mode now allows to trigger 2 sounds

## New in V 0.8:
- volume offset bug was back and is fixed again!
- improved sound quality of Union Pacific 2002
- Detroit Diesel truck added
- Sine test tones added
- M2 sound added

## New in V 0.9:
- Humvee Diesel engine sound added
- Truck pneumatic brake release sound added

## New in V 1.0:
- Engine now slowing down, if switched off, not just fading out
- Fader bug fixed, now working smoothly
- HG P408 sounds added

## New in V 1.1:
- Truck reversing beep sound added
- Can play in parallel with other additional sound and with variable speed engine sound!

## New in V 1.2:
- Light functions added: reversing light, beacons (blue light), headlights, taillights with integrated brake lights
- My "statusLED" library is required: https://github.com/TheDIYGuy999/statusLED

## New in V 1.3:
- Irish fire truck horn
- Double flash blue lights option
- US fire truck air horn and air siren

## New in V 1.4:
- Indicator (turn signal) support added
- RC signals now handled as arrays in order to simplify auto zero calibration of multiple channels

## New in V 1.5:
- More Detroit Diesels added

## New in V 1.51:
- Solved issue: redefinition of 'const unsigned int sampleRate'

## New in V 1.6:
- Servo input channels rearranged to match the pinout of the "Micro RC" receiver (you can change it in the pin assignment section)
- Cleaned up the code a bit
- An updated version (16 timers) of my "statusLED" library is required: https://github.com/TheDIYGuy999/statusLED
- Added experimental support for serial communication with my "Micro RC" receiver: https://github.com/TheDIYGuy999/Micro_RC_Receiver
- Uncomment "#define SERIAL_COMMUNICATION" in Adjustments.h
- Connect pin 36 "VP" to pin "TXO" of the receiver (disable "TXO_momentary1" & "TXO_toggle1" in vehicleConfig.h)
- The "RC Servo Signals" are not required in this mode!
- Added Scania R500 V8 sounds

## New in V 1.7:
- Added shaker motor control on pin 23. Simulates engine vibration. IRLZ44N Mosfet and freewheel diode 1N5819 required
- Shaker power can be adjusted with the variables "shakerMin" & "shakerMax" in Adjustments.h
- Driver schematic down below
- I'm using a shaker motor from the G.T.Power kit 103061 (this controller is crap, but the accessories are useful)
- Foglight and side light pins moved to pins 18 & 19

## New in V 1.8:
- LED pins changed for trailer light driver
- Horn sounds, siren sounds & additional sounds variable names changed! ---> Replace them all!
- Added more horns
- Added indicator (blinker) ticking sound
- Added independent volume adjustment for every sound
- Engine sound volume is now throttle dependent (adjustable)

## New in V 1.9:
- Kenworth W900 added
- Initial PPM signal input on pin 34 added. For now usable for steering and throttle signal. Uncomment "#define PPM_COMMUNICATION", if you want to use it.

## New in V 2.0:
- Swiss post bus horn moved to category "sirens" ---> Replace existing .h file!
- Experimental ESC output (do not use it). Latest statusLED library update required: https://github.com/TheDIYGuy999/statusLED
- Mack truck sounds added

## New in V 2.1:
- Additional turbo sound (playing in parallel with engine sound), volume and throttle dependent volume adjustable
- Caterpillar 3406B sound added
- VW Beetle sound added
- Indicator direction adjustable with "INDICATOR_DIR" = "true" or "false"
- Shaker rpm now adjustable for engine start, idle, full throttle & shutdown

## New in V 2.2:
- Support for crawler ESC (with direct brake) on pin 33. Vehicle mass simulation with proportional brake! Tested in Tamiya King Hauler (REELY Model No H0050 ESC) and working fine, but use it at your own risk! If you want to test it, connect ESC to pin 33 of the ESP32 instead of the receiver output.
- LED pins rearranged  to fit my board layout (you can change it in the pin assignment section)
- Scania R620 sound added

## New in V 2.3:
- Reversing light, reversing beep and brake light behaviour changed in order to interact correctly with the new vehicle mass simulation
- ESC is locked, if engine is not running ;-)
- Air brake sound now triggered correctly, as soon as the brake pedal is released
- I'm really amazed about this update! The vecihle almost behaves like a real truck now.

## New in V 2.4:
- Bug fixed: direct transition from state "braking backwards" to "driving backwards" now working
- failsafe function for serial signal added. Emergency brake is triggered in case of RC signal loss (serial & PWM mode only, PPM will follow)

## New in V 2.5:
- 3rd brake light on pin 32 added
- "escPulseSpan" > 1400 now working properly. Allows to accelerate and decelerate even smoother as well as limiting the top speed to a realistic level

## New in V 2.6:
- Indicator activation point adjustable with "indicatorOn"
- Norwegian siren, new air brake sound
- Door noise
- sound files moved to /sounds
- optimized bluelight patterns, using the new, optional "delay" variable. Latest statusLED library update required: https://github.com/TheDIYGuy999/statusLED

## New in V 2.7:
- Hornblasters train horns added
- Horns are now louder
- Trash removed
- Acceleratoin & deceleration now shifting transmission gear dependent

## New in V 2.8:
- "clutchClosingPoint" configuration variable added. Prevents engine sound from "rubber band effect". Engine sound is in synch (clutch engaged) with ESC power above this value
- Virtual clutch is also disengaging during gear shifting, allowing the engine rpm to settle down during shifting
- Acceleration speed now variable, depending on throttle position
- Added way more inertia to make vehicle behavior even more realistic
- Brake has now much finer granularity

## New in V 2.9:
- "shiftingAutoThrottle" is altering throttle for synchronizing while shifting the TAMIYA 3 speed transmission -> Gearbox is protected, extreme realism in engine sound!
- More inertia added, engine idle volume lowered to 40%

## New in V 2.91:
- Engine sound was slowing down too much during braking. This bug is now solved
- No turbo sound while braking: Bug solved
- King Hauler parameters fine adjusted
- "clutchClosingPoint" renamed to "clutchEngagingPoint"

## New in V 3.0:
- Ramping ESC signal faster below "clutchEngagingPoint" to prevent clutch from excessive slipping
- Solved a 2nd engine rpm bug during braking

## New in V 3.1:
- Added a new, pretty realistic SCANIA R620 "Straight Pipe" engine sound (ScaniaR620Uphill2.h). Pure goose flesh!
- Detroit diesel sounds with more bass added
- A speaker with good bass reproduction is required!

## New in V 3.2:
- Added the new "Wastegate" sound. It is triggered, if the throttle is dropped rapidly
- Added Unimog U 1000, uses the new Wastegate sound
- Added AM General M35 truck

## New in V 3.3:
- Dimmed headlights during engine start
- International DT-466 sounds added
- New SCANIA V8 added
- Brake sound moved to the fixed sample rate playback interrupt
- Cleaned up placback interrupt functions
- DAC offset 128 moved to dacWrite()
- Brake sounds don't have to start & end @ -128
- Parking brake sound added
- Pneumatic shifting sound added

## New in V 3.4:
- Experimental support for separate engine revving sound. See "REV_SOUND" in Adjustments.h (don't use it)
- New Diesel ignition "knock" sound (fixed sample rate), played in synch with the engine sound (variable sample rate). This results in a way more realistic Diesel sound, because the ignition "knock" does not vary in pitch.
- engine sound is now mixed together from up to 4 sounds: idle, turbo, wastegate, Diesel knock. All of them are variable in volume, depending on throttle position or engine RPM. You can adjust everything, using a lot of variables in "Adjustments,h". The result is a very realistic engine sound. allows to use an engine RPM range of 3 instead of 2 without sounding strange
- New squeaky brake sound
- Up to 11 sounds are now played in parallel!


## On the todo list:
- solving ticking noise issue in serial communication mode
- adding more sounds
- adding SBUS protocol
- adding schematic for LED wiring (for now pinout see code)
- designing a proper PCB

## How to create new sound file arrays:

### Audacity:
- Import the sound file you want in Audacity
- Convert it to mono, if needed
- on the bottom left, select project frequency 22'050Hz
- cut the sound to one engine cycle. Zoom in to find the exact zero crossing
- adjust the volume, so that the entire range is used
- select > export audio > WAV > 8-bit-PCM
- note, that the files should be as short as possible: search for a repeating sound pattern and cut it to this length

### Convert the wav file with bitlunis converting tool:
- open https://bitluni.net/wp-content/uploads/2018/01/Audio2Header.html
- select the generated wav file from Audacity
- select "normalize"
- select "resample" and the frequency (22'050 recommended)
- a .h file is generated and downloaded
- move the .h file to your sketch directory
- rename the variables, according to the exising files of the same category

### Processing the new header file with your sound:
- include this .h file in "settings.h"

### Compiling the new sketch:
- compile and upload the sketch in Arduino IDE
- the new engine should now run...

## Schematic:
![](https://github.com/TheDIYGuy999/Rc_Engine_Sound_ESP32/blob/master/wiring.jpg)

![](https://github.com/TheDIYGuy999/Rc_Engine_Sound_ESP32/blob/master/shakerDriver.jpg)

For now, do the wiring according to the pin names in the sketch.

## Pictures:
First prototype
![](https://github.com/TheDIYGuy999/Rc_Engine_Sound_ESP32/blob/master/top.jpg)

Micro RC receiver wiring (with RC signal and serial connections)
![](https://github.com/TheDIYGuy999/Rc_Engine_Sound_ESP32/blob/master/receiver_wiring.jpg)

![](https://github.com/TheDIYGuy999/Rc_Engine_Sound_ESP32/blob/master/Bestueckt_oben.jpg)

![](https://github.com/TheDIYGuy999/Rc_Engine_Sound_ESP32/blob/master/oben.jpg)

![](https://github.com/TheDIYGuy999/Rc_Engine_Sound_ESP32/blob/master/unten.jpg)


2019 - 2020, TheDIYGuy999
