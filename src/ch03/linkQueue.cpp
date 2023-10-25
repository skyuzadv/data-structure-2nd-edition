//**********************************************************
//*******************3.5.2 队列实现*************************
// 主要操作
// 1> 队列表示
// 2> 队列操作 初始化、队空、队长、入队、出队
// 3> 队列实现 链式储存
//**********************************************************
#include <cstdio>
#include <cstdlib>
#include <iostream>

#define MAXQSIZE 100
typedef int QElemType;
typedef struct Qnode {
  QElemType data;
  struct Qnode* next;
} QNode, *QueuePtr;

typedef struct {
  QueuePtr front;  // 队头指针
  QueuePtr rear;   // 队尾指针
} LinkQueue;

// 1.0 初始化队列
template <typename T1, typename T2>
bool InitialQueue(T1& Q) {
  Q.front = Q.rear = new T2;
  if (!Q.front) return false;  // 分配失败
  Q.front->next = NULL;
  return true;
}
// 1.1 销毁队列
template <typename T1, typename T2>
bool DestoryQueue(T1& Q) {
  T2* r;
  while (Q.front) {
    r = Q.front->next;
    delete Q.front;
    Q.front = r;
    // Q.rear = Q.front->next; delete Q.front; Q.front = Q.rear;
  }
}

// 2.0 入队
template <typename T1, typename T2>
bool EnQueue(T1& Q, T2 item) {
  QNode* p = new QNode;
  if (!p) return false;  // 分配失败
  p->data = item;
  p->next = NULL;
  Q.rear->next = p;
  Q.rear = p;
  return true;
}

// 2.1 出队
template <typename T1, typename T2>
bool DeQueue(T1& Q, T2& item) {
  if (Q.rear == Q.front) return false;
  QNode* r;
  r = Q.front->next;
  item = r->data;
  Q.front->next = r->next;
  if (r == Q.rear) Q.rear = Q.front;  // 删除结点等于尾结点
  delete r;
  return true;
}

// 3.0 取队头元素
template <typename T1, typename T2>
T2 GetHead(T1& Q) {
  return Q.front->next->data;
}

// 3.1 取队尾元素
template <typename T1, typename T2>
T2 GetTail(T1& Q) {
  return Q.rear->data;
}

// main()
int main(void) {
  system("chcp 65001");
  exit(0);
}
