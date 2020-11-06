/* 
 * @file deleteVoice.ino
 * @The experimental phenomenon is to delete the current numbered audio.
 * @the red REG flashes for the first time, and the deletion is completed for the second time
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
int deleteVoices  = 4;                                            // set delete button

void setup()
{
  Serial.begin(115200);
  pinMode(deleteVoices , INPUT);
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
  voicerecorder.setVoiceNumber(VOICE_NUMBER_0);
}

void loop()
{
  volatile uint8_t state   = 0;
  if(digitalRead(deleteVoices)) {
    state = voicerecorder.deleteVoice();       // delete voice
    if(state == VOICE_SUCCESS){
      Serial.println("delete success!");
    }else if(state == VOICE_NONE){
      Serial.println("You don't need to delete,no voice!");
    }else{
      Serial.println("It has been recorded or played, please finish recording or playing first!");
    }
    delay(300);
  }
}