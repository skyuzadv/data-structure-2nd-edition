//**********************************************************
//******************2.2 单链表******************************
// 单链表：一个链域普通链表
// 链表分：双向链表、循环链表、双向循环链表
// 单链表 -动态定义
// 编程语言：c、c++
//**********************************************************
#include <stdbool.h>

#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

// 函数结果状态代码
#define TRUE       1
#define FALSE      0
#define OK         1
#define ERROR      0
#define INFEASIBLE -1
#define OVERFLOW   -2

// 定义数据类型
typedef int STATUS;

// 定义数据结构体
typedef struct ElemType {
  int elem;
} ElemType;

// 单链表结构:静态定义
typedef struct LNode {
  ElemType data;
  struct LNode* next;
} LNode, *LinkList;

//**********************************************************
// 函数声明开始
bool InitList(LinkList& L);
int DestoryList(LinkList& L);
int ListEmpty(LinkList L);
int ClearList(LinkList& L);
int ListLength(LinkList L);
bool GetElem(LinkList L, int i, ElemType& e);
bool getelem(LinkList L, int i, ElemType& e);
LNode* LocateElem(LinkList L, ElemType e);
int LocateElem(LNode& L, ElemType e);
ElemType* find(LinkList& list, ElemType item);
ElemType* findK(LinkList& list, int k);
ElemType* findMiddle(LinkList& list);
ElemType* findMax(LinkList& list);
ElemType* findMin(LinkList& list);
bool ListInsert(LinkList& L, int i, ElemType e);
bool ListDelete(LinkList& L, int i);
void pop_front(LinkList& L);
void pop_back(LinkList& L);
int Delete_rep(LinkList& L, ElemType e);
bool ListCreate_H(LinkList& L, int n);
bool ListCreate_R(LinkList& L, int n);
void push_front(LinkList& L, ElemType e);
void push_back(LinkList& L, ElemType e);
void ListReverse(LinkList& list);
int ListShow(LinkList& L);
void MergeList(LinkList& la, LinkList& lb, LinkList& lc);
// 函数声明结束
//**********************************************************

//**********************************************************
// 1.0 初始化
// 算法思路：
// a.生成新结点作为头结点，用头指针指向头结点
// b.将头结点的指针域置为空
//**********************************************************
bool InitList(LinkList& L) {
  //	L = (LinkList)malloc(sizeof(LinkList));
  L = new LNode;         // 创建头结点
  if (!L) return false;  // 创建失败后返回0
  L->next = NULL;        // 指针域赋空
  return true;           // 创建完成后返回1
}

//**********************************************************
// 1.1 销毁单链表L
// 算法思路：
// 从头指针开始，依次释放所有结点
// 关键词：从表的头指针开始处依次释放
// 头结点也被释放占用空间
// a. p = L			/*指针p指向头结点*/
// b. L = L->next
// c. L == NULL		/*结束条件*/
//**********************************************************
int DestoryList(LinkList& L) {
  LNode* p;
  while (L != NULL) {
    p = L;
    L = L->next;
    delete p;
  }
  return 1;
}

//**********************************************************
// 1.2 判定单链表是否为空表
// 空表：链表中无元素，称为空链表(头指针和头结点仍然存在)
// 算法思路：
// 判断头结点的指针域是否空
//**********************************************************
int ListEmpty(LinkList L) {
  if (L->next == NULL) return 1;  // 指针域为空，返回值为1
  return 0;                       // 否则，返回值为1
}
//**********************************************************
// 1.3 清空单链表L
// 链表仍然存在，但链表中无元素，成为空表(头指针和头结点仍然存在)
// 算法思路：
// 依次释放所有结点，并将头结点指针域置为空
// a. p = L->next 	/*指针p指向首元结点*/
// b. q = p->next
// c. delete p
// d. p == NULL		/*结束条件*/
//**********************************************************
int ClearList(LinkList& L) {
  LNode *p, *q;
  p = L->next;
  while (p) {  // 没到表尾
    q = p->next;
    delete p;  // 释放结点
    p = q;     // p指针置为下一个地址
  }
  L->next = NULL;  // 头结点指针域置为空
  return 1;
}

//**********************************************************
// 1.4 求单链表的表长
// 算法思路：
// 从首元结点开始，依次计数所有结点
// a. p = L->next 	/*指针p指向首元结点*/
// b. p = p->next 	/*指针p移动*/
// c. p == NULL 	/*结束条件*/
//**********************************************************
int ListLength(LinkList L) {
  int length = 0;                 // 初始表长置0
  if (L->next == NULL) return 0;  // 判断空表，返回值为0
  LinkList p = L->next;           // p指向首元结点
  while (p) {                     // p != NULL
    length++;                     // 依次计数
    p = p->next;                  // 移动指针p
  }
  return length;  // 返回表长
}

//**********************************************************
// 2.取值 取单链表中第i个元素的内容
// 算法思路：
// 从链表的头指针出发，顺着链域next逐个结点向下搜索，直至搜索第i个结点为止
// 链表不是随机存取结构，而是顺序存取
//**********************************************************
bool GetElem(LinkList L, int i, ElemType& e) {
  LNode* p = L->next;           // p指向首元结点地址
  int j = 1;                    // 定义计数器
  while (p != NULL && j < i) {  // j=1时排除特殊值：i = 0, i= -1,
    p = p->next;                // p指针迭代
    ++j;                        // 计数+1
  }
  // 假设有p == NULL 结束循环
  // 此时有p == NULL and j=5,i=10,仍然满足：j < i(i值不合理)
  if (j > i || p == NULL) return false;  // p为空，j超过i范围。返回值为0
  e = p->data;
  return true;
}

//**********************************************************
// 2.取值
// 改进代码
//**********************************************************
bool getelem(LinkList L, int i, ElemType& e) {
  LNode* p = L->next;
  int j = 1;
  // p -> NULL, i值不合理i = 0, i = -1,返回值为0
  if (j > i || p == NULL) return false;
  while (p != NULL && j < i) {
    p = p->next;
    j++;
  }
  // 假设 j=5, i = 10,p指针指向表尾
  // 循环结束后，仍有满足：j < i
  if (j < i && p == NULL) return false;
  if (j == i) e = p->data;
  return true;
}

// 3.1 查找
LNode* LocateElem(LinkList L, ElemType e) {
  LNode* p = L->next;                    // p指向首元结点
  while (p && p->data.elem != e.elem) {  // p为非空
    p = p->next;                         // p指针迭代
  }
  return p;  // 返回p所指的地址
}

// 3.2 查找
int LocateElem(LNode& L, ElemType e) {  // 函数重载，返回索引值
  LNode* p = &L;                        // p指向首元结点
  int j = 1;
  while (p) {
    p = p->next;
    j++;
    if (p->data.elem == e.elem) break;
  }
  if (p) return j;
  return 0;
}
// 3.3 查找
ElemType* find(LinkList& list, ElemType item) {
  LNode* p = list->next;
  ElemType* e = NULL;
  if (p == NULL) return e;
  while (p != NULL) {
    if (item.elem == p->data.elem) {
      e = &p->data;
      break;
    }
    p = p->next;
  }
  return e;
}

// 3.4 查找中间结点
ElemType* findMiddle(LinkList& list) {
  LNode *fast, *slow;
  ElemType* e = NULL;
  if (list->next == NULL) return e;
  fast = list;  // fast pointer
  slow = list;  // slow pointer
  while (fast != NULL && fast->next != NULL) {
    fast = fast->next->next;
    slow = slow->next;
  }
  return e = &slow->data;
}

// 3.5 查找倒数第k个元素
ElemType* findK(LinkList& list, int k) {
  ElemType* e;
  LNode *fast, *slow;
  fast = list->next;
  slow = list->next;
  if (!list->next) return e = NULL;
  // 对偶逻辑代码
  while (fast->next) {
    if (--k <= 0) slow = slow->next;
    fast = fast->next;
  }
  if (k - 1 > 0) return e = NULL;
  return e = &slow->data;
  {  // other way
    while (fast->next != NULL) {
      if (k - 1 > 0)
        fast = fast->next, k--;
      else {
        fast = fast->next;
        slow = slow->next;
      }
    }
    return e = &slow->data;
  }
}

// 3.6 查找最大值
// 查找链表最大值返回该结点值
ElemType* findMax(LinkList& list) {
  ElemType* e = NULL;
  LNode *pmax, *p;
  pmax = list->next;     // 首元结点
  p = list->next->next;  // 第二结点
  if (!list->next) return e;
  while (p) {
    if (p->data.elem >= pmax->data.elem) pmax = p;
    p = p->next;
  }
  return e = &pmax->data;
}

// 3.7 查找最小值
// 查找链表最小值返回该结点值
ElemType* findMin(LinkList& list) {
  ElemType* e = NULL;
  LNode *pmin, *p;
  pmin = list->next;     // 首元结点
  p = list->next->next;  // 第二结点
  if (!list->next) return e;
  while (p) {
    if (p->data.elem <= pmin->data.elem) pmin = p;
    p = p->next;
  }
  return e = &pmin->data;
}

// 4.插入
// 在链表L中第i个位置插入元素e
bool ListInsert(LinkList& L, int i, ElemType e) {
  LNode* p = L->next;  // p指向首元结点
  int j = 1;
  while (p != NULL && j < i) {  // 移动p指针
    p = p->next;                // p指针迭代
    j++;                        // 位序+1
  }
  if (j > i || p == NULL) return false;
  LNode* s = new LNode;  // 插入结点指针
  s->data = e;           // 插入元素赋值
  s->next = p->next;
  p->next = s;
  return true;
}

// 5.1 删除
bool ListDelete(LinkList& L, int i) {
  LinkList p = L;  // p指向头结点
  int j = 0;
  while (p->next && j < i - 1) {  // 移动p指针
    p = p->next;                  // p指针迭代
    j++;                          // 位序+1
  }
  if (!(p->next) || j > i - 1) return false;
  LinkList q = p->next;
  p->next = q->next;
  delete q;
  return true;
}

// 5.2 头删
void pop_front(LinkList& L) {
  LNode* p = L->next;  // p指向首元结点
  L->next = p->next;   // 指向下一个结点
  delete p;            // 释放储存空间
}

// 5.3 尾删
void pop_back(LinkList& L) {
  LNode* p = L->next;                         // p指向首元结点
  while (p->next->next != NULL) p = p->next;  // p指针迭代
  LNode* q = p->next;                         // 指针q记录
  p->next = q->next;                          // p->next = NULL
  delete q;                                   // 释放储存空间
}

//**********************************************************
// 5.4 删除
// 删除表中元素等于该值的位置
// 删除包括重复元素
// 快慢指针法
int Delete_rep(LinkList& L, ElemType e) {
  if (L->next == NULL) return 0;  // 空表返回
  LinkList list;                  // 声明储存链表
  if (!InitList(list)) {
    printf("Failed to Initial node!\n");  // 初始化失败！
    return 0;
  }
  LNode* fast = L->next;  // L链表快指针p
  LNode* slow = L;        // L链表慢指针s
  LNode* p = list;        // 指针p迭代
  while (fast) {
    if (e.elem != fast->data.elem) {
      p->next = fast;
      p = fast;
      slow->next = fast->next;  // 储存头尾结点
      cout << p->data.elem << endl;
    }
    if (fast->next == NULL) p->next = NULL;  // 下个结点是链尾，q->next指向空
    if (e.elem == fast->data.elem) slow = fast;  // 越过相等结点
    fast = fast->next;                           // 指针p迭代
  }
  ListShow(list);
  ListShow(L);
  DestoryList(L);  // destory list
  L = list;
  ListShow(L);
  return 1;
}

// 6.1 建立单链表 头插法
bool ListCreate_H(LinkList& L, int n) {
  L = new LNode;   // 创建头结点
  L->next = NULL;  // 表尾赋空
  LNode* p;        // p指针
  for (int i = 0; i < n; i++) {
    p = new LNode, p->data.elem = i;
    p->next = L->next;
    L->next = p;
  }
  return true;
}

// 6.2 建立单链表 尾插法
bool ListCreate_R(LinkList& L, int n) {
  L = new LNode;   // 创建头结点
  L->next = NULL;  // 表尾赋空
  LNode* p;        // p指针
  LNode* rear;     // 尾指针
  rear = L;        // 尾指针指向L
  while (n--) {
    p = new LNode;
    p->next = NULL;
    rear->next = p;
    rear = p;
  }
  return true;
}
// 6.3 头插
void push_front(LinkList& L, ElemType e) {
  LNode* s = new LNode;
  s->data.elem = e.elem;
  s->next = L->next;
  L->next = s;
}

// 6.4 尾插
void push_back(LinkList& L, ElemType e) {
  LNode* s = new LNode;
  s->data.elem = e.elem;
  if (L->next == NULL) {
    s->next = L->next;
    L->next = s;
  } else {
    LNode* p = L->next;
    while (p->next) p = p->next;
    s->next = p->next;
    p->next = s;
  }
}
// 7.0 逆置
// 逆序线性表
// 算法思路：
// 头插法逆序造表
void ListReverse(LinkList& L) {
  if (L->next == NULL) return;  // 空表返回
  LinkList list;                // 声明储存链表
  if (!InitList(list)) {
    printf("Failed to Initial node!\n");  // 初始化失败！
    return;
  }
  LNode* p = L;
  LNode* q = NULL;
  while (p->next) {
    q = p->next;
    p->next = q->next;
    q->next = list->next;
    list->next = q;
  }
  DestoryList(L);
  L = list;
}

// 8.0 打印
int ListShow(LinkList& L) {
  LinkList p = L;
  int i = 0;
  if (!p->next) {
    printf("null\n");
    return 0;
  }
  while (p->next) {
    p = p->next;
    if (i != 0) printf(" ");
    printf("[%d]=%d", i++, p->data);
  }
  printf("\n");
  return 1;
}
// 9.0 有序表合并
void MergeList(LinkList& la, LinkList& lb, LinkList& lc) {
  LNode *pa, *pb, *pc;
  pa = la->next;
  pb = lb->next;
  pc = lc = la;  // lc头结点赋值
  while (pa && pb) {
    if (pa->data.elem <= pb->data.elem) {
      pc->next = pa;
      pc = pa;
      pa = pa->next;
    } else {
      pc->next = pb;
      pc = pb;
      pb = pb->next;
    }
  }
  pc->next = pa ? pa : pb;
}

// main()
int main(int argc, char** argv) {
  LinkList mylist;   // 声明链表p
  InitList(mylist);  // 初始化链表
  ElemType item;     // 元素项
  int select = 1;
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
    printf("*[15] merge     	[16] exit	  *\n");
    printf("*******************************************\n");
    printf("请选择：>>");
    scanf("%d", &select);
    if (select == 0) break;
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
      case 7: {
        int sele = 0;
        printf(
            "请选择:按值查找:>1 or 查找中点:>2 or 按倒数查找:>3 or "
            "查找最值:>4 \n");
        scanf("%d", &sele);
        ElemType* p;
        switch (sele) {
          case 1: {
            printf("请输入要查找的数据:>");
            scanf("%d", &item.elem);
            p = find(mylist, item);
          } break;
          case 2:
            p = findMiddle(mylist);
            break;
          case 3: {
            int k = 0;
            printf("请输入倒数第k个数据:>");
            scanf("%d", &k);
            p = findK(mylist, k);
          } break;
          case 4: {
            int k = 0;
            printf("请选择:最大值:>1 or 最小值:>2 \n");
            scanf("%d", &k);
            switch (k) {
              case 1:
                printf("链表最大结点值:>\n");
                p = findMax(mylist);
                break;
              case 2:
                printf("链表最小结点值:>\n");
                p = findMin(mylist);
                break;
              default:
                printf("选择错误,请重新选择！");
                break;
            }
          } break;
          default:
            printf("选择错误,请重新选择！\n");
            break;
        }
        if (p == NULL)
          printf("要查找的数据在表中不存在！\n");
        else
          printf("返回数值=%d", *p);
      } break;
      case 8:
        printf("线性表的长度为%d\n", ListLength(mylist));
        break;
      case 9:
        printf("请输入要删除的值:>");
        scanf("%d", &item);
        Delete_rep(mylist, item);
        break;
      case 10:
        // sort(&mylist);
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
      case 15: {
        LinkList la, lb, lc;
        InitList(la);
        InitList(lb);
        ElemType item;
        printf("请给la输入要插入的数据（-1结束）:>\n");
        while (scanf("%d", &item.elem), item.elem != -1) push_back(la, item);
        printf("请给lb输入要插入的数据（-1结束）:>\n");
        while (scanf("%d", &item.elem), item.elem != -1) push_back(lb, item);
        printf("有序表合并：\n");
        MergeList(la, lb, lc);
        ListShow(lc);
        DestoryList(lb);
      } break;
      case 16:
        exit(0);
        break;
      default:
        printf("选择错误,请重新选择！\n");
        break;
    }
  }

  return 0;  // exit
}
