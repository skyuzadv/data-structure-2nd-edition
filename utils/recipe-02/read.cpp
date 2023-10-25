#define _CRT_SECURE_NO_WARNINGS
#define cinios \
  (std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);)

#include <cstdio>
#include <iostream>

// cin <cinios ≈ scanf < my ≈ zyh < hzwer < fread

// my
inline void read_a(int& n) {
  char ch = getchar();
  bool flag = 0;
  n = 0;
  while (ch < '0' || ch > '9')
    ch == '-' ? flag = 1, ch = getchar() : ch = getchar();
  while (ch >= '0' && ch <= '9') n = n * 10 + ch - '0', ch = getchar();
  flag == 1 ? n = -n : n = n;
}

// zsh
inline void read_b(int& x) {
  char ch = getchar();
  x = 0;
  int f = 1;
  for (; !isdigit(ch); ch = getchar())
    if (ch == '-') f = -1;
  for (; isdigit(ch); ch = getchar()) x = x * 10 + ch - '0';
  x = x * f;
}
// hzwer
inline int read_c(void) {
  int x = 0, f = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-') f = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
  return x * f;
}
// fread
inline char nc() {
  static char buf[100000], *p1 = buf, *p2 = buf;
  return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2)
             ? EOF
             : *p1++;
}
inline int read_d() {
  char ch = nc();
  int sum = 0;
  int flag = 1;
  while (!(ch >= '0' && ch <= '9')) {
    ch = nc();
    if (ch == '-') flag = -1;
  }
  while (ch >= '0' && ch <= '9') sum = sum * 10 + ch - '0', ch = nc();
  return sum * flag;
}