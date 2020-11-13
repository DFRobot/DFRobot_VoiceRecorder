/* 
 * @file getSetValue.ino
 * @You can get the data you want and print it out on the serial port.
 *
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author      [ZhixinLiu](zhixin.liu@dfrobot.com)
 * @version  V1.0
 * @date  2020-10-13
 * @get from https://www.dfrobot.com
 * @url https://github.com/DFRobot/DFRobot_VoiceRecorder
 */
#include "DFRobot_VoiceRecorder.h"

#define I2C_ADDRESS  0x30                                         // default I2C device address is 0x30
DFRobot_VoiceRecorder_I2C voicerecorder(&Wire, I2C_ADDRESS);      // i2c configuration parameters

void setup()
{
  Serial.begin(115200);
  while(voicerecorder.begin() != 0) {
    Serial.println("i2c device number error!");
    delay(1000);
  } Serial.println("i2c connect success!");

/*
  Set button mode on or off
    BUTTON_MODE_ON
    BUTTON_MODE_OFF
*/
  voicerecorder.setButtonMode(BUTTON_MODE_ON);

/*
  Set light mode on or off
    LIGHT_MODE_ON
    LIGHT_MODE_OFF
*/
  voicerecorder.setLightMode(LIGHT_MODE_ON);

/*
  Set the audio number
    VOICE_NUMBER_0
    VOICE_NUMBER_1
    VOICE_NUMBER_2
    VOICE_NUMBER_3
    VOICE_NUMBER_4
    VOICE_NUMBER_5
    VOICE_NUMBER_6
    VOICE_NUMBER_7
    VOICE_NUMBER_8
    VOICE_NUMBER_9
*/
  if(VOICE_NONE != voicerecorder.setVoiceNumber(VOICE_NUMBER_0)){
    Serial.println("set number error, please wait!");
  }
}

void loop()
{
  Serial.print("I2C address  = 0x");
  Serial.println(voicerecorder.getI2CAddress(),HEX);
  
  Serial.print("Button Mode  = 0x0");
  Serial.println(voicerecorder.getButtonMode(),HEX);
  
  Serial.print("Light  Mode  = 0x0");
  Serial.println(voicerecorder.getLightMode(),HEX);

  Serial.print("Voice Number = 0x0");
  Serial.println(voicerecorder.getVoiceNumber(),HEX);

  Serial.print("Voice State  = 0x0");
  Serial.println(voicerecorder.getVoiceState(),HEX);

  Serial.print("excess time  = ");
  Serial.print(voicerecorder.getTimeRemaining());
  Serial.println("S");

  switch(voicerecorder.getNowState())
  {
    case VOICE_SYNTHESISING:
      Serial.println("voice synthesising !");
      break;
    case VOICE_PLAYING:
      Serial.println("voice palying !");
      break;
    case VOICE_RECORDING:
      Serial.println("voice recording !");
      break;
  }
  delay(1000);
}