//**********************************************************
//********************2.8 案例分析与实现********************
// 解决目标：一元多项式运算
// 主要运算：加法 减法 乘法
// 主要特点：递增、递减、唯一
// 储存方式：数组下标法(静态数组) 数组元素为系数，其下标为指数
// 编译配置：-std=c++11，auto
// 文件名称：example 2-1 polynomial array
//**********************************************************

#ifndef __poly_array_hpp__
#define __poly_array_hpp__

#define _CRT_SECURE_NO_WARNINGS
#define SIZE 30
#include <cstdlib>
#include <iostream>

#include "file.cxx"

template <typename T>
class polyArray {
 public:
  std::size_t length;
  T* arr;
  int expn;

 public:
  polyArray() {
    std::printf("call default ctor function\n!");
    polyArray(SIZE);
  }
  polyArray(std::size_t size = SIZE) {
    arr = new T[size];
    length = 0;
    if (arr) {
      std::printf("memory allocat failed!\n");
      exit(1);
    }
    InitArray(size);
  }
  void InitArray(std::size_t size) {
    memset(arr, static_cast<T>(0), sizeof(arr[0]) * size);
    length = 0;
  }
  ~polyArray() {
    if (arr) delete[] arr;
    arr = nullptr;
  }
  static void inputData(polyArray<T> a, polyArray<T> b, const char* file) {
    std::size_t n1, n2;
    T coef;            // coef 系数
    std::size_t expn;  // expn 指数
    FILE* fp;

    if (utils::isFileNull(file)) {
      printf("file is null! please input some data, end up with '$' \n");
      fp = fopen(file, "w");
      int ch = getchar();
      while (ch != '$') {
        fputc(ch, fp);
        ch = getchar();
      }
      fclose(fp);
    } else {
      printf("file is good! \n");
      fp = fopen(file, "r");
      fscanf(fp, "%d", &n1);
      for (int i = 0; i < n1; i++) {
        fscanf(fp, "%d %d", &coef, &expn);
        a.arr[expn] = coef;
        a.expn = expn;
      }
      fscanf(fp, "%d", &n2);
      for (int i = 0; i < n2; i++) {
        fscanf(fp, "%d %d", &coef, &expn);
        a.arr[expn] = coef;
      }
      fclose(fp);
    }
  }
  polyArray<T> addArray(polyArray<T> a, polyArray<T> b) {
    polyArray<T> add;
    for (int i = 0; i < SIZE; i++) add.arr[i] = a.arr[i] + b.arr[i];
    return add;
  }
  polyArray<T> subArray(polyArray<T> a, polyArray<T> b) {
    polyArray<T> sub;
    for (int i = 0; i < SIZE; i++) sub.arr[i] = a.arr[i] - b.arr[i];
    return sub;
  }
  polyArray<T> mulArray(polyArray<T> a, polyArray<T> b) {
    polyArray<T> mul(2 * SIZE);
    int range = SIZE;
    for (int i = 0; i < SIZE; i++)
      for (int j = 0; j < SIZE; j++) {
        mul.arr[i + j] += a.arr[i] * b.arr[j];  // += is merge same expn item
      }
    return mul;
  }
  // 升序遍历
  void showArrayAscend(T c[], int range) {
    int flag = 0;
    for (int i = 0; i < range; i++)
      if (c[i] != 0) {
        if (flag) printf(" ");
        printf("%d %d", c[i], i);
        flag = 1;
      }
    if (!flag) printf("0 0");
    printf("\n");
  }
  // 降序遍历
  void showArrayDescend(T c[], int range, const char* file) {
    FILE* fp;
    fp = fopen(file, "a+");
    if (!fp) {
      printf("can not open file! \n");
      exit(0);
    }
    int flag = 0;
    for (int i = range; i >= 0; i--) {
      if (c[i] != 0) {
        if (flag) {
          fprintf(fp, " + ");
          printf(" + ");
        }
        fprintf(fp, "%dx^%d", c[i], i);
        printf("%dx^%d", c[i], i);
        flag = 1;
      }
    }
    fprintf(fp, "\n");
    if (!flag) printf("0 0");
    fclose(fp);
    printf("\n");
  }
};

#endif