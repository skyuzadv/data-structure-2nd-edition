#include <iostream>

// title 递归法求解约瑟夫环

int josephus(int num, int m, int i) {
  if (i == 1) return (m - 1 + num) % num;
  return (josephus(num - 1, m, i - 1) + m) % num;
}

int main(void) {
  int num, m;
  std::cin >> num >> m;
  for (int i = 1; i <= num; i++) std::cout << josephus(num, m, i) + 1 << " ";
  return 0;
}