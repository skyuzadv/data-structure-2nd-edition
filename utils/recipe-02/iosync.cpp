#include <cstdio>
#include <iostream>

int main(void) {
  std::ios::sync_with_stdio(false);
  std::cout.tie(0);
  std::cout << "a\n";
  std::printf("b\n");
  std::cout << "c\n";
  return 0;
}