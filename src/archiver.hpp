#ifndef HUFFMAN_ARCHIVER_H
#define HUFFMAN_ARCHIVER_H

#include "huffman.hpp"
#include "bitstring.hpp"

class Archiver {
private:
  std::map<std::vector<bool>, char> codes;

  std::map<char, std::vector<bool> > lookup;

public:
  Archiver() = default;

  void compress(std::ifstream &, std::ofstream &, HuffmanTree *);

  void decompress(std::ifstream &, std::ofstream &, HuffmanTree *);

  static void encodeTree(BitStringWrite &, TreeNode *);

  static TreeNode *decodeTree(BitStringRead &);

  void buildCodes(TreeNode *, std::vector<bool>);

  std::map<std::vector<bool>, char> &getCodes() {
    return codes;
  };

  static std::map<char, int32_t> &createFreqTable(const std::string &, std::map<char, int32_t> &);

  void buildTable(TreeNode *);

  std::map<char, std::vector<bool> > &getTable() {
    return lookup;
  };

};

#endif //HUFFMAN_ARCHIVER_H