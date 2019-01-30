#include "constants.h"

#ifndef Receiver_h
#define Receiver_h

#include "Arduino.h"

/*
 * This code is based on this excellent post, written by Robin2:
 *
 * http://forum.arduino.cc/index.php?topic=396450.0
 *
 * This library extracts messages from the serial channel. It uses a byte to
 * distinguish when a message starts and another byte to know when the
 * message ends. These byte can actually be the same. As an example,
 * messages can be:
 *
 * ^Some set of strings$
 *
 * In this case "^" and "$" are the characters that indicate when the message
 * starts and when the message ends.
 *
 * This receiver reads bytes one by one. It does not use other functions in
 * the Arduino library because they may be blocking. This means to be used in
 * applications where the Arduino needs to read from the serial channel and do
 * other things as fast as possible.
 *
 * It has a limit of bytes that can be stored, indicated by one of the
 * instance variables. If the message is larger than the number of bytes,
 * the last available bytes in this receiver will be continuously
 * overwritten by the next bytes of the message.
 */
class Receiver {
  private:

  /*
   * Maximum number of bytes that can be read.
   */
  int _nBytes;

  /*
   * Bytes from the message that have been received so far.
   */
  byte* _receivedBytes;

  /*
   * The byte that indicates when a message starts.
   */
  byte _startMarker;

  /*
   * The byte that indicates when a message ends.
   */
  byte _endMarker;

  /*
   * A flag that indicates that a message has been received and it's waiting
   * to be read.
   */
  boolean _hasData;

  /*
   * A flag that indicates the beginning of a message has been received.
   */
  boolean _recvInProgress;

  /*
   * The number of bytes of the message that have been read so far.
   */
  byte _ndx = 0;

  public:

  /*
   * The constructor.
   *
   * "startMarker" , the byte that signals a new message starts.
   * "endMarker"   , the byte that signals a message has ended.
   */
  Receiver(byte startMarker, byte endMarker);

  /*
   * Read as many bytes of possible.
   */
  void read();

  /*
   * Return true if there is a message stored in this receiver, false otherwise.
   */
  boolean hasData();

  /*
   * Return the message stored in this receiver and sets the receiver ready to
   * receive next message.
   */
  byte* getData();
};

#endif
