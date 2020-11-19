#include "DFRobot_VoiceRecorder.h"
/*
DFRobot_VoiceRecorder::DFRobot_VoiceRecorder()
{
}

DFRobot_VoiceRecorder::~DFRobot_VoiceRecorder()
{
}
*/

void DFRobot_VoiceRecorder::setButtonMode(uint8_t mode)
{
  sendBuf[0] = mode;
  writeData(BUTTON_REGISTER ,sendBuf ,1);
}

void DFRobot_VoiceRecorder::setLightMode(uint8_t mode)
{
  sendBuf[0] = mode;
  writeData(LIGHT_REGISTER ,sendBuf ,1);
}

uint8_t DFRobot_VoiceRecorder::setVoiceNumber(uint8_t number)
{
  uint8_t state = getNowState();
  if(VOICE_NONE == state){
    sendBuf[0] = number;
    writeData(VOICE_NUMBER_REGISTER ,sendBuf ,1);
    return state;
  }else{
    return state;
  }
}

void DFRobot_VoiceRecorder::setRecordPlayState(uint8_t state)
{
  sendBuf[0] = state;
  writeData(RECORD_PLAY_REGISTER ,sendBuf ,1);
}

void DFRobot_VoiceRecorder::setVoiceState(uint8_t state)
{
  sendBuf[0] = state;
  writeData(EMPTY_DELETE_REGISTER ,sendBuf ,1);
}

uint8_t DFRobot_VoiceRecorder::VoiceSynthesis(uint8_t language ,String string ,uint8_t mode)
{
  if(VOICE_SYNTHESIS_MODE == mode){
    return synthesisMode(language ,string);
  }else if(VOICE_REPLACE_MODE == mode){
    return replaceMode(language ,string);
  }else{
    return MODE_ERROR;
  }
}
uint8_t DFRobot_VoiceRecorder::getBit(int32_t number)
{
  int32_t temp  = number;
  uint8_t count = 0;
  while(temp != 0)
  {
    temp /= 10;
    count++;
  }
  return count;
}

uint8_t DFRobot_VoiceRecorder::synthesisMode(uint8_t language ,String string)
{
  char *   pointString  = NULL;
  char *   testString   = NULL;
  uint8_t  pointlen     = 0;
  uint8_t  pointCount   = 0;
  uint8_t  pointData[MAX_POINT_LENGTH] = {NONE};
  uint8_t  len = strlen(string.c_str());
  char     string1[100] = {0};
  memcpy(string1 ,string.c_str() ,strlen(string.c_str()));
  if(!((string1[0] >= 0x30 && string1[0] <= 0x39) || (string1[0] == '-')))
  {
    return DATA_ERROR;
  }
  for(uint8_t i = 1; i < len; i++)
  {
    if(!((string1[i] >= 0x30 && string1[i] <= 0x39) || (string1[i] == '.')))
    {
      return DATA_ERROR;
    }
    if(string[i] == '.')
    {
      pointCount++;
    }
    if(pointCount > 1)
    {
      return DATA_ERROR;
    }
  }
  int32_t integer = strtol((const char *)string1 ,&testString ,DECIMAL);
  if(getBit(integer) > 9)
  {
    return DATA_ERROR;
  }
  
  if(language == CHINESE_LANGUAGE){
    pointString = strstr(string1 ,".");
    if(NULL == pointString){
      if(string1[0] == '-'){ language = MINUS_CHINESE_INTEGER; integer *= -1; }
      else {                 language = CHINESE_INTEGER;       }
    }else{
      if(string1[0] == '-'){ language = MINUS_CHINESE_DOUBLE;  integer *= -1; }
      else {                 language = CHINESE_DOUBLE;       }
      pointlen = strlen(pointString) - 1;
      if(pointlen > MAX_POINT_LENGTH) pointlen = MAX_POINT_LENGTH;
      for(uint8_t i = 0; i < pointlen; i++)
        pointData[i] = (uint8_t)pointString[i+1] - STRING_CHANGE_NUMBER;
    }
  }else if(language == ENGLISH_LANGUAGE){
    pointString = strstr(string1 ,".");
    if(NULL == pointString){
      if(string1[0] == '-'){ language = MINUS_ENGLISH_INTEGER; integer *= -1; }
      else {                language = ENGLISH_INTEGER;       }
    }else{
      if(string1[0] == '-'){ language = MINUS_ENGLISH_DOUBLE;  integer *= -1; }
      else {                language = ENGLISH_DOUBLE;        }
      pointlen = strlen(pointString) - 1;
      if(pointlen > MAX_POINT_LENGTH) pointlen = MAX_POINT_LENGTH;
      for(uint8_t i = 0; i < pointlen; i++)
        pointData[i] = (uint8_t)pointString[i+1] - STRING_CHANGE_NUMBER;
    }
  }else{
    language = NONE;
    return MODE_ERROR;
  }

  memset(sendBuf ,NONE ,I2C_BUFF_LEN);
  
  if(getVoiceSynthesis()) {               // In speech synthesis, please wait
    return VOICE_SYNTHESISING;
  }else{
    if(getRecording() == RECORD_PLAY_START || getPlaying() == RECORD_PLAY_START) {
      return VOICE_BUSY;                      // The current number is recording or playing. Please finish recording or playing first
    }else{
      switch(language)
      {
        case CHINESE_INTEGER:
        case ENGLISH_INTEGER:
        case MINUS_CHINESE_INTEGER:
        case MINUS_ENGLISH_INTEGER:
          sendBuf[0] = language;
          sendBuf[1] = integer >> 24;
          sendBuf[2] = integer >> 16;
          sendBuf[3] = integer >> 8;
          sendBuf[4] = integer;
          writeData(SYNTHESIS_FLAG ,sendBuf ,MAX_INTEGER + 1);
          break;
        case CHINESE_DOUBLE:
        case ENGLISH_DOUBLE:
        case MINUS_CHINESE_DOUBLE:
        case MINUS_ENGLISH_DOUBLE:
          sendBuf[0]  = language;
          sendBuf[1]  = integer >> 24;
          sendBuf[2]  = integer >> 16;
          sendBuf[3]  = integer >> 8;
          sendBuf[4]  = integer;
          memcpy(&sendBuf[MAX_INTEGER + 1] ,pointData ,MAX_POINT_LENGTH);
          writeData(SYNTHESIS_FLAG ,sendBuf ,MAX_INTEGER + MAX_POINT_LENGTH + 1);
          break;
        default:
          break;
      }
      return VOICE_SUCCESS;
    }
  }
}


uint8_t DFRobot_VoiceRecorder::replaceMode(uint8_t language ,String string)
{
  uint8_t replaceLen = 0;
  uint8_t replaceData[MAX_REPLACE_LENGTH] = {NONE};
  uint8_t len = strlen(string.c_str());
  uint8_t j   = 0;
  char    string1[100] = {0};
  memcpy(string1 ,string.c_str() ,strlen(string.c_str()));

  for(uint8_t i = 0; i < len; i++)
  {
    if(string1[i] >= 0x30 && string1[i] <= 0x39)
    {
      string1[j++] = string1[i];
    }
  }
  memset(&string1[j] ,0 ,len - j);
  len = j;
  if(language == CHINESE_LANGUAGE){
    language = CHINESE_REPLACE;
  }else if(language == ENGLISH_LANGUAGE){
    language = ENGLISH_REPLACE;
  }else{
    language = NONE;
    return MODE_ERROR;
  }
  replaceLen = len;
  if(replaceLen > MAX_REPLACE_LENGTH) replaceLen = MAX_REPLACE_LENGTH;
  for(uint8_t i = 0; i < replaceLen; i++)
    replaceData[i] = (uint8_t)string1[i] - STRING_CHANGE_NUMBER;
  memset(sendBuf ,NONE ,I2C_BUFF_LEN);
  if(getVoiceSynthesis()){
      return VOICE_SYNTHESISING;
  }else{
    if(getRecording() == RECORD_PLAY_START || getPlaying() == RECORD_PLAY_START) {
      return VOICE_BUSY;                      // The current number is recording or playing. Please finish recording or playing first
    }else{
      sendBuf[0]  = language;
      memcpy(&sendBuf[MAX_INTEGER + 1] ,replaceData ,replaceLen);
      writeData(SYNTHESIS_FLAG ,sendBuf ,MAX_INTEGER + replaceLen + 1);
      return VOICE_SUCCESS;
    }
  }
}


uint8_t DFRobot_VoiceRecorder::VoiceSynthesis(uint8_t language, int64_t number)
{
  if(number > 999999999 || number < -999999999)
  {
    return DATA_ERROR;
  }
  if(language == CHINESE_LANGUAGE){
    if(number > 0){   language = CHINESE_INTEGER;}
    else{number*=-1;  language = MINUS_CHINESE_INTEGER;}
  }else if(language == ENGLISH_LANGUAGE){
    if(number > 0){   language = ENGLISH_INTEGER;}
    else{number*=-1;  language = MINUS_ENGLISH_INTEGER;}
  }else{
    language = NONE;
  }
  memset(sendBuf ,NONE ,I2C_BUFF_LEN); 
  if(getVoiceSynthesis()) {               // In speech synthesis, please wait
    return VOICE_SYNTHESISING;
  }else{
    if(getRecording() == RECORD_PLAY_START || getPlaying() == RECORD_PLAY_START){
      return VOICE_BUSY;                      // The current number is recording or playing. Please finish recording or playing first
    }else{
      sendBuf[0] = language;
      sendBuf[1] = number >> 24;
      sendBuf[2] = number >> 16;
      sendBuf[3] = number >> 8;
      sendBuf[4] = number;
      writeData(SYNTHESIS_FLAG ,sendBuf ,MAX_INTEGER + 1);
      return VOICE_SUCCESS;
    }
  }
}

uint8_t DFRobot_VoiceRecorder::recordvoiceStart(void)
{
  if(getVoiceSynthesis()) {                    // In speech synthesis, please wait
    return VOICE_SYNTHESISING;
  }else{
    if(getRecording() == RECORDING_STATE) {
      return VOICE_BUSY;                       // The current number is recording or playing. Please finish recording or playing first
    }else{
      if(getVoiceState() == EMPTY) {           // if number as is empty
        setRecordPlayState(RECORD_PLAY_START);
        return VOICE_SUCCESS;
      }else{                                   // The current numbered sound is not empty. 
        return VOICE_HAVED_AUDIO;
      }
    }
  }
}

uint8_t DFRobot_VoiceRecorder::playVoiceStart(void)
{
  if(getVoiceSynthesis()) {                    // In speech synthesis, please wait
    return VOICE_SYNTHESISING;
  }else{
    if(getPlaying() == PLAYING_STATE) {
      return VOICE_BUSY;                       // The current number is recording or playing. Please finish recording or playing first
    }else{
      if(getVoiceState() == EMPTY) {
        return VOICE_NONE;                     // There are no songs in the current number
      }else{
        setRecordPlayState(RECORD_PLAY_START);
        return VOICE_SUCCESS;
      }
    }
  }
}

uint8_t DFRobot_VoiceRecorder::deleteVoice(void)
{
  if(getVoiceSynthesis()) {                    // In speech synthesis, please wait
    return VOICE_SYNTHESISING;
  }else{
    if(getRecording() == RECORD_PLAY_START || getPlaying() == RECORD_PLAY_START) {
      return VOICE_BUSY;                       // The current number is recording or playing. Please finish recording or playing first
    }else{
      if(getVoiceState() == EMPTY) {           // if number as is empty
        return VOICE_NONE;                     // You don't need to delete
      }else{
        setVoiceState(DELETE_VOICE);
        while(getVoiceState() != EMPTY)       // Waiting for deletion to complete
          delay(10);
        return VOICE_SUCCESS;
      }
    }
  }
}

uint8_t DFRobot_VoiceRecorder::recordVoiceEnd(void)
{
  if(getVoiceSynthesis()) {                    // In speech synthesis, please wait
    return VOICE_SYNTHESISING;
  }else{
    if(getRecording() == RECORD_PLAY_END) {
      return VOICE_NONE;                       // No beginning
    }else{
      setRecordPlayState(RECORD_PLAY_END);
      return VOICE_SUCCESS;
    }
  }
}

uint8_t DFRobot_VoiceRecorder::playVoiceEnd(void)
{
  delay(50);
  if(getVoiceSynthesis()) {                    // In speech synthesis, please wait
    return VOICE_SYNTHESISING;
  }else{
    if(getPlaying() == RECORD_PLAY_END) {
      return VOICE_NONE;                       // No beginning no end
    }else{
      setRecordPlayState(RECORD_PLAY_END);
      return VOICE_SUCCESS;
    }
  }
}




uint8_t DFRobot_VoiceRecorder::getI2CAddress(void)
{
  delay(50);
  readData(I2C_ADDRESS_REGISTER ,recvBuf ,1);
  return recvBuf[0];
}

uint8_t DFRobot_VoiceRecorder::getButtonMode(void)
{
  delay(50);
  readData(BUTTON_REGISTER ,recvBuf ,1);
  return recvBuf[0];
}

uint8_t DFRobot_VoiceRecorder::getLightMode(void)
{
  delay(50);
  readData(LIGHT_REGISTER ,recvBuf ,1);
  return recvBuf[0];
}

uint8_t DFRobot_VoiceRecorder::getVoiceNumber(void)
{
  delay(50);
  readData(VOICE_NUMBER_REGISTER ,recvBuf ,1);
  return recvBuf[0];
}

uint8_t DFRobot_VoiceRecorder::getNowState(void)
{
  if(getVoiceSynthesis())
    return VOICE_SYNTHESISING;

  if(getRecording() == RECORD_PLAY_START)
    return VOICE_RECORDING;

  if(getPlaying() == RECORD_PLAY_START)
    return VOICE_PLAYING;
  
  return VOICE_NONE;
}

uint8_t DFRobot_VoiceRecorder::getVoiceState(void)
{
  delay(50);
  readData(EMPTY_DELETE_REGISTER ,recvBuf ,1);
  return recvBuf[0];
}

uint8_t DFRobot_VoiceRecorder::getTimeRemaining(void)
{
  delay(50);
  readData(TIMEREMAIN_REGISTER ,recvBuf ,1);
  return recvBuf[0];
}

uint8_t DFRobot_VoiceRecorder::getRecording(void)
{
  delay(50);
  readData(RECORDING_REGISTER ,recvBuf ,1);
  return recvBuf[0];
}
  
uint8_t DFRobot_VoiceRecorder::getPlaying(void)
{
  delay(50);
  readData(PLAYING_REGISTER ,recvBuf ,1);
  return recvBuf[0];
}

uint8_t DFRobot_VoiceRecorder::getVoiceSynthesis(void)
{
  delay(50);
  readData(SYNTHESIS_FLAG ,recvBuf ,1);
  return recvBuf[0];
}


DFRobot_VoiceRecorder_I2C::DFRobot_VoiceRecorder_I2C(TwoWire *pWire, uint8_t addr)
{
  _pWire = pWire;
  this->_I2C_addr = addr;
}

uint8_t DFRobot_VoiceRecorder_I2C::begin(void)
{
  _pWire->begin();
  _pWire->beginTransmission(_I2C_addr);
  if(_pWire->endTransmission() == 0)
    return 0;
  return 1;
}

void DFRobot_VoiceRecorder_I2C::writeData(uint8_t Reg ,uint8_t *Data ,uint8_t len)
{
  _pWire->beginTransmission(this->_I2C_addr);
  _pWire->write(Reg);
  for(uint8_t i = 0; i < len; i++)
    _pWire->write(Data[i]);
  _pWire->endTransmission();
}

uint8_t DFRobot_VoiceRecorder_I2C::readData(uint8_t Reg,uint8_t *Data,uint8_t len)
{
  int i=0;
  _pWire->beginTransmission(this->_I2C_addr);
  _pWire->write(Reg);
  _pWire->endTransmission();
  _pWire->requestFrom((uint8_t)this->_I2C_addr,(uint8_t)len);
  while (_pWire->available()){
    Data[i++]=_pWire->read();
  }
}