/**！
 * @author junfengzheng
 * @version  V1.0
 * @date  2021-08-04
*/

#include "DFRobot_VoiceRecorder.h"

#define I2C_ADDRESS  (0x30)
DFRobot_VoiceRecorder_I2C voicerecorder(&Wire, I2C_ADDRESS);
uint8_t buttonPin=D10; 
bool playing=false;
void record(){
  if((digitalRead(buttonPin)==HIGH)&&(playing==false))//When you press the button
 {
  voicerecorder.setVoiceNumber(VOICE_NUMBER_2);//Select Audio NO.2
  voicerecorder.deleteVoice();
  Serial.println("Delete Voice");
  voicerecorder.recordvoiceStart();
  Serial.println("Recode Start");
  for (int8_t n = 20; n > 0; n--)
  {
    Serial.println(n);
    delay(1000);
  }
  voicerecorder.recordVoiceEnd();//Recode End
  Serial.println("Recode End");
  playing=true;
  }
}
void play(){
  if((digitalRead(buttonPin)==LOW)&&(playing==true))//release the button
  {
  voicerecorder.setVoiceNumber(VOICE_NUMBER_2);//Select Audio NO.2
  voicerecorder.playVoiceStart();
  Serial.println("play recording");
  for (int8_t n = 22; n > 0; n--)
  {
    Serial.println(n);
    delay(1000);
  }
  playing=false;
  }
}
void setup() {
  pinMode(buttonPin,INPUT);  
  Serial.begin(115200);
  while (voicerecorder.begin() != 0)
  {
    Serial.println("i2c device number error!");
    delay(1000);
  }
  Serial.println("i2c connect success!");
}
void loop() {
  record();
  play();
}
