#include "receiver.h"

Receiver::Receiver(char startMarker, char endMarker) {
  _nChars = 32;
  _receivedChars = new char[_nChars];
  _startMarker = startMarker;
  _endMarker = endMarker;
  _hasData = false;
  _recvInProgress = false;
}

void Receiver::read() {
    while (Serial.available() > 0 && _hasData == false) {
      char rc = Serial.read();

      if (_recvInProgress == true) {
        if (rc != _endMarker) {
          _receivedChars[_ndx] = rc;
          _ndx++;
          if (_ndx >= _nChars) {
            _ndx = _nChars - 1;
          }
        } else {
          _receivedChars[_ndx] = '\0'; // terminate the string
          _recvInProgress = false;
          _ndx = 0;
          _hasData = true;
        }
      }
      else if (rc == _startMarker) {
        _recvInProgress = true;
      }
    }
  }

boolean Receiver::hasData() {
  return _hasData;
}

String Receiver::getData() {
  _hasData = false;
  return String(_receivedChars);
}
