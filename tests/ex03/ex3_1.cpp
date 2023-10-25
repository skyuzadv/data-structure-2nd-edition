#include <iostream>

#include "./ch03/seqStack.hpp"

int main(int argc, char** argv) {
  seqstack* data;
  InitialStack(data);
  int n = 555;
  while (n) {
    Push(data, n % 8);
    n /= 8;
  }
  int item;
  while (!StackEmpty(data)) {
    Pop(data, item);
    std::cout << item;
  }
  DestoryStack(data);
  return 0;
}