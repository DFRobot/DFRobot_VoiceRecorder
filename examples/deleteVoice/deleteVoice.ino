/*!
 * @file deleteVoice.ino
 * @brief delete voice
 * @details You can get the data you want and print it out on the serial port.
 * @copyright Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author [ZhixinLiu](zhixin.liu@dfrobot.com)
 * @version V1.0
 * @date 2020-10-13
 * @url https://github.com/DFRobot/DFRobot_VoiceRecorder
 */
#include "DFRobot_VoiceRecorder.h"

#define VOICE_ADDRESS  0x30      // default I2C device address is 0x30
DFRobot_VoiceRecorder_I2C voicerecorder(&Wire, VOICE_ADDRESS);
int deleteVoices = 4;            // set delete button

void setup()
{
  Serial.begin(115200);
  pinMode(deleteVoices, INPUT);
  while(voicerecorder.begin() != 0) {
    Serial.println("i2c device number error!");
    delay(1000);
  } Serial.println("i2c connect success!");

  /**
   * Set button mode on or off
   * BUTTON_MODE_ON
   * BUTTON_MODE_OFF
   */
  voicerecorder.setButtonMode(BUTTON_MODE_ON);

  /**
   * Set light mode on or off
   * LIGHT_MODE_ON
   * LIGHT_MODE_OFF
   */
  voicerecorder.setLightMode(LIGHT_MODE_ON);

  /**
   * Set the audio number
   * VOICE_NUMBER_0
   * VOICE_NUMBER_1
   * VOICE_NUMBER_2
   * VOICE_NUMBER_3
   * VOICE_NUMBER_4
   * VOICE_NUMBER_5
   * VOICE_NUMBER_6
   * VOICE_NUMBER_7
   * VOICE_NUMBER_8
   * VOICE_NUMBER_9
   */
  if(VOICE_NONE != voicerecorder.setVoiceNumber(VOICE_NUMBER_0)){
    Serial.println("set number error, please wait!");
  }
}

void loop()
{
  volatile uint8_t state = 0;
  if(digitalRead(deleteVoices)){
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