#include <ctime>
#include <iostream>

// title 数组模拟求解约瑟夫环

static int arr[50] = {0};

int main(void) {
  int start = clock();
  int num = 10, m = 3;
  int tal = 0, i = 0, spk = 0;
  std::cin >> num >> m;
  while (1) {
    if (arr[i] == 0) {
      spk++;
      if (spk == m) spk = 0, tal++, arr[i] = -1, std::cout << i + 1 << " ";
      if (tal == num) break;
    }
    i++;
    if (i > num - 1) i = 0;
  }
  std::printf("\ntime: %.3lfs\n", double(clock() - start) / CLOCKS_PER_SEC);
  return 0;
}