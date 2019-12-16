#include <sstream>
#include <queue>

#include "huffman.hpp"

using namespace std;

HuffmanTree::HuffmanTree(std::map<char, int> &count_map) {
  if (count_map.empty()) {
    std::stringstream ss;
    ss << "Compressor requires a non-empty text.";
    throw std::runtime_error{ss.str()};
  }

  std::priority_queue<TreeNode *, std::vector<TreeNode *>, HuffmanTree::NodeComparator> queue;

  for (auto a : count_map)
    queue.push(new TreeNode(a.first, a.second, true, nullptr, nullptr));

  while (queue.size() > 1) {
    TreeNode *node1 = queue.top();
    queue.pop();
    TreeNode *node2 = queue.top();
    queue.pop();
    queue.push(merge(node1, node2));
  }

  root = queue.top();
  queue.pop();
}

void HuffmanTree::recursiveNodeDelete(TreeNode *node) {
  if (node == nullptr) {
    return;
  }

  recursiveNodeDelete(node->getLeftTree());
  recursiveNodeDelete(node->getRightTree());

  delete node;
}

HuffmanTree::~HuffmanTree() {
  recursiveNodeDelete(root);
}

TreeNode *HuffmanTree::merge(TreeNode *node1, TreeNode *node2) {
  auto *new_node = new TreeNode(0, node1->getCount() + node2->getCount(), false, nullptr, nullptr);

  if (node1->getCount() < node2->getCount()) {
    new_node->setLeftTree(node1);
    new_node->setRightTree(node2);
  } else {
    new_node->setLeftTree(node2);
    new_node->setRightTree(node1);
  }

  new_node->setChar(std::max(node1->getChar(), node2->getChar()));

  return new_node;
}