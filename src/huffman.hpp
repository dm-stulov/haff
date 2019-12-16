#ifndef HUFFMAN_HUFFMAN_H
#define HUFFMAN_HUFFMAN_H

//#include <sys/param.h>
#include <iostream>
#include <map>
#include <vector>

class TreeNode {
public:
  TreeNode(char c, int cnt, bool l, TreeNode *lc, TreeNode *rc) : character(c), count(cnt), is_leaf(l), left(lc),
                                                                  right(rc) {};

  TreeNode() : character(0), count(0), is_leaf(false), left(nullptr), right(nullptr) {}

  int getCount() const {
    return this->count;
  };

  char getChar() const {
    return this->character;
  };

  TreeNode *getLeftTree() const {
    return this->left;
  };

  TreeNode *getRightTree() const {
    return this->right;
  };

  void setLeftTree(TreeNode *n) {
    this->left = n;
  };

  void setRightTree(TreeNode *n) {
    this->right = n;
  };

  void setChar(char c) {
    this->character = c;
  };

  bool isLeaf() {
    return is_leaf;
  }

  void setLeaf(bool num) {
    this->is_leaf = num;
  }

private:
  char character;
  int count;
  bool is_leaf;
  TreeNode *left;
  TreeNode *right;
};

class HuffmanTree {
public:

  explicit HuffmanTree(std::map<char, int> &);

  HuffmanTree() {
    root = new TreeNode(0, 0, false, nullptr, nullptr);
  };

  ~HuffmanTree();

  TreeNode *getRoot() const {
    return this->root;
};

class NodeComparator {
public:
  bool operator()(const TreeNode *const lhs, const TreeNode *const rhs) {
    if (lhs->getCount() == rhs->getCount()) {
      return lhs->getChar() > rhs->getChar();
    }
    return lhs->getCount() > rhs->getCount();
  }
};

  static TreeNode *merge(TreeNode *node1, TreeNode *node2);

  static void recursiveNodeDelete(TreeNode *node);
  // uint32_t check_count(uint32_t count);

private:
  TreeNode *root;
};


#endif