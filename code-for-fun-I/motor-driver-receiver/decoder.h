#include "constants.h"

class Decoder {
  public:

  /*
   * Returns the command from the data.
   */
  int getCommand(byte* data);

  /*
   * Returns the X coordinate from the data if it has been defined.
   * Otherwise returns -1.
   */
  int getX(byte* data);

  /*
   * Returns the Y coordinate from the data if it has been defined.
   * Otherwise returns -1.
   */
  int getY(byte* data);
};
