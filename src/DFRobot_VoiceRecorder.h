/*!
 * @file DFRobot_VoiceRecorder.h
 * @brief Define the DFRobot_VoiceRecorder class infrastructure, the implementation of the base method
 * @copyright	Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author [ZhixinLiu](zhixin.liu@dfrobot.com)
 * @version V1.0
 * @date 2020-10-13
 * @url https://github.com/DFRobot/DFRobot_VoiceRecorder
 */
#ifndef __DFRobot_VOICERECORDER_H__
#define __DFRobot_VOICERECORDER_H__
#include <Arduino.h>
#include <Wire.h>

//#define ENABLE_DBG                ///< Open this macro to see the program running in detail
//#define NORMAL_ENABLE             ///< normal dbg

#ifdef ENABLE_DBG
  #ifdef NORMAL_ENABLE
    #define DBG(...) {Serial.println(__VA_ARGS__);}
  #else
    #define DBG(...) {Serial.print("[");Serial.print(__FUNCTION__); Serial.print("(): "); Serial.print(__LINE__); Serial.print(" ] "); Serial.println(__VA_ARGS__);}
  #endif
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
  
  /**
   * @fn setButtonMode
   * @brief Set button mode
   * @param mode Enable or disable the button function
   * @n     BUTTON_MODE_ON   0x00 enable button
   * @n     BUTTON_MODE_OFF  0x01 disable button
   */
  void setButtonMode(uint8_t mode);

  /**
   * @fn setLightMode
   * @brief Set light mode 
   * @param mode enable or disable lights
   * @n     LIGHT_MODE_OFF 0x00 disable lights
   * @n     LIGHT_MODE_ON  0x01 enable lights
   */
  void setLightMode(uint8_t mode);
  
  /**
   * @fn setVoiceNumber
   * @brief set voice number
   * @param number The audio number to play
   * @n     VOICE_NUMBER_0   0x00
   * @n     VOICE_NUMBER_1   0x01
   * @n     VOICE_NUMBER_2   0x02
   * @n     VOICE_NUMBER_3   0x03
   * @n     VOICE_NUMBER_4   0x04
   * @n     VOICE_NUMBER_5   0x05
   * @n     VOICE_NUMBER_6   0x06
   * @n     VOICE_NUMBER_7   0x07
   * @n     VOICE_NUMBER_8   0x08
   * @n     VOICE_NUMBER_9   0x09
   * @return state int type
   * @retval VOICE_SYNTHESISING is speech synthesis state
   * @retval VOICE_PLAYING      is playing state
   * @retval VOICE_RECORDING    is recording state
   * @retval VOICE_NONE         is idle condition set number success
   */
  uint8_t setVoiceNumber(uint8_t number);

  /**
   * @fn getI2CAddress
   * @brief get i2c device address
   * @return i2c device address
   */
  uint8_t getI2CAddress(void);

  /**
   * @fn getNowState
   * @brief get now state
   * @return state int type
   * @retval VOICE_SYNTHESISING is speech synthesis state
   * @retval VOICE_PLAYING      is playing state
   * @retval VOICE_RECORDING    is recording state
   * @retval VOICE_NONE         is idle condition
   */
  uint8_t getNowState(void);

  /**
   * @fn getButtonMode
   * @brief get Button Mode
   * @return Mode button mode
   * @retval BUTTON_MODE_ON  0x00
   * @retval BUTTON_MODE_OFF 0x01
   */
  uint8_t getButtonMode(void);

  /**
   * @fn getLightMode
   * @brief get light Mode
   * @return Mode light mode
   * @retval LIGHT_MODE_OFF  0x00
   * @retval BUTTON_MODE_OFF 0x01
   */
  uint8_t getLightMode(void);


  /**
   * @fn getVoiceNumber
   * @brief get voice number
   * @return number int type
   * @retval VOICE_NUMBER_0  0x00
   * @retval VOICE_NUMBER_1  0x01
   * @retval VOICE_NUMBER_2  0x02
   * @retval VOICE_NUMBER_3  0x03
   * @retval VOICE_NUMBER_4  0x04
   * @retval VOICE_NUMBER_5  0x05
   * @retval VOICE_NUMBER_6  0x06
   * @retval VOICE_NUMBER_7  0x07
   * @retval VOICE_NUMBER_8  0x08
   * @retval VOICE_NUMBER_9  0x09
   */
  uint8_t getVoiceNumber(void);

  /**
   * @fn getVoiceState
   * @brief get voice state
   * @return state int type
   * @retval 0 is Current position has audio
   * @retval 1 is empty
   */
  uint8_t getVoiceState(void);

  /**
   * @fn getTimeRemaining
   * @brief get time reamaining
   * @return The time range is 0-100
   */
  uint8_t getTimeRemaining(void);

  /**
   * @fn recordvoiceStart
   * @brief start record
   * @return state
   * @retval VOICE_SUCCESS is start record
   * @retval VOICE_BUSY is repeat recording or playback
   * @retval VOICE_NONE is Audio already exists delete and record
   */
  uint8_t recordvoiceStart(void);

  /**
   * @fn playVoiceStart
   * @brief start play
   * @return state
   * @retval VOICE_SUCCESS is start play
   * @retval VOICE_BUSY is repeat recording or playback
   * @retval VOICE_NONE is no songs in the current number
   */
  uint8_t playVoiceStart(void);

  /**
   * @fn deleteVoice
   * @brief delete voice
   * @return state
   * @retval VOICE_SUCCESS is delete success
   * @retval VOICE_BUSY is repeat recording or playback
   * @retval VOICE_NONE is no songs in the current number
   */
  uint8_t deleteVoice(void);

  /**
   * @fn recordVoiceEnd
   * @brief End of the tape
   * @return state
   * @retval VOICE_SUCCESS is end success
   * @retval VOICE_NONE is no begin record
   */
  uint8_t recordVoiceEnd(void);

  /**
   * @fn playVoiceEnd
   * @brief End play
   * @return VOICE_SUCCESS is end success
   * @retval VOICE_NONE is no begin record
   */
  uint8_t playVoiceEnd(void);

  /**
   * @fn voiceSynthesis
   * @brief speech synthesis
   * @param language
   * @n     CHINESE_LANGUAGE 0x01
   * @n     ENGLISH_LANGUAGE 0x02
   * @param number range is (999999999 to -999999999)
   * @return state
   * @retval VOICE_SUCCESS        is speech synthesis success
   * @retval VOICE_BUSY           is recording or playing. Please finish recording or playing first
   * @retval VOICE_SYNTHESISING   is In speech synthesis
   * @retval DATA_ERROR           is data error
   * @retval MODE_ERROR           is mode error
   */
  uint8_t voiceSynthesis(uint8_t language ,int64_t number);

  /**
   * @fn voiceSynthesis
   * @brief speech synthesis
   * @param language 
   * @n     CHINESE_LANGUAGE     0x01
   * @n     ENGLISH_LANGUAGE     0x02
   * @param string is Input string the scope is determined by the pattern
   * @param mode
   * @n     VOICE_SYNTHESIS_MODE range (999999999.999999999  to  -999999999.999999999)
   * @n     VOICE_REPLACE_MODE   Nine-bit string
   * @return state
   * @retval VOICE_SUCCESS       is speech synthesis success
   * @retval VOICE_BUSY          is recording or playing. Please finish recording or playing first
   * @retval VOICE_SYNTHESISING  is In speech synthesis
   * @retval DATA_ERROR          is data error
   * @retval MODE_ERROR          is mode error
   */
  uint8_t voiceSynthesis(uint8_t language ,String string ,uint8_t mode);

  uint8_t sendBuf[I2C_BUFF_LEN] = {NONE};
  uint8_t recvBuf[I2C_BUFF_LEN] = {NONE};
protected:
  uint8_t synthesisMode(uint8_t language  ,String string);
  uint8_t replaceMode(uint8_t language    ,String string);
  uint8_t getBit(int32_t number);  
  uint8_t getVoiceSynthesis(void);
  uint8_t getRecording(void);
  uint8_t getPlaying(void);
  void setRecordPlayState(uint8_t state);
  void setVoiceState(uint8_t state);
  virtual uint8_t readData (uint8_t reg ,uint8_t *data ,uint8_t len)=0;
  virtual void    writeData(uint8_t reg ,uint8_t *data ,uint8_t len)=0;
};

class DFRobot_VoiceRecorder_I2C:public DFRobot_VoiceRecorder{
public:
  DFRobot_VoiceRecorder_I2C(TwoWire *pWire=&Wire ,uint8_t addr=0x30);
  ~DFRobot_VoiceRecorder_I2C(){};
  void writeData(uint8_t reg,uint8_t *data,uint8_t len);
  uint8_t readData(uint8_t reg,uint8_t *data,uint8_t len);
  uint8_t begin();
private:
  TwoWire *_pWire;
  uint8_t _I2C_addr;
};
#endif