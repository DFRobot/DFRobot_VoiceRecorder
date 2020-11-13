/* 
 * @file recordStartEnd.ino
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

#define I2C_ADDRESS  0x30                                             // default I2C device address is 0x30
DFRobot_VoiceRecorder_I2C voicerecorder(&Wire, I2C_ADDRESS);          // i2c configuration parameters
int recordStart = 4;
int recordEnd   = 5;

void setup()
{
  Serial.begin(115200);
  pinMode(recordStart , INPUT);
  pinMode(recordEnd , INPUT);
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
  volatile uint8_t state   = 0;
  if(digitalRead(recordStart)) {
    state = voicerecorder.recordvoiceStart();      // start record
    if(state == VOICE_SUCCESS){
      Serial.println("start record!");
    }else if(state == VOICE_HAVED_AUDIO){
      Serial.println("Please delete the audio before recording!");
    }else{
      Serial.println("It has been recorded or played, please finish recording or playing first!");
    }
    delay(300);
  }
  
  if(digitalRead(recordEnd)) {
    state = voicerecorder.recordVoiceEnd();        // end record
    if(state == VOICE_SUCCESS){
      Serial.println("end record!");
    }else{
      Serial.println("record No beginning!");
    }
    delay(300);
  }
}