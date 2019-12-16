#include <stdc++.hpp>

#include "huffman.hpp"
#include "archiver.hpp"

using namespace std::chrono;

int main() {
  high_resolution_clock::time_point t1 = high_resolution_clock::now();
  Archiver ar;

  //encoding
  std::map<char, int32_t> m;
  Archiver::createFreqTable("test.in", m);
  HuffmanTree t(m);
  std::ifstream ifs("test.in");
  std::ofstream ofs("test.out");
  ar.compress(ifs, ofs, &t);

  high_resolution_clock::time_point t2 = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(t2 - t1).count();

  return 0;
}

