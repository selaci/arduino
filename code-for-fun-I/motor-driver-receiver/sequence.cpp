#include "sequence.h"

int Horizontal::next() {
  if (isIncreasing()) {
    return nextToRight();
  } else {
    return nextToLeft();
  }
}

bool Horizontal::isIncreasing() {
  return increasing;
}
  
int Random::next() {
  return random(0, 256); // [0, 256) => [0, 255]
}
