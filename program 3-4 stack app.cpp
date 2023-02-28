//**********************************************************
//*******************3.4 栈与递归***************************
// 主要操作
// 1> 尾递归、单向递归 -> 循环结构
// 2> 自用栈模拟系统的运行时栈
// 3> 系统栈和用户栈
//**********************************************************
#include <cstdio>
#include <cstdlib>
#include <iostream>


// 1.1 尾递归
long long int Fact(long n) {
  if (n == 1)
    return 1;
  else
    return n * Fact(n - 1);
}
// 1.2 尾递归 -> 循环结构
long long int fact(long n) {
  int t = 1;
  for (int i = 1; i <= n; i++)
    t = t * i;
  return t;
}
// 2.1 单向递归
long long int Fibo(long n) { // Fibonacci数列
  if (n == 1 || n == 2)
    return 1;
  else
    return Fibo(n - 1) + Fibo(n - 2);
}
// 2.2 单向递归 -> 循环结构
long long int fibo(long n) {
  int t1, t2, t3;
  if (n == 1 || n == 2)
    return 1;
  else {
    t1 = 1;
    t2 = 1;
    for (int i = 3; i <= n; i++) { // i = 3
      t3 = t2 + t1;
      t1 = t2;
      t2 = t3;
    }
  }
  return t3;
}

// main()
int main(int argc, char **argv) {
  int n = 3;
  printf("Fact(%d) = %d\n", n, Fact(n)); // n = 2, ans = 6
  printf("fact(%d) = %d\n", n, fact(n)); // n = 2, ans = 6
  printf("Fibo(%d) = %d\n", n, Fibo(n)); // n = 2, ans = 2
  printf("fibo(%d) = %d\n", n, fibo(n)); // n = 2, ans = 2
  return 0;
}
