//**********************************************************
//*******************3.1 顺序栈的表示和实现*****************
// 主要操作
// 常用操作：判定栈空、栈满、压栈、弹栈、读栈等
// 储存方式：顺序储存
//**********************************************************
#include <iostream>

#if 1
#define DEBUG
#else
#undef DEBUG
#endif

#define STACKSIZE 100  // 栈最大容量
typedef int SElemType;
typedef struct seqstack {
  SElemType* base;
  SElemType* top;
  int stacksize;
} seqstack;

// 初始化函数
// 操作结果：构造一个空栈S
template <typename T>
bool InitialStack(T* s) {
#ifdef DEBUG
  std::cout << "\n" << __PRETTY_FUNCTION__ << std::endl;
#endif
  s->base = new SElemType[STACKSIZE];
  if (!s->base) return false;  // 分配失败
  s->top = s->base;
  s->stacksize = STACKSIZE;
  return true;
}
// 销毁函数
// 初始条件：栈S已存在，
// 操作结果：栈S被销毁
template <typename T>
void DestoryStack(T* s) {
#ifdef DEBUG
  std::cout << "\n" << __PRETTY_FUNCTION__ << std::endl;
#endif
  if (s->base) delete[] s->base;
  s->stacksize = 0;
  s->top = s->base = NULL;
}

// 栈长度
// 初始条件：栈S已存在
// 操作结果：返回S的元素个数，即为栈的长度
template <typename T>
int StackLength(T* s) {
  if (s->base)
    return s->top - s->base;
  else
    return 0;
}

// 栈空判定
// 栈空标志：base == top
// 初始条件：栈S已存在
// 操作结果：若栈为空栈，则返回true，否则false
template <typename T>
bool StackEmpty(T* s) {
  if (s->base == s->top) return true;
  return false;
}

// 栈满判定
// 上溢：栈满,继续压栈
// 下溢：栈空,继续弹栈, 一般作为结束条件
// 栈满标志：top-base == stacksize
// 初始条件：栈S已存在
// 操作结果：若栈为满栈，则返回true，否则false
template <typename T>
bool StackFull(T* s) {
  if (s->top - s->base == s->stacksize) return true;
  return false;
}

// 栈满处理方法
// 1.报错返回操作系统
// 2.分配更大空间，作为栈的储存空间，将原栈内容拷贝新栈
// 数据海量，相当占用时间

// 清空栈
// 算法思路：栈底和栈顶指针重合
// 初始条件：栈S已存在
// 操作结果：将s清空为空栈
template <typename T>
void ClearStack(T& s) {
  if (s->base) s->top = s->base;
}

// 压栈
// 初始条件：栈S已存在，是否栈满
// 操作结果：插入元素e为新的栈顶元素
template <typename T1, typename T2>
bool Push(T1* s, T2 item) {
  if (s->top - s->base == s->stacksize) return false;
  //	*s->top++ = item;
  *s->top = item;
  s->top++;
  return true;
}

// 弹栈
// 初始条件：栈S已存在，是否栈空
// 操作结果：删除S的栈顶元素an，并用e返回其值
template <typename T1, typename T2>
bool Pop(T1* s, T2& item) {
  if (s->base == s->top) return false;
  //	item = *(--s->top);
  --s->top;
  item = *s->top;
  return true;
}

// 读栈
// 初始条件：栈S存在且非空
// 操作结果：用e返回S的栈顶元素
template <typename T1, typename T2>
bool GetTop(T1* s, T2& item) {
  if (s->base == s->top) return false;
  //	item = *(--s->top);
  //	++s->top;
  item = *(s->top - 1);
  return true;
}
