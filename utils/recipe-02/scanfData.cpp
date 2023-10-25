#define _CRT_SECURE_NO_WARNINGS
#define SIZE 10000000
#include <cstdio>
#include <ctime>

int numbers[SIZE];

int main(void) {
  int start = clock();
  freopen("data.txt", "r", stdin);
  for (int i = 0; i < SIZE; i++) scanf("%d", &numbers[i]);
  printf("%.3lf\n", double(clock() - start) / CLOCKS_PER_SEC);
  return 0;
}