#include <stdc++.hpp>

#include "huffman.hpp"
#include "archiver.hpp"

using namespace std::chrono;

int main() {
  high_resolution_clock::time_point t1 = high_resolution_clock::now();
  Archiver ar;

  //decoding
  HuffmanTree nt;
  std::ifstream ifs2("test.out");
  std::ofstream ofs2("result.txt");
  ar.decompress(ifs2, ofs2, &nt);


  high_resolution_clock::time_point t2 = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(t2 - t1).count();

  return 0;
}
