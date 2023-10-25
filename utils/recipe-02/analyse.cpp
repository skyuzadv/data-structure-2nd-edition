#define _CRT_SECURE_NO_WARNINGS
#include <fcntl.h>
#include <sys/mman.h>  //linux
#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>

const int MAXN = 10000000;
const int MAXS = 60 * 1024 * 1024;
int numbers[MAXN];
char buf[MAXS];

void scanf_read() {
  freopen("data.txt", "r", stdin);
  for (int i = 0; i < MAXN; i++) scanf("%d", &numbers[i]);
}

void cin_read() {
  freopen("data.txt", "r", stdin);
  for (int i = 0; i < MAXN; i++) std::cin >> numbers[i];
}

void cin_read_nosync() {
  freopen("data.txt", "r", stdin);
  std::ios::sync_with_stdio(false);
  for (int i = 0; i < MAXN; i++) std::cin >> numbers[i];
}

void analyse(char* buf, int len = MAXS) {
  int i;
  numbers[i = 0] = 0;
  for (char* p = buf; *p && p - buf < len; p++)
    if (*p == ' ')
      numbers[++i] = 0;
    else {
      numbers[i] = numbers[i] * 10 + *p - '0';
    }
}

void fread_analyse() {
  freopen("data.txt", "rb", stdin);
  int len = fread(buf, 1, MAXS, stdin);
  buf[len] = '\0';
  analyse(buf, len);
}

// void read_analyse() {
//   int fd = open("data.txt", O_RDONLY);
//   int len = read(fd, buf, MAXS);
//   buf[len] = '\0';
//   analyse(buf, len);
// }

// void mmap_analyse() {
//   int fd = fopen("data.txt", O_RDONLY);
//   int len = lseek(fd, 0, SEEK_END);
//   char* mbuf = (char*)mmap(NULL, len, PROT_READ, MAP_PRIVATE, fd, 0);
//   analyse(mbuf, len);
// }

int main() {
  int start = clock();
  // DO SOMETHING
  printf("%.3lf\n", double(clock() - start) / CLOCKS_PER_SEC);
}