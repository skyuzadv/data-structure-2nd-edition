//**********************************************************
//*******************3.2 链栈的表示和实现*******************
// 主要操作
// 常用操作：判定栈空、栈满、压栈、弹栈、读栈等
// 储存方式：链式储存(链栈)
// 链栈操作：运算受限的单链表，只能在链表头部进行操作
//**********************************************************
#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

typedef int SElemType;
typedef struct StackNode {
  SElemType data;
  struct StackNode *next;
} StackNode, *LinkStack;

// main()
int main(int argc, char **argv) { return 0; }

// 1. 0 初始化函数
// 操作结果：构造空栈，栈顶指针置为空
template <typename T> bool InitialStack(T &S) {
  S = NULL;
  return true;
}
// 1.1 销毁函数
template <typename T> bool DestoryStack(T &S) {
  if (!S)
    return;
  StackNode *r;
  while (S) {
    r = S;
    S = S->next;
    delete r;
  }
  return true;
}

// 2.0 栈空判定
template <typename T> bool StackEmpty(T &S) {
  if (S == NULL)
    return true;
  else
    return false;
}

// 3.0 压栈
template <typename T1, typename T2> bool Push(T1 &S, T2 e) {
  StackNode *p = new StackNode;
  p->data = e;
  p->next = S;
  S = p;
  return true;
}

// 4.0 弹栈
template <typename T1, typename T2> bool Pop(T1 &S, T2 &e) {
  if (S == NULL)
    return false;
  StackNode *r;
  e = S->data;
  r = S;
  S = S->next;
  delete r;
  return true;
}

// 5.0 读栈
template <typename T1, typename T2> T2 GetTop(T1 *S) {
  if (S)
    return S->data;
}

void foo() {
  FILE *fpout;
  char ch;
  if ((fpout = fopen("file_a.dat", "w")) == NULL) {
    printf("can't open the file! \n");
    exit(0);
  }
  ch = getchar();
  while (ch != '$') {
    fputc(ch, fpout);
    ch = getchar();
  }
  fclose(fpout);
}
