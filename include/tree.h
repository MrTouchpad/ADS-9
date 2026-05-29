// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <algorithm>

struct Node {
  char value;
  std::vector<Node*> children;
  explicit Node(char v) : value(v) {}
};

class PMTree {
 private:
  Node* root;
  int   sz;

  void build(Node* node, std::vector<char> remaining) {
    std::sort(remaining.begin(), remaining.end());
    for (char c : remaining) {
      Node* child = new Node(c);
      node->children.push_back(child);
      std::vector<char> next;
      for (char r : remaining)
        if (r != c) next.push_back(r);
      build(child, next);
    }
  }

  void destroy(Node* node) {
    if (!node) return;
    for (Node* child : node->children)
      destroy(child);
    delete node;
  }

 public:
  explicit PMTree(const std::vector<char>& in) : sz(static_cast<int>(in.size())) {
    root = new Node('\0');
    build(root, in);
  }

  ~PMTree() { destroy(root); }

  PMTree(const PMTree&)            = delete;
  PMTree& operator=(const PMTree&) = delete;

  Node* getRoot() const { return root; }
  int   getSize() const { return sz; }
};

std::vector<std::vector<char>> getAllPerms(PMTree& tree);
std::vector<char>              getPerm1(PMTree& tree, int num);
std::vector<char>              getPerm2(PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
