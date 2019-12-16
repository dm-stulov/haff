#include <fstream>
#include <deque>

#include "archiver.hpp"

std::map<char, int32_t> &Archiver::createFreqTable(const std::string &name, std::map<char, int32_t> &freq) {
  std::ifstream file(name);
  int next = 0;

  while ((next = file.get()) != EOF) {
    char uc = static_cast <char> (next);
    std::map<char, int32_t>::iterator iter;
    iter = freq.find(uc);
    if (iter != freq.end())
      iter->second += 1;
    else
      freq[uc] = 1;
  }

  return freq;
};

void Archiver::encodeTree(BitStringWrite &bw, TreeNode *node) {
  if (node->isLeaf()) {
    bw.writeBit(true);
    bw.writeByte(node->getChar());
    return;
  } else {
    bw.writeBit(false);
    encodeTree(bw, node->getLeftTree());
    encodeTree(bw, node->getRightTree());
  }
}

TreeNode *Archiver::decodeTree(BitStringRead &br) {
  if (br.readBit()) {
    return new TreeNode(br.readByte(), 0, true, nullptr, nullptr);
  } else {
    TreeNode *left = decodeTree(br);
    TreeNode *right = decodeTree(br);
    return new TreeNode(0, 0, false, left, right);
  }
}

void Archiver::buildCodes(TreeNode *n, std::vector<bool> cur) {
  if (n->isLeaf()) {
    codes[cur] = n->getChar();
    return;
  }

  cur.push_back(false);
  buildCodes(n->getLeftTree(), cur);
  cur.pop_back();
  cur.push_back(true);
  buildCodes(n->getRightTree(), cur);
}

void Archiver::buildTable(TreeNode *root) {
  std::deque<std::pair<TreeNode *, std::vector<bool> > > q;
  q.emplace_back(root, std::vector<bool>());

  while (!q.empty()) {
    TreeNode *node, *lc, *rc;
    std::vector<bool> code;
    node = q.front().first;
    code = q.front().second;
    q.pop_front();
    lc = node->getLeftTree();
    rc = node->getRightTree();
    if (lc) {
      std::vector<bool> code_cp(code);
      q.emplace_back(lc, (code.push_back(false), code));
      q.emplace_back(rc, (code_cp.push_back(true), code_cp));
    } else
      lookup.insert(make_pair(node->getChar(), code));
  }
}

void Archiver::compress(std::ifstream &ifs, std::ofstream &ofs, HuffmanTree *tree) {
  ifs.clear();
  ifs.seekg(0, ifs.beg);
  BitStringRead br(ifs);
  BitStringWrite bw(ofs);
  buildTable(tree->getRoot());
  encodeTree(bw, tree->getRoot());

  while (!ifs.eof()) {
    br.readByte();
    int sz = getTable()[br.getByte()].size();
    std::vector<bool> out = getTable()[br.getByte()];
    for (int i = 0; i < sz; i++)
      bw.writeBit(out[i]);
  }
}

void Archiver::decompress(std::ifstream &ifs, std::ofstream &ofs, HuffmanTree *tree) {
  ifs.clear();
  ifs.seekg(0, ifs.beg);
  BitStringRead br(ifs);
  BitStringWrite bw(ofs);
  TreeNode *t = decodeTree(br);
  std::vector<bool> cur;
  buildCodes(t, cur);
  std::vector<bool> v;
  bool b = false;

  while (!ifs.eof()) {
    while (!(getCodes().count(v)) && !ifs.eof()) {
      b = br.readBit();
      v.push_back(b);
    }
    if (ifs.eof())
      break;
    char s = getCodes()[v];
    v.clear();
    bw.writeByte(s);
  }
}
