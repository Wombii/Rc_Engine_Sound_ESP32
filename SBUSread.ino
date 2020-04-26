/*
 * SBUS reading by Wombii
 * 
 * Serial.begin(100000)
 * 
 * The data stream from the receiver is 25 bytes of serial data at 100K baudrate. Repeats every x ms (5-20ms?)
 * This data contains 16 analog channels, 2 digital channels and frame lost + failsafe info.
 * 
 * byte 1 and 25 is startframe (0x0F) and endframe (0x00)
 * byte 24 is d17, d18, frame lost, failsafe (1 bit each)
 * byte 2-23 is 16 analog channels (11 bits each)
 * 
 * How to use, insert this in the main loop:

  SBUSinput();  //Should be called more frequently than the receiver sends a full data set.
                //When a full data set is received, SBUS.channelsReady will be 1 or true and channels updated in the SBUS. struct.

    //if all channels are in and ready:
    if (SBUS.channelsReady)
    {
      //SBUSpreparechannels_M();  //convert buffer to channels. Now called directly from SBUSinput().
      SBUS.channelsReady = 0;     //reset the channelsReady flag.

      //Do stuff with the updated channel info:
      SBUSthrottle();             //copy throttle channel to pulseWidth[2]
      SBUSswitches();             //process horn and siren switches
    }

 * SBUS.channels[0] to SBUS.channels[15] contains data for the 16 analog channels. CAUTION: (frSky) SBUS channels use 0-2000, not 1000-2000us
 * map(SBUS.channels[0],0,2000,1000,2000) will work to convert it to traditional pwm values.
 * 
 * SBUS.failsafe will be //TODO: insert correct value here// when receiver reports loss of comms with transmitter.
 * 
 * Use SBUSprintstuff() to print out all processed SBUS data to the serial monitor.
 */

 
/*
#define sbusdebug 1

//union+struct works fine on atmega arduinos, but not ESP32. 
//save the incoming buffer to tempArray[25] and read out SBUShelper.pieces.ch1 - ch16 or SBUShelper.pieces.failsafe
union SBUSconverter
  {
    struct
    {
      byte startframe:8;
      unsigned int ch1 : 11;
      unsigned int ch2 : 11;
      unsigned int ch3 : 11;
      unsigned int ch4 : 11;
      unsigned int ch5 : 11;
      unsigned int ch6 : 11;
      unsigned int ch7 : 11;
      unsigned int ch8 : 11;
      unsigned int ch9 : 11;
      unsigned int ch10 : 11;
      unsigned int ch11 : 11;
      unsigned int ch12 : 11;
      unsigned int ch13 : 11;
      unsigned int ch14 : 11;
      unsigned int ch15 : 11;
      unsigned int ch16 : 11;
      byte d17 : 1;
      byte d18 : 1;
      byte frameLost: 1;
      byte failsafe: 1;
      byte test : 4; //junk
      byte endframe :8;
    } pieces;
    uint8_t tempArray[25];
  } SBUShelper;

struct sbusdata
{
  unsigned int channels[18];
  byte failsafe;
  byte channelsReady = 0;
} SBUS;
*/



//There is a failsafe bit in the SBUS stream. That bit is set by the receiver if it loses contact with the transmitter.
//This is a function to set another failsafe state if the microcontroller is not receiveing data from the receiver.
void SBUSfailsafeTimeout(unsigned long failsafeTimeoutTimer, unsigned long timeoutDuration)
{
  //static unsigned long failsafeTimeoutStore = 0;
  //Serial.println((millis() - failsafeTimeoutTimer));
  if (millis() - failsafeTimeoutTimer > timeoutDuration)
  {
    SBUS.failsafe = 8;
  }
}


//Read the serial stream from receiver.
void SBUSinput(void)
{
  static byte state = 1;
  byte readbyte = 0;
  //Serial.println("s:");
  switch (state)
  {
    
    //If the serial rx hardware buffer is full, we get useless data because it may overwrite parts of a data set.
    //First empty the buffer if it is full.
    //If SBUSinput() is not called frequently enough, this is most likely where the SBUS reading will fail.
    case 1:
      SBUS.tempArray[24] = 1;                           //Break the endframe in tempArray to be able to test for a good endframe in stage 3.
      
      //If hardware buffer contains too many bytes...
      if (SBUSserial.available() > 53)                  //53 for arduino mega, not sure how large the esp32 buffer is.
      {
        #if sbusdebug 
        Serial.print("buffer full"); 
        #endif
        //...read until the buffer is empty. 
        while(SBUSserial.available()) 
        {
          SBUSserial.read();
          
        }
        #if sbusdebug
        Serial.println(".k");
        #endif
      }
      //Else, read until we find the startframe 0x0F...
      if (SBUSserial.available() )
      {
        while(SBUSserial.available())
        {
          readbyte = SBUSserial.read();
          //Serial.println(readbyte,HEX);
          if (readbyte == 0x0F)
          {
            //... and save the next byte in the first spot of the input array.
            SBUS.tempArray[0] = readbyte;
            state = 2;
            break;
          }
        }
        
      }
      
      break;

    //If we have found a startbyte and have read the first data byte, keep reading and saving!
    case 2:
      
      static byte i = 1;
      //Keep reading and saving data to the input array for as long as there is data in the hardware buffer
      while (SBUSserial.available() )
      {
        readbyte = SBUSserial.read();
        
        //Until we've read all 25 bytes
        SBUS.tempArray[i++] = readbyte;
        if (i >= 25)
        {
          //Then exit and goto stage 3
          i = 1;
          state = 3;
          break;
        }
      }
      break;

    case 3:
      //If it seems like a good full read (endframe is expected to be 0x00)
      if (SBUS.tempArray[24] == 0)
      {
        //Do the things. Either set channelsReady = 1 here, or go directly to data processing.

        //copy from the buffer that will be partially overwritten when new data comes in to an array that can be used for data processing and passthrough.
        for(byte i=0; i<25; i++)
        {
          SBUS.receivedSBUSdata[i] = SBUS.tempArray[i]; 
        }
        
        SBUS.failsafe = 0;            //Clearing the failsafe state in case it's been set by the timeout function.
        SBUSpreparechannels_M();      //Process the data set into channels (11 bits per channel)
        #if sbusdebug
        SBUSprintstuff();
        #endif

        
      }
      //if the endframe doesn't match a good full read
      else
      {
        SBUSserial.read(); //read one byte in attempt to catch up to pattern.
      }
      state = 1;
      break;
  }
  
}


//Based on SBUS library from
//https://github.com/mikeshub/FUTABA_SBUS

//A good explanation of this method here: http://www.robotmaker.eu/ROBOTmaker/quadcopter-3d-proximity-sensing/sbus-graphical-representation

//tempArray contains 24 bytes of data (8x24 bits), but we need to pull out 16x11 bits for 16 analog channels + 1 byte (8 bits) for d17,d18,failsafe.
//This is not straight forward as the data bytes arrive with their most significant bytes first, but the 11 bit channel "bytes" are little endian, so we have to 
//do some backwards trickery. 
//Channel 1 use all 8 bits of the first byte + 3 bits of the second byte. Move the right-most 3 bits of byte 2 to the left and
//place them in front of byte 1, then read these 11 bytes as one number.
// aaaaaaaa cccccbbb
// bbbaaaaaaaa = channel 1
//Channel 2 use the next 5 bits of byte 2 and move them to the right, then the right-most 6 bits of byte 3 and move them left to the front.
// cccccbbb eedddddd
// ddddddccccc == channel 2
//For the Arduino Mega I was able to use a union+struct bitfield combination, but for a portable version, this seems to be the way to do it:

void SBUSpreparechannels_M()
{
  #if sbusdebug 
  Serial.print("channels: ");
  #endif

  SBUS.channelsReady = 1; //Channels are updated and ready to use.


  SBUS.channels[0]  = ((SBUS.receivedSBUSdata[1]|SBUS.receivedSBUSdata[2]<< 8) & 0x07FF);
  SBUS.channels[1]  = ((SBUS.receivedSBUSdata[2]>>3|SBUS.receivedSBUSdata[3]<<5) & 0x07FF);
  SBUS.channels[2]  = ((SBUS.receivedSBUSdata[3]>>6|SBUS.receivedSBUSdata[4]<<2|SBUS.receivedSBUSdata[5]<<10) & 0x07FF);
  SBUS.channels[3]  = ((SBUS.receivedSBUSdata[5]>>1|SBUS.receivedSBUSdata[6]<<7) & 0x07FF);
  SBUS.channels[4]  = ((SBUS.receivedSBUSdata[6]>>4|SBUS.receivedSBUSdata[7]<<4) & 0x07FF);
  SBUS.channels[5]  = ((SBUS.receivedSBUSdata[7]>>7|SBUS.receivedSBUSdata[8]<<1|SBUS.receivedSBUSdata[9]<<9) & 0x07FF);
  SBUS.channels[6]  = ((SBUS.receivedSBUSdata[9]>>2|SBUS.receivedSBUSdata[10]<<6) & 0x07FF);
  SBUS.channels[7]  = ((SBUS.receivedSBUSdata[10]>>5|SBUS.receivedSBUSdata[11]<<3) & 0x07FF);
  SBUS.channels[8]  = ((SBUS.receivedSBUSdata[12]|SBUS.receivedSBUSdata[13]<< 8) & 0x07FF);
  SBUS.channels[9]  = ((SBUS.receivedSBUSdata[13]>>3|SBUS.receivedSBUSdata[14]<<5) & 0x07FF);
  SBUS.channels[10] = ((SBUS.receivedSBUSdata[14]>>6|SBUS.receivedSBUSdata[15]<<2|SBUS.receivedSBUSdata[16]<<10) & 0x07FF);
  SBUS.channels[11] = ((SBUS.receivedSBUSdata[16]>>1|SBUS.receivedSBUSdata[17]<<7) & 0x07FF);
  SBUS.channels[12] = ((SBUS.receivedSBUSdata[17]>>4|SBUS.receivedSBUSdata[18]<<4) & 0x07FF);
  SBUS.channels[13] = ((SBUS.receivedSBUSdata[18]>>7|SBUS.receivedSBUSdata[19]<<1|SBUS.receivedSBUSdata[20]<<9) & 0x07FF);
  SBUS.channels[14] = ((SBUS.receivedSBUSdata[20]>>2|SBUS.receivedSBUSdata[21]<<6) & 0x07FF);
  SBUS.channels[15] = ((SBUS.receivedSBUSdata[21]>>5|SBUS.receivedSBUSdata[22]<<3) & 0x07FF);

  
  if (SBUS.receivedSBUSdata[23] & (1<<0)) {
    SBUS.channels[16] = 1;
  }
  else{
    SBUS.channels[16] = 0;
  }
  
  if (SBUS.receivedSBUSdata[23] & (1<<1)) {
    SBUS.channels[17] = 1;
  }
  else{
    SBUS.channels[17] = 0;
  }

  //2 of the bits from the last data byte contain framelost and failsafe
  int failsafebits = SBUS.receivedSBUSdata[23] & (1<<3); //(3<<2);
  SBUS.failsafe = failsafebits>>3;


  return;
}


//print all 16 channels, then digital bits and failsafe.
void SBUSprintstuff(){


  for(byte i=0; i<15; i++)
  {
    Serial.print(SBUS.channels[i]);
    Serial.print("\t");
    //Serial1.write(timingArray[0][0][i]); //sends bytevalues to app
  }
  Serial.print("DDF:");
  Serial.print(SBUS.channels[16]);
  Serial.print("\t");
  Serial.print(SBUS.channels[17]);

  Serial.print("\t");
  Serial.println(SBUS.failsafe);
}
