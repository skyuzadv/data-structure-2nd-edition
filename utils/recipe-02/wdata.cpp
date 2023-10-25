#define _CRT_SECURE_NO_WARNINGS
#define SIZE 10000000
#include <cstdio>
#include <cstdlib>
#include <ctime>

int main(void) {
  int start = clock();
  freopen("data.txt", "w", stdout);
  srand(time(0));
  for (int i = 0; i < SIZE; i++) printf("%d ", rand());
  printf("%3lf\n", double(clock() - start) / CLOCKS_PER_SEC);
  return 0;
}