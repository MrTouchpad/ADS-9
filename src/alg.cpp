// Copyright 2022 NNTR-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  <cstdint>
#include  <vector>
#include  "tree.h"

static void dfs(Node* node, std::vector<char>& path,
                std::vector<std::vector<char>>& result, int depth) {
  if (depth > 0)
    path.push_back(node->value);

  if (node->children.empty()) {
    result.push_back(path);
  } else {
    for (Node* child : node->children)
      dfs(child, path, result, depth + 1);
  }

  if (depth > 0)
    path.pop_back();
}

static int64_t factorial(int n) {
  int64_t f = 1;
  for (int i = 2; i <= n; i++) f *= i;
  return f;
}

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
  std::vector<std::vector<char>> result;
  std::vector<char> path;
  dfs(tree.getRoot(), path, result, 0);
  return result;
}

std::vector<char> getPerm1(PMTree& tree, int num) {
  std::vector<std::vector<char>> all = getAllPerms(tree);
  if (num < 1 || num > static_cast<int>(all.size()))
    return {};
  return all[num - 1];
}

std::vector<char> getPerm2(PMTree& tree, int num) {
  if (num < 1) return {};

  int n = tree.getSize();
  int64_t total = factorial(n);
  if (num > total) return {};

  std::vector<char> result;
  Node* node = tree.getRoot();
  int64_t idx = num - 1;

  for (int depth = 0; depth < n; depth++) {
    int64_t blockSize = factorial(n - depth - 1);
    int childIdx = static_cast<int>(idx / blockSize);
    idx %= blockSize;
    node = node->children[childIdx];
    result.push_back(node->value);
  }

  return result;
}
