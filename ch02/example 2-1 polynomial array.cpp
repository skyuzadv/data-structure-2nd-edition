//**********************************************************
//********************2.8 案例分析与实现********************
// 解决目标：一元多项式运算
// 主要运算：加法 减法 乘法
// 主要特点：递增、递减、唯一
// 储存方式：数组下标法(静态数组) 数组元素为系数，其下标为指数
// 编译配置：-std=c++11，auto
//**********************************************************

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

#define SIZE     1000
#define FILENAME "polynomial array.ans"

int arr_1[SIZE];        // 数组1
int arr_2[SIZE];        // 数组2
int arr_a[SIZE];        // 加法结果
int arr_b[SIZE];        // 减法结果
int arr_c[SIZE + SIZE]; // 乘法结果,数组长度 = x^(m + n)

void addArray(int a[], int b[], int range) {
  for (int i = 0; i < range; i++)
    arr_a[i] = arr_1[i] + arr_2[i];
}

void subArray(int a[], int b[], int range) {
  for (int i = 0; i < range; i++)
    arr_b[i] = arr_1[i] - arr_2[i];
}

void mulArray(int a[], int b[], int range) {
  for (int i = 0; i < range; i++)
    for (int j = 0; j < range; j++)
      arr_c[i + j] +=
          arr_1[i] * arr_2[j]; // x^(m + n) = x^m + x^n,合并同类项(+=)
}

void resetArray() {
  memset(arr_1, 0, sizeof(arr_1));
  memset(arr_2, 0, sizeof(arr_2));
  memset(arr_a, 0, sizeof(arr_a));
  memset(arr_b, 0, sizeof(arr_b));
  memset(arr_c, 0, sizeof(arr_c));
}

// 升序显示
void showArray_H(int c[], int range) {
  int flag = 0;
  for (int i = 0; i < range; i++) {
    if (c[i] != 0) {
      if (flag)
        printf(" ");
      flag = 1;
      printf("%d %d", c[i], i);
    }
  }
  // 假设两个相同多项式做减法运算，那么同类项抵消，产生0个多项式
  // 根据算法至少一个输出原则，所以应输出0 0
  if (!flag)
    printf("0 0");
  printf("\n");
}

// 降序显示
void showArray_L(int c[], int range) {
  FILE* fp;
  fp = fopen("polynomial array.ans", "w");
  if (!fp) {
    printf("Can't open file! \n");
    exit(0);
  }
  int flag = 0;
  for (int i = range; i >= 0; i--) {
    if (c[i] != 0) {
      if (flag)
        printf(" ");
      flag = 1;
      fprintf(fp, "%dx^%d", c[i], i);
      printf("%dx^%d", c[i], i);
    }
  }
  // 假设两个相同多项式做减法运算，那么同类项抵消，产生0个多项式
  // 根据算法至少一个输出原则，所以应输出0 0
  if (!flag)
    printf("0 0");
  fclose(fp);
  printf("\n");
}

// 判定文本文件是否为空
// 文件空，返回值为1
int isfileNull(const char* fileName) {
  FILE* fp = fopen(fileName, "r");
  if (!fp) {
    printf("Can't open file! \n");
    return 1;
  }
  int ch = fgetc(fp);
  fclose(fp);
  if (ch == EOF)
    return 1;
  else
    return 0;
}

int main(int argc, char** argv) {
  resetArray();
  int n1, n2, coef, expn; // coef系数 expn指数
  FILE* fp;
  if (isfileNull("polynomial array.in")) {
    printf("file is null! please input some data, end with '$' \n");
    fp = fopen("polynomial array.in", "w"); // write data
    int ch = getchar();                     // 读取整数
    while (ch != '$') {
      fputc(ch, fp);
      ch = getchar();
    }
    fclose(fp);
  } else {
    printf("file is good! \n");
    fp = fopen("polynomial array.in", "r"); // read data
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

  // add
  addArray(arr_1, arr_2, SIZE);
  // showArray_H(arr_a, SIZE);
  showArray_L(arr_a, SIZE);
  // sub
  subArray(arr_1, arr_2, SIZE);
  // showArray_L(arr_b, SIZE);
  //  mul
  mulArray(arr_1, arr_2, SIZE);
  showArray_L(arr_c, 2 * SIZE);

  return 0;
}
