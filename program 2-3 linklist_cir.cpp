//**********************************************************
//**************2.3 单循环链表******************************
// 单循环链表:circular linked list
// 循环链表中没有NULL指针
// 循环链表设立尾指针,访问首元结点、尾结点时间复杂度:O(1)
// 编程语言：c、c++
//**********************************************************
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <malloc.h>
#include <stdbool.h>

using namespace std;

// 函数结果状态代码
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

// 定义数据类型
typedef int STATUS;

// 定义数据结构体
typedef struct {
  int elem;
} ElemType;

// 单链表结构:静态定义
typedef struct LNode {
  ElemType data;
  struct LNode *next;
  struct LNode *rear; // 设立尾指针
} LNode, *LinkList;

//**********************************************************
// 函数声明开始
bool InitList(LinkList &L);
bool DestoryList(LinkList &L);
bool ListEmpty(LinkList L);
int ClearList(LinkList &L);
int ListLength(LinkList L);
void pop_front(LinkList &L);
void pop_back(LinkList &L);
void push_front(LinkList &L, ElemType e);
void push_back(LinkList &L, ElemType e);
int Delete_val(LinkList &L, ElemType e);
ElemType *find(LinkList &list, ElemType item);
LinkList MergeList(LinkList Ta, LinkList Tb);
bool ListInsert(LinkList &L, int i, ElemType e);
bool ListCreate_H(LinkList &L, int n);
bool ListCreate_R(LinkList &L, int n);
void ListReverse(LinkList &list);
int ListShow(LinkList &L);

// 函数声明结束
//**********************************************************

// 1.1 初始化链表
// 构造一个空的循环单向链表L
// 指针域指向头结点
bool InitList(LinkList &L) {
  L = new LNode;
  if (!L)
    return false;
  L->next = L;
  L->rear->next = L->next;
  return true;
}

// 1.2 销毁单链表L
// 销毁链表后成为空表
bool DestoryList(LinkList &L) {
  //	LNode* p = L->rear->next->next; 		// p指向首元结点
  LNode *p = L->next; // p指向首元结点
  LNode *q = NULL;    // 记录指针
  if (L->next == L->rear)
    return false; // 空表时，返回值为0
  while (p != L->rear) {
    q = p;       // 储存结点
    p = p->next; // p指针迭代
    L->next = p; // L指针域指向下个结点
    delete q;    // 释放储存空间
  }
  L->rear = L->next; // 尾指针指向头结点
  return true;
}

int ClearList(LinkList &L) { return 1; }

int ListLength(LinkList L) {
  int length = 0;
  return length;
}

// 2 判定循环链表是否为空表
bool ListEmpty(LinkList L) {
  if (L->next == L)
    return true; // 指针域为头指针，返回值为1
  else
    return false; // 否则，返回值为1
}

// 1.3 头删
void pop_front(LinkList &L) {
  LNode *p = L->rear->next;      // 储存首元结点
                                 //	L->next = L->next->next;				//
                                 //L指向第二个结点
  L->rear->next = L->next->next; // L指向第二个结点
  delete p;                      // 释放储存空间
}

// 1.4 尾删
void pop_back(LinkList &L) {
  LNode *p = L->rear->next; // p指向首元结点
                            //	LNode* p = L->next;						//
                            //p指向首元结点
  LNode *q = L->rear;       // 储存尾指针
  while (p->next != L->rear)
    p = p->next;     // p指针迭代
  L->rear = p->next; // 尾指针上移
  delete q;          // 释放储存空间
}

int Delete_val(LinkList &L, ElemType e) { return 1; }

bool ListInsert(LinkList &L, int i, ElemType e) { return true; }

// 6.1 建立单链表 头插法
bool ListCreate_H(LinkList &L, int n) { return true; }

// 6.2 建立单链表 尾插法
bool ListCreate_R(LinkList &L, int n) { return true; }
// 6.3 头插
void push_front(LinkList &L, ElemType e) {}
// 6.4 尾插
void push_back(LinkList &L, ElemType e) {}

ElemType *find(LinkList &list, ElemType item) {
  ElemType *e;
  return e;
}

LinkList MergeList(LinkList Ta, LinkList Tb) {
  LNode *q = Tb->rear->next;
  Ta->rear = q;
  delete q;
  Tb->rear = Ta->rear;
  return Ta;
}

void ListReverse(LinkList &list) {}

int ListShow(LinkList &L) {}

int main(int argc, char **argv) {
  LinkList mylist;  // 声明链表p
  InitList(mylist); // 初始化链表
  ElemType item;    // 元素项
  int select = 1;
  scanf("%d", &select);
  while (select) {
    printf("\n");
    printf("*******************************************\n");
    printf("*[01] push_back		[02] push_front	  *\n");
    printf("*[03] show_list		[04] pop_back	  *\n");
    printf("*[05] pop_front		[06] insert_val	  *\n");
    printf("*[07] find		[08] length	  *\n");
    printf("*[09] delete_val	[10] sort	  *\n");
    printf("*[11] reverse		[12] clear	  *\n");
    printf("*[13] destroy     	[14] CreateList   *\n");
    printf("*******************************************\n");
    printf("请选择：>>");
    scanf("%d", &select);
    if (select == 0)
      break;
    switch (select) {
    case 1:
      printf("请输入要插入的数据（-1结束）:>\n");
      while (scanf("%d", &item.elem), item.elem != -1)
        push_back(mylist, item);
      break;
    case 2:
      printf("请输入要插入的数据（-1结束）:>\n");
      while (scanf("%d", &item.elem), item.elem != -1)
        push_front(mylist, item);
      break;
    case 3:
      ListShow(mylist);
      break;
    case 4:
      pop_back(mylist);
      break;
    case 5:
      pop_front(mylist);
      break;
    case 6:
      printf("请输入要插入的数据:>");
      scanf("%d", &item);
      ListInsert(mylist, 1, item);
      break;
    case 7:
      ElemType *p;
      printf("请输入要查找的数据:>");
      scanf("%d", &item);
      p = find(mylist, item);
      if (p == NULL)
        printf("要查找的数据在表中不存在！\n");
      else
        printf("%d", *p);
      break;
    case 8:
      printf("线性表的长度为%d\n", ListLength(mylist));
      break;
    case 9:
      printf("请输入要删除的值:>");
      scanf("%d", &item);
      Delete_val(mylist, item);
      break;
    case 10:
      // sort(&mylist);
      exit(0);
      break;
    case 11:
      ListReverse(mylist);
      break;
    case 12:
      ClearList(mylist);
      break;
    case 13:
      DestoryList(mylist);
      break;
    case 14: {
      int sele = 0;
      printf("请选择:头插法:>1 or 尾插法:>2\n");
      scanf("%d", &sele);
      int n = 0;
      printf("请输入要插入元素个数\n");
      scanf("%d", &n);
      switch (sele) {
      case 1:
        ListCreate_H(mylist, n);
        break;
      case 2:
        ListCreate_R(mylist, n);
        break;
      default:
        printf("选择错误,请重新选择！\n");
        break;
      }
    } break;
    default:
      printf("选择错误,请重新选择！\n");
      break;
    }
  }

  return 0;
}
