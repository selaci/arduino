#include "receiver.h"

Receiver::Receiver(byte startMarker, byte endMarker) {
  _nBytes = 64;
  _receivedBytes = new byte[_nBytes];
  _startMarker = startMarker;
  _endMarker = endMarker;
  _hasData = false;
  _recvInProgress = false;
}

void Receiver::read() {
    while (Serial.available() > 0 && _hasData == false) {
      if (DEBUG) {
        Serial.print("In receiver. Available bytes: ");
        Serial.println(Serial.available());
      }
      
      byte rc = Serial.read();

      if (_recvInProgress == true) {
        if (rc != _endMarker) {
          _receivedBytes[_ndx] = rc;
          _ndx++;
          if (_ndx >= _nBytes) {
            _ndx = _nBytes - 1;
          }
        } else {
          _recvInProgress = false;
          _hasData = true;
        }
      }
      else if (rc == _startMarker) {
        _recvInProgress = true;
        _ndx = 0;
      }
    }
  }

boolean Receiver::hasData() {
  return _hasData;
}

byte* Receiver::getData() {
  _hasData = false;
  
  byte data[_ndx];

  for (int i = 0; i < _ndx; i++) {
    data[i] = _receivedBytes[i];
  }

  if (DEBUG) {
    Serial.print("In decoder. ");
    Serial.print("data[0]: ");
    Serial.print(data[0]);
    Serial.print(", data[1]: ");
    Serial.print(data[1]);
    Serial.print(", data[2]: ");
    Serial.println(data[2]);
  }
  
  return data;
}

