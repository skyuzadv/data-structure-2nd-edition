#define _CRT_SECURE_NO_WARNINGS
#define cinios \
  (std::ios_snyc_with_stdio(false), std::cin.tie(0), std::cout.tie(0);)
#include <cstdio>
#include <iostream>

int main(void) {
  // FILE* fp = fopen("polynomial-array.ans", "r");
  // if (fp == NULL)
  //   std::printf("file is null\n");
  // else {
  //   std::printf("file is good\n");
  // }
  // fclose(fp);

  // FILE* fout = fopen("data.txt", "w");
  // freopen("data.txt", "w", stdout);
  // std::printf("hello world!");
  // fclose(fout);
  // fclose(stdout);
  // return 0;

  // freopen("1234.in", "r", stdin);
  // freopen("1234.out", "w", stdout);
  // double a, b, r;
  // int k;
  // std::cin >> a >> b;
  // k = int(a + b);
  // r = a - b;
  // std::printf("%g %d", r, k);
  // fclose(stdin);
  // fclose(stdout);

  // int a, b;
  // freopen("1234.in", "r", stdin);
  // freopen("1234.out", "w", stdout);
  // while (std::cin >> a >> b) std::cout << a + b << std::endl;
  // fclose(stdin);
  // fclose(stdout);

  // int a, b;
  // freopen("1234.in", "r", stdin);
  // freopen("1234.out", "w", stdout);
  // while (~scanf("%d%d", &a, &b)) printf("%d\n", a + b);
  // fclose(stdin);
  // fclose(stdout);

  // 在windows/DOS，读文件后用freopen("CON", "r", stdin)，写文件后
  // freopen("CON", "w", stdout)。 在linux中，控制台设备是
  // /dev/console：freopen("/dev/console", "r", stdin)。
  int a, b;
  freopen("1234.in", "r", stdin);
  freopen("1234.out", "w", stdout);
  while (~scanf("%d %d", &a, &b)) printf("%d\n", a + b);
  // fclose(stdin);
  // fclose(stdout);
  freopen("CON", "r", stdin);
  freopen("CON", "w", stdout);
  printf("Hello World\n");
  scanf("%d %d", &a, &b);
  printf("a * b = %d\n", a * b);

  return 0;
}