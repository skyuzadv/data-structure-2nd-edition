#define _CRT_SECURE_NO_WARNINGS
#define SIZE 10000000
#include <cstdio>
#include <ctime>
#include <iostream>

int numbers[SIZE];
int main() {
  int start = clock();
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  freopen("data.txt", "r", stdin);
  for (int i = 0; i < SIZE; i++) std::cin >> numbers[i];
  std::printf("%.3lf\n", double(clock() - start) / CLOCKS_PER_SEC);
  return 0;
}