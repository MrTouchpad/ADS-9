// Copyright 2022 NNTU-CS
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <cstdint>
#include <string>
#include "tree.h"

static double measureAllPerms(int n) {
  std::vector<char> in;
  for (int i = 0; i < n; i++) in.push_back(static_cast<char>('1' + i));
  PMTree tree(in);
  auto t0 = std::chrono::high_resolution_clock::now();
  getAllPerms(tree);
  auto t1 = std::chrono::high_resolution_clock::now();
  return std::chrono::duration<double, std::micro>(t1 - t0).count();
}

static double measureGetPerm1(int n, int num) {
  std::vector<char> in;
  for (int i = 0; i < n; i++) in.push_back(static_cast<char>('1' + i));
  PMTree tree(in);
  auto t0 = std::chrono::high_resolution_clock::now();
  getPerm1(tree, num);
  auto t1 = std::chrono::high_resolution_clock::now();
  return std::chrono::duration<double, std::micro>(t1 - t0).count();
}

static double measureGetPerm2(int n, int num) {
  std::vector<char> in;
  for (int i = 0; i < n; i++) in.push_back(static_cast<char>('1' + i));
  PMTree tree(in);
  auto t0 = std::chrono::high_resolution_clock::now();
  getPerm2(tree, num);
  auto t1 = std::chrono::high_resolution_clock::now();
  return std::chrono::duration<double, std::micro>(t1 - t0).count();
}

static int64_t factorial(int n) {
  int64_t f = 1;
  for (int i = 2; i <= n; i++) f *= i;
  return f;
}

int main() {
  std::vector<char> in = {'1', '2', '3'};
  PMTree tree(in);

  std::cout << "All permutations of {1,2,3}:\n";
  for (const auto& p : getAllPerms(tree)) {
    for (char c : p) std::cout << c;
    std::cout << "\n";
  }

  std::cout << "\ngetPerm1(tree, 1): ";
  for (char c : getPerm1(tree, 1)) std::cout << c;

  std::cout << "\ngetPerm2(tree, 2): ";
  for (char c : getPerm2(tree, 2)) std::cout << c;
  std::cout << "\n";

  std::ofstream csv("result/timing.csv");
  csv << "n,getAllPerms_us,getPerm1_us,getPerm2_us\n";

  std::cout << "\nn\tgetAllPerms(us)\tgetPerm1(us)\tgetPerm2(us)\n";

  for (int n = 2; n <= 9; n++) {
    int64_t total = factorial(n);
    int num = static_cast<int>(1 + std::rand() % total);

    double tAll = measureAllPerms(n);
    double tP1  = measureGetPerm1(n, num);
    double tP2  = measureGetPerm2(n, num);

    std::cout << n << "\t" << tAll << "\t" << tP1 << "\t" << tP2 << "\n";
    csv << n << "," << tAll << "," << tP1 << "," << tP2 << "\n";
  }

  csv.close();
  return 0;
}
