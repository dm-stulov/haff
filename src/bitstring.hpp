#ifndef HUFFMAN_BITSTRING_H
#define HUFFMAN_BITSTRING_H

#include <iostream>
#include <vector>

class BitStringWrite {

private:
  char _byte;
  int _pos;
  std::ostream &_out_f;

public:
  explicit BitStringWrite(std::ostream &_out_f);

  ~BitStringWrite();

  void writeBit(bool bit);

  void writeByte(char b);

  void flush();
};

class BitStringRead {

private:
  char _byte{};
  int _pos;
  std::istream &_in_f;

public:

  explicit BitStringRead(std::istream &_in_f);

  char readByte();

  bool readBit();

  char getByte() {
    return _byte;
  }

};

#endif
