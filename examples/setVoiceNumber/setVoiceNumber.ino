/*!
 * @file setVoiceNumber.ino
 * @brief set voice number
 * @details You can see the value of the digital tube changing from 0-9-0.
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
int setVNumber = 4;
void setup()
{
  Serial.begin(115200);
  pinMode(setVNumber , INPUT);
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
  static uint8_t   numbers = 0;
  if(digitalRead(setVNumber)) {
    if(numbers >= 9) numbers = 0;
    else             numbers++;
    if(VOICE_NONE != voicerecorder.setVoiceNumber(numbers)){
      Serial.println("set number error, please wait!");
    }
    delay(200);
  }
}