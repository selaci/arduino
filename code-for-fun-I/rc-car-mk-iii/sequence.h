#ifndef SEQUENCE_H
#define SEQUENCE_H

class Sequence {
public:
  virtual unsigned int next();
  virtual ~Sequence();
};

class Circular : public Sequence {
private:
  unsigned int _number;

public:
  unsigned int next();
};

class DoubleCircular : public Sequence {
private:
  int _index = -1;
  unsigned int _sequence[8] = { 257, 514, 1028, 2056, 4112, 8224, 16448,
                            32896 };

public:
  unsigned int next();
};

class StarTrek : public Sequence {
private:
  int _index = -1;
  unsigned int _sequence[4] = { 33153, 16962, 9252, 6168 };

public:
  unsigned int next();
};

class KnightRider : public Sequence {
private:
  int _index = -1;
  unsigned int _sequence[14] = { 32769, 16386, 8196, 4104, 2064, 1056, 576,
                             384, 576, 1056, 2064, 4104, 8196, 16386 };

public:
  unsigned int next();
};

class DoubleKnightRider : public Sequence {
private:
  int _index = -1;
  unsigned int _sequence[14] = { 257, 514, 1028, 2056, 4112, 8224, 16448,
                             32896, 16448, 8224, 4112, 2056, 1028, 514 };

public:
  unsigned int next();
};

class FillUp : public Sequence {
private:
  unsigned int _cumulated = 0;
  unsigned int _max = 32768;
  unsigned int _number = 0;

public:
  unsigned int next();
};
#endif
