/*!
 * @file recorder.ino
 * @brief use example
 * @details application realizes the recording and play function, press the recording, then press the play.
 * @details the button after recording to play, and press the button after playing to record.
 * @copyright Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author [JunfengZheng](junfeng.zheng@dfrobot.com)
 * @version V1.0
 * @date 2021-08-04
 * @url https://github.com/DFRobot/DFRobot_VoiceRecorder
 */
#include "DFRobot_VoiceRecorder.h"
#define VOICE_ADDRESS  (0x30)
#define BUTTON_PIN   (D10)
DFRobot_VoiceRecorder_I2C voicerecorder(&Wire, VOICE_ADDRESS);
bool playing = false;

void record(void)
{
  // When you press the button 
  if((digitalRead(BUTTON_PIN)==HIGH)&&(playing==false))
  {
    voicerecorder.setVoiceNumber(VOICE_NUMBER_2); //Select Audio NO.2
    voicerecorder.deleteVoice();
    Serial.println("Delete Voice");
    voicerecorder.recordvoiceStart();
    Serial.println("Recode Start");
    for(int8_t n = 20; n > 0; n--){
      Serial.println(n);
      delay(1000);
    }
    voicerecorder.recordVoiceEnd(); //Recode End
    Serial.println("Recode End");
    playing=true;
  }
}

void play(void)
{
  // release the button
  if((digitalRead(BUTTON_PIN)==LOW)&&(playing==true))
  {
    voicerecorder.setVoiceNumber(VOICE_NUMBER_2); // Select Audio NO.2
    voicerecorder.playVoiceStart();
    Serial.println("play recording");
    for (int8_t n = 22; n > 0; n--){
      Serial.println(n);
      delay(1000);
    }
    playing=false;
  }
}

void setup()
{
  pinMode(BUTTON_PIN,INPUT);  
  Serial.begin(115200);
  while (voicerecorder.begin() != 0)
  {
    Serial.println("i2c device number error!");
    delay(1000);
  }
  Serial.println("i2c connect success!");
}

void loop()
{
  record();
  play();
}
