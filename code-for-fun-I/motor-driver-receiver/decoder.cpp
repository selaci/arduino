#include "decoder.h"

int Decoder::getCommand(byte* data) {
  return data[0] & 0xF0;
}

int Decoder::getX(byte* data) { 
  return (data[0] & 0x0F) << 6 | (data[1] >> 2);
}

int Decoder::getY(byte* data) {  
  return ((data[1] & 0x3) << 8) | data[2];
}
