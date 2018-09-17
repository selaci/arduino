# Introduction

This is a library that I use in my sketches in order to read messages from the
serial channel.

This code is based on this excellent post, written by Robin2:

http://forum.arduino.cc/index.php?topic=396450.0

This library extracts messages from the serial channel. It uses a character to
distinguish when a message starts and another character to know when the message
ends. These characters can actually be the same. As an example, messages can be:

^Some set of strings$

In this case, "^" and "$" are the characters that indicate when the message
starts and when the message ends.

This receiver reads characters one by one. It does not use other functions in the
Arduino library because they may be blocking. This means to be used in
applications where the Arduino needs to read from the serial channel and do
other things as fast as possible.

It has a limit of characters that can be stored, indicated by one of the
instance variables. If the message is larger than the number of characters, the
last available character in this receiver will be continuously overwritten by
the next character of the message.

You can use this library as follows:

```
#include <receiver.h>

void setup() {
  Serial.begin(9600);
}

Receiver receiver('^', '$');

void loop() {
  receiver.read();

  if (receiver.hasData()) {
    String message = receiver.getData();
    //
  }
}
```
