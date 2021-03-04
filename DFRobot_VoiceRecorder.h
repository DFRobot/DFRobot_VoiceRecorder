#ifndef __DFRobot_VOICERECORDER_H__
#define __DFRobot_VOICERECORDER_H__
#include <Arduino.h>
#include <Wire.h>

//#define ENABLE_DBG                // Open this macro to see the program running in detail

#ifdef ENABLE_DBG
#define DBG(...) {Serial.print("[");Serial.print(__FUNCTION__); Serial.print("(): "); Serial.print(__LINE__); Serial.print(" ] "); Serial.println(__VA_ARGS__);}
#else
#define DBG(...)
#endif

#define BUTTON_MODE_ON         0
#define BUTTON_MODE_OFF        1

#define LIGHT_MODE_ON          1
#define LIGHT_MODE_OFF         0

#define VOICE_NUMBER_0         0
#define VOICE_NUMBER_1         1
#define VOICE_NUMBER_2         2
#define VOICE_NUMBER_3         3
#define VOICE_NUMBER_4         4
#define VOICE_NUMBER_5         5
#define VOICE_NUMBER_6         6
#define VOICE_NUMBER_7         7
#define VOICE_NUMBER_8         8
#define VOICE_NUMBER_9         9

#define EMPTY                  1
#define NO_EMPTY               0
#define RECORD_PLAY_START      1
#define RECORD_PLAY_END        0
#define DELETE_VOICE           1

#define RECORDING_STATE        1
#define RECORDEND_STATE        0

#define PLAYING_STATE          1
#define PLAYEND_STATE          0

#define CHINESE_LANGUAGE       (uint8_t)1
#define ENGLISH_LANGUAGE       (uint8_t)2

#define CHINESE_INTEGER         0x01
#define ENGLISH_INTEGER         0x02
#define CHINESE_DOUBLE          0x03
#define ENGLISH_DOUBLE          0x04
#define MINUS_CHINESE_INTEGER   0x05
#define MINUS_ENGLISH_INTEGER   0x06
#define MINUS_CHINESE_DOUBLE    0x07
#define MINUS_ENGLISH_DOUBLE    0x08
#define CHINESE_REPLACE         0x09
#define ENGLISH_REPLACE         0x0A

#define I2C_ADDRESS_REGISTER    0x00
#define BUTTON_REGISTER         0x01
#define LIGHT_REGISTER          0x02
#define VOICE_NUMBER_REGISTER   0x03
#define RECORD_PLAY_REGISTER    0x04
#define EMPTY_DELETE_REGISTER   0x05
#define TIMEREMAIN_REGISTER     0x06
#define RECORDING_REGISTER      0x07
#define PLAYING_REGISTER        0x08
#define SYNTHESIS_FLAG          0x09
#define SYNTHESIS_HIGH_REGISTER 0x0A
#define SYNTHESIS_LOW_REGISTER  0x0B

#define STRING_CHANGE_NUMBER    0x30
#define MAX_POINT_LENGTH        0x09
#define MAX_REPLACE_LENGTH      0x09
#define MAX_INTEGER             0x04
#define DECIMAL                 0x0A
#define NONE                    0x00
#define I2C_BUFF_LEN            0x14

#define VOICE_SUCCESS           0x01
#define VOICE_NONE              0x00

#define VOICE_SYNTHESISING      0x03
#define VOICE_PLAYING           0x04
#define VOICE_RECORDING         0x05

#define VOICE_HAVED_AUDIO       0x00
#define VOICE_BUSY              0x02
#define MODE_ERROR              0x05
#define DATA_ERROR              0x0B

#define VOICE_SYNTHESIS_MODE    0x01
#define VOICE_REPLACE_MODE      0x02

#define VOICE_MAX_LEN           0x14
#define VOICE_LEN_ERROR         0x07


class DFRobot_VoiceRecorder{
public:
  DFRobot_VoiceRecorder(){};
  ~DFRobot_VoiceRecorder(){};
  
  void setButtonMode(uint8_t mode);
  void setLightMode(uint8_t mode);
  
  void setRecordPlayState(uint8_t state);
  void setVoiceState(uint8_t state);
  
  uint8_t setVoiceNumber(uint8_t number);
  uint8_t VoiceSynthesis(uint8_t language ,int64_t number);
  uint8_t VoiceSynthesis(uint8_t language ,String string ,uint8_t mode);
  uint8_t synthesisMode(uint8_t language  ,String string);
  uint8_t replaceMode(uint8_t language    ,String string);
  
  uint8_t getBit(int32_t number);
  uint8_t recordvoiceStart(void);
  uint8_t playVoiceStart(void);
  uint8_t deleteVoice(void);
  uint8_t recordVoiceEnd(void);
  uint8_t playVoiceEnd(void);

  uint8_t getNowState(void);
  uint8_t getVoiceSynthesis(void);
  uint8_t getRecording(void);
  uint8_t getPlaying(void);
  
  uint8_t getI2CAddress(void);
  uint8_t getButtonMode(void);
  uint8_t getLightMode(void);
  uint8_t getVoiceNumber(void);
  uint8_t getVoiceState(void);
  uint8_t getTimeRemaining(void);
  uint8_t sendBuf[I2C_BUFF_LEN] = {NONE};
  uint8_t recvBuf[I2C_BUFF_LEN] = {NONE};
protected:
  virtual uint8_t readData (uint8_t Reg ,uint8_t *Data ,uint8_t len)=0;
  virtual void    writeData(uint8_t Reg ,uint8_t *Data ,uint8_t len)=0;
};

class DFRobot_VoiceRecorder_I2C:public DFRobot_VoiceRecorder{
public:
  DFRobot_VoiceRecorder_I2C(TwoWire *pWire=&Wire ,uint8_t addr=0x30);
  ~DFRobot_VoiceRecorder_I2C(){};
  void writeData(uint8_t Reg,uint8_t *Data,uint8_t len);
  uint8_t readData(uint8_t Reg,uint8_t *Data,uint8_t len);
  uint8_t begin();
private:
  TwoWire *_pWire;
  uint8_t _I2C_addr;
};
#endif