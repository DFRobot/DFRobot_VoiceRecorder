# DFRobot_VoiceRecorder
- [English Version](./README.md)

DFR0699 音频录放模块 Pro 是 DFRobot 最新推出的一体式语音交互模块。集成录放音功能为一体,集成按钮可以一键录音,也支持 Grevity I2C 接口由单片机控制录放音。可以储存 10 段 100s 时长音频,支持耳机和扬声器接口输出,内置功放即插即用。让您轻松地为创意项目添加语音提示或声音互动。<br>

![正反面svg效果图](resources/images/DFR0699.jpg)

## 产品链接(https://www.dfrobot.com.cn/goods-3228.html)

    SKU:DFR0699

## 目录

* [概述](#概述)
* [库安装](#库安装)
* [方法](#方法)
* [兼容性](#兼容性y)
* [历史](#历史)
* [创作者](#创作者)

## 概述

录音功能:<br>
单段最长100s,最大10段录音保存<br>
语音合成:<br>
合成 -999999999.999999999 到 999999999.999999999<br>
电气性能:<br>
工作电压: 3.3-5V<br>
物理特性:<br>
外形尺寸:<br>
控制接口: I2C
I2C 地址: 0x30-0x39 可设置<br>
输出接口:<br>
3.5mm 耳机口<br>
PH2.0 扬声器口<br>

## 库安装

这里提供两种使用本库的方法:<br>
1.打开Arduino IDE,在状态栏中的Tools--->Manager Libraries 搜索"DFRobot_VoiceRecorder"并安装本库.<br>
2.首先下载库文件,将其粘贴到\Arduino\libraries目录中,然后打开examples文件夹并在该文件夹中运行演示.<br>

## 方法

```C++
  /**
   * @fn setButtonMode
   * @brief 设置按键模式
   * @param mode 使能按键或者禁止按键
   * @n     BUTTON_MODE_ON   0x00 使能按键
   * @n     BUTTON_MODE_OFF  0x01 禁止按键
   */
  void setButtonMode(uint8_t mode);

  /**
   * @fn setLightMode
   * @brief 设置灯光模式 
   * @param mode 打开或者关闭灯光
   * @n     LIGHT_MODE_OFF 0x00 关闭灯光
   * @n     LIGHT_MODE_ON  0x01 打开灯光
   */
  void setLightMode(uint8_t mode);
  
  /**
   * @fn setVoiceNumber
   * @brief 设置音频号
   * @param number 音频编号
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
   * @retval VOICE_SYNTHESISING 语音合成状态
   * @retval VOICE_PLAYING      播放状态
   * @retval VOICE_RECORDING    录制状态
   * @retval VOICE_NONE         空闲状态 设置编号成功
   */
  uint8_t setVoiceNumber(uint8_t number);

  /**
   * @fn getI2CAddress
   * @brief 获取i2c地址
   * @return i2c device address
   */
  uint8_t getI2CAddress(void);

  /**
   * @fn getNowState
   * @brief 获取当前状态
   * @return state int type
   * @retval VOICE_SYNTHESISING 语音合成状态
   * @retval VOICE_PLAYING      播放状态
   * @retval VOICE_RECORDING    录制状态
   * @retval VOICE_NONE         空闲状态
   */
  uint8_t getNowState(void);

  /**
   * @fn getButtonMode
   * @brief 获取按键模式
   * @return Mode 按键模式
   * @retval BUTTON_MODE_ON  0x00
   * @retval BUTTON_MODE_OFF 0x01
   */
  uint8_t getButtonMode(void);

  /**
   * @fn getLightMode
   * @brief 获取灯光模式
   * @return Mode 灯光模式
   * @retval LIGHT_MODE_OFF  0x00
   * @retval BUTTON_MODE_OFF 0x01
   */
  uint8_t getLightMode(void);


  /**
   * @fn getVoiceNumber
   * @brief 获取当前音频编号
   * @return number
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
   * @brief 获取音频状态
   * @return state 当前编号是否有音频
   * @retval 0 当前编号有音频
   * @retval 1 当前为空
   */
  uint8_t getVoiceState(void);

  /**
   * @fn getTimeRemaining
   * @brief 获取剩余录制时间
   * @return The time range is 0-100
   */
  uint8_t getTimeRemaining(void);

  /**
   * @fn recordvoiceStart
   * @brief 开始录制
   * @return state
   * @retval VOICE_SUCCESS 开始录制
   * @retval VOICE_BUSY 重复录音或重放
   * @retval VOICE_NONE 音频已经存在
   */
  uint8_t recordvoiceStart(void);

  /**
   * @fn playVoiceStart
   * @brief 开始播放
   * @return state
   * @retval VOICE_SUCCESS 开始播放
   * @retval VOICE_BUSY 重复录音还是重放
   * @retval VOICE_NONE 当前编号没有音频
   */
  uint8_t playVoiceStart(void);

  /**
   * @fn deleteVoice
   * @brief 删除当前编号的声音
   * @return state
   * @retval VOICE_SUCCESS 删除成功
   * @retval VOICE_BUSY 正在录制或者播放
   * @retval VOICE_NONE 当前编号没有声音
   */
  uint8_t deleteVoice(void);

  /**
   * @fn recordVoiceEnd
   * @brief 结束录制
   * @return state
   * @retval VOICE_SUCCESS 结束录制
   * @retval VOICE_NONE 没有开始录制不需要结束录制
   */
  uint8_t recordVoiceEnd(void);

  /**
   * @fn playVoiceEnd
   * @brief 结束播放
   * @return VOICE_SUCCESS 结束播放
   * @retval VOICE_NONE 没有开始播放
   */
  uint8_t playVoiceEnd(void);

  /**
   * @fn voiceSynthesis
   * @brief 语音合成
   * @param language
   * @n     CHINESE_LANGUAGE 0x01   中文
   * @n     ENGLISH_LANGUAGE 0x02   英文
   * @param number range is (999999999 to -999999999)
   * @return state
   * @retval VOICE_SUCCESS       语音合成成功
   * @retval VOICE_BUSY          当前为播放或者录制状态,请先结束当前动作
   * @retval VOICE_SYNTHESISING  语音合成中
   * @retval DATA_ERROR          数据错误
   * @retval MODE_ERROR          模式错误
   */
  uint8_t voiceSynthesis(uint8_t language ,int64_t number);

  /**
   * @fn voiceSynthesis
   * @brief 语音合成
   * @param language 
   * @n     CHINESE_LANGUAGE     0x01
   * @n     ENGLISH_LANGUAGE     0x02
   * @param string 输入字符串的范围是由模式决定的
   * @param mode
   * @n     VOICE_SYNTHESIS_MODE 范围 (999999999.999999999  to  -999999999.999999999)
   * @n     VOICE_REPLACE_MODE   9比特字符串
   * @return state
   * @retval VOICE_SUCCESS       语音合成成功
   * @retval VOICE_BUSY          当前为播放或者录制状态,请先结束当前动作
   * @retval VOICE_SYNTHESISING  语音合成中
   * @retval DATA_ERROR          数据错误
   * @retval MODE_ERROR          模式错误
   */
  uint8_t voiceSynthesis(uint8_t language ,String string ,uint8_t mode);
```

## 兼容性

| 主板        | 通过 | 未通过 | 未测试 | 备注 |
| ----------- | :--: | :----: | :----: | ---- |
| Arduino uno |  √   |        |        |      |
| Mega2560    |  √   |        |        |      |
| Leonardo    |  √   |        |        |      |
| ESP32       |  √   |        |        |      |
| micro:bit   |      |        |   √    |      |


## 历史

- 2020/05/21 - V0.1.0 版本
- 2020/10/13 - V0.2.0 版本
- 2020/11/13 - V0.3.0 版本
- 2021/05/11 - V1.0.0 版本

## 创作者

Written by ZhixinLiu(zhixin.liu@dfrobot.com), 2021. (Welcome to our [website](https://www.dfrobot.com/))
