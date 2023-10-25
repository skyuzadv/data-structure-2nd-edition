//**********************************************************
//*******************3.5.1 队列实现*************************
// 主要操作
// 1> 队列表示
// 2> 队列操作 初始化、队空、队长、入队、出队
// 3> 队列实现 顺序储存
//**********************************************************
#include <cstdio>
#include <cstdlib>
#include <iostream>

#define MAXQSIZE 100
typedef int QElemType;
typedef struct Queue {
  QElemType* base;  // 队列储存指针
  int front;        // 队头
  int rear;         // 队尾
} SeqQueue;

// 1.0 初始化队列
template <typename T1, typename T2>
bool InitialQueue(T1& Q) {
  Q.base = new T2[MAXQSIZE];
  if (!Q.base) return false;  // 分配失败
  Q.front = Q.rear = 0;
  return true;
}

// 1.1 销毁队列
template <typename T>
bool DestoryQueue(T& Q) {
  delete[] Q.base;
  Q.base = nullptr;
  Q.front = Q.rear = 0;
  return true;
}
// 1.2 队空
// 解决队头和队尾指针重合：
// 1> 设个标志区别队空和队满
// 2> 设变量记录元素个数
// 3> 预留一个元素空间
template <typename T>
bool QueueEmpty(T& Q) {
  if (!Q.base) return false;
  if (Q.front == Q.rear)
    return true;
  else
    return false;
}
// 1.3 队满
template <typename T>
bool QueueFull(T& Q) {
  if (!Q.base) return false;
  if (Q.front == (Q.rear + 1) % MAXQSIZE)
    return true;
  else
    return false;
}
// 1.4 队长
template <typename T>
int QueueLength(T& Q) {
  return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;  // 循环队表
}

// 2.0 入队
// 真溢出：front = 0, rear == maxqsize,再次入队
// 假溢出：front ≠ 0, rear == maxqsize,再次入队
// 解决假溢出问题方法：
// 1> 队中元素依次向队头方向移动(耗费时间)
// 2> 队列设想一个循环的表(循环队表)
template <typename T1, typename T2>
void EnQueue(T1& Q, T2 item) {
  if (!Q.base) return;
  if (QueueFull<SeqQueue>(Q)) return;  // 队满
  // Q.base[Q.rear++] = item; 					// 队尾入列
  Q.base[Q.rear] = item;
  Q.rear = (Q.rear + 1) % MAXQSIZE;  // 循环队表
}

// 2.1 出队
template <typename T1, typename T2>
void DeQueue(T1& Q, T2& item) {
  if (!Q.base) return;
  if (QueueEmpty<SeqQueue>(Q)) return;  // 队空
  // item = Q.base[Q.front];					// 队头出列
  // Q.front++;
  item = Q.base[Q.front];
  Q.front = (Q.front + 1) % MAXQSIZE;
}

// 3.0 取队头元素
template <typename T1, typename T2>
T2 GetHead(T1& Q) {
  if (!QueueEmpty<SeqQueue>(Q))  // 队为非空
    return Q.base[Q.front];
}

// 3.1 取队尾元素
template <typename T1, typename T2>
T2 GetTail(T1& Q) {
  if (!QueueEmpty<SeqQueue>(Q))  // 队为非空
    return Q.base[Q.rear];
}

// main()
int main(void) { exit(0); }
