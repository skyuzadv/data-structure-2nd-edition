
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

#include "file.cxx"

using namespace std;

#define SIZE        50
#define FILE_Import "polynomial-array.in"
#define FILE_Export "polynomial-array.ans"

int arr_1[SIZE];         // 数组1
int arr_2[SIZE];         // 数组2
int add_a[SIZE];         // 加法结果
int sub_b[SIZE];         // 减法结果
int mul_c[SIZE + SIZE];  // 乘法结果,数组长度 = x^(m + n)

int main(int argc, char** argv) {
  InitArray();
  int n1, n2, coef, expn;  // coef系数 expn指数
  FILE* fp;

  if (isFileNull(FILE_Import)) {
    printf("file is null! please input some data, end up with '$' \n");
    fp = fopen(FILE_Import, "w");
    int ch = getchar();
    while (ch != '$') {
      fputc(ch, fp);
      ch = getchar();
    }
    fclose(fp);
  } else {
    printf("file is good! \n");
    fp = fopen(FILE_Import, "r");
    fscanf(fp, "%d", &n1);
    for (int i = 0; i < n1; i++) {
      fscanf(fp, "%d %d", &coef, &expn);
      arr_1[expn] = coef;
    }
    fscanf(fp, "%d", &n2);
    for (int i = 0; i < n2; i++) {
      fscanf(fp, "%d %d", &coef, &expn);
      arr_2[expn] = coef;
    }
    fclose(fp);
  }

  showArrayAscend(arr_1, SIZE);
  showArrayAscend(arr_2, SIZE);

  addArray(arr_1, arr_2, SIZE);
  showArrayAscend(add_a, SIZE);
  showArrayDescend(add_a, SIZE, FILE_Export);

  subArray(arr_1, arr_2, SIZE);
  showArrayDescend(sub_b, SIZE, FILE_Export);

  mulArray(arr_1, arr_2, SIZE);
  showArrayDescend(mul_c, 2 * SIZE, FILE_Export);

  return 0;
}
