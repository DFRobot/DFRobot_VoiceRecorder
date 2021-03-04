# DFRobot_VoiceRecorder
The recording module can record 10 sounds, 100 seconds each, which can be controlled by I2C and manually.

## DFRobot_VoiceRecorder
---------------------------------------------------------
DFRobot_VoiceRecorder


## Table of Contents

* [Summary](#Summary)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [History](#history)
* [Credits](#credits)

<snippet>
<content>


## Summary

You can set button mode, light mode, manual control number and I2C control, to achieve the recording function

## Installation

To use this library, first download the library file, paste it into the \Arduino\libraries directory, then open the examples folder and run the demo in the folder.

## Methods

```C++

  /**
   * @brief initialization parameters for i2c
   * @return 0 or 1, 0 is i2c begin success, 1 is i2c begin error
   */
  uint8_t begin();

  /**
   * @brief Set button mode
   * @param BUTTON_MODE_ON   0x00
   * @param BUTTON_MODE_OFF  0x01
   */
  void setButtonMode(uint8_t mode);

  /**
   * @brief Set light mode
   * @param LIGHT_MODE_OFF   0x00
   * @param LIGHT_MODE_ON    0x01
   */
  void setLightMode(uint8_t mode);

  /**
   * @brief set voice number
   * @param VOICE_NUMBER_0   0x00
   * @param VOICE_NUMBER_1   0x01
   * @param VOICE_NUMBER_2   0x02
   * @param VOICE_NUMBER_3   0x03
   * @param VOICE_NUMBER_4   0x04
   * @param VOICE_NUMBER_5   0x05
   * @param VOICE_NUMBER_6   0x06
   * @param VOICE_NUMBER_7   0x07
   * @param VOICE_NUMBER_8   0x08
   * @param VOICE_NUMBER_9   0x09
   * @return state
   *    VOICE_SYNTHESISING   is speech synthesis state
   *    VOICE_PLAYING        is playing state
   *    VOICE_RECORDING      is recording state
   *    VOICE_NONE           is idle condition set number success
   */
  uint8_t setVoiceNumber(uint8_t number);

  /**
   * @brief get i2c device address
   * @return i2c device address
   */
  uint8_t getI2CAddress();

  /**
   * @brief get now state
   * @return state
   *    VOICE_SYNTHESISING   is speech synthesis state
   *    VOICE_PLAYING        is playing state
   *    VOICE_RECORDING      is recording state
   *    VOICE_NONE           is idle condition
   */
  uint8_t getNowState(void);

  /**
   * @brief get Button Mode
   * @return Mode 
   *    BUTTON_MODE_ON   0x00
   *    BUTTON_MODE_OFF  0x01
   */
  uint8_t getButtonMode(void);
  
  /**
   * @brief get light Mode
   * @return Mode 
   *    LIGHT_MODE_OFF   0x00
   *    BUTTON_MODE_OFF  0x01
   */
  uint8_t getButtonMode(void);

  /**
   * @brief get voice number
   * @return number 
   *    VOICE_NUMBER_0   0x00
   *    VOICE_NUMBER_1   0x01
   *    VOICE_NUMBER_2   0x02
   *    VOICE_NUMBER_3   0x03
   *    VOICE_NUMBER_4   0x04
   *    VOICE_NUMBER_5   0x05
   *    VOICE_NUMBER_6   0x06
   *    VOICE_NUMBER_7   0x07
   *    VOICE_NUMBER_8   0x08
   *    VOICE_NUMBER_9   0x09
   */
  uint8_t getVoiceNumber(void);

  /**
   * @brief get voice state
   * @return state 0 is Current position has audio 1 is empty
   */
  uint8_t getVoiceState(void);

  /**
   * @brief get time reamaining
   * @return The time range is 0-100
   */
  uint8_t getTimeRemaining(void);

  /**
   * @brief start record
   * @return VOICE_SUCCESS is start record ,VOICE_BUSY is repeat recording or playback,VOICE_NONE is Audio already exists, delete and record
   */
  uint8_t recordvoiceStart(void);

  /**
   * @brief start play
   * @return VOICE_SUCCESS is start play ,VOICE_BUSY is repeat recording or playback,VOICE_NONE is no songs in the current number
   */
  uint8_t playVoiceStart(void);

  /**
   * @brief delete voice
   * @return VOICE_SUCCESS is delete success ,VOICE_BUSY is repeat recording or playback,VOICE_NONE is no songs in the current number
   */
  uint8_t deleteVoice(void);

  /**
   * @brief End of the tape
   * @return VOICE_SUCCESS is end success ,VOICE_NONE is no begin record
   */
  uint8_t recordVoiceEnd(void);

  /**
   * @brief End play
   * @return VOICE_SUCCESS is end success ,VOICE_NONE is no begin record
   */
  uint8_t playVoiceEnd(void);

  /**
   * @brief speech synthesis
   * @param language is  CHINESE_LANGUAGE     0x01
   *                     ENGLISH_LANGUAGE     0x02
   * @param number range is (999999999 to -999999999)
   * @return VOICE_SUCCESS        is speech synthesis success
   *         VOICE_BUSY           is recording or playing. Please finish recording or playing first
   *         VOICE_SYNTHESISING   is In speech synthesis
   *         DATA_ERROR           is data error
   *         MODE_ERROR           is mode error
   */
  uint8_t VoiceSynthesis(uint8_t language ,int64_t number);
  
  
  /**
   * @brief speech synthesis
   * @param language is  CHINESE_LANGUAGE     0x01
   *                     ENGLISH_LANGUAGE     0x02
   * @param string   is  Input string the scope is determined by the pattern
   * @param mode     is  VOICE_SYNTHESIS_MODE         range (999999999.999999999  to  -999999999.999999999)
   *                     VOICE_REPLACE_MODE           Nine-bit string
   * @return VOICE_SUCCESS        is speech synthesis success
   *         VOICE_BUSY           is recording or playing. Please finish recording or playing first
   *         VOICE_SYNTHESISING   is In speech synthesis
   *         DATA_ERROR           is data error
   *         MODE_ERROR           is mode error
   */
  uint8_t VoiceSynthesis(uint8_t language ,String string ,uint8_t mode);
```
## Compatibility

MCU                | Work Well | Work Wrong | Untested  | Remarks
------------------ | :----------: | :----------: | :---------: | -----
Arduino uno        |      √       |              |             | 
Mega2560           |      √       |              |             | 
Lenardo            |      √       |              |             | 
ESP32              |      √       |              |             | 
ESP8266            |      √       |              |             | 

## History

-  May      21, 2020 - Version 0.1 released.
-  October  13, 2020 - Version 0.2 released.
-  November 6,  2020 - Version 0.3 released.
-  November 13, 2020 - Version 0.4 released.

## Credits

Written by ZhiXinLiu(ZhiXin.Liu@dfrobot.com), 2020. (Welcome to our [website](https://www.dfrobot.com/))