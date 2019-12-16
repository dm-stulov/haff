#include "bitstring.hpp"

BitStringWrite::BitStringWrite(std::ostream &_out_f) : _byte(0), _pos(0), _out_f(_out_f) {}

void BitStringWrite::writeBit(bool bit) {
  if (_pos == 8)
    flush();
  if (bit == 1) {
    _byte |= (1 << _pos);
  }
  _pos++;
}

void BitStringWrite::writeByte(char b) {
  for (int i = 0; i < 8; i++)
    writeBit((b >> i) & 1);
}

void BitStringWrite::flush() {
  if (_pos != 0) {
    _out_f.write(&_byte, sizeof(char));
    _pos = 0;
    _byte = 0;
  }
}

BitStringRead::BitStringRead(std::istream &_in_f) : _pos(8), _in_f(_in_f) {}

bool BitStringRead::readBit() {
  if (_pos == 8) {
    _in_f.read(&_byte, sizeof(char));
    _pos = 0;
  }
  return (_byte >> _pos++) & (char) 1;
}

char BitStringRead::readByte() {
  char sym = (char) 0;
  for (int i = 0; i < 8; i++) {
    sym |= ((1 & readBit()) << (i));
  }
  return sym;
}

BitStringWrite::~BitStringWrite() {
  flush();
}