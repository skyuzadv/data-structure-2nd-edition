//**********************************************************
//******************2.1 线性表******************************
// 线性表 -静态定义
// 线性表 -动态定义
// 编程语言：c、c++
//**********************************************************
#include <cstdio>
#include <cstdlib>
#include <iostream>
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
typedef int ElemType;

#define MAXSIZE 100 // 线性表容量

// 线性表结构:静态定义
typedef struct sqlist {
  ElemType elem[MAXSIZE]; // 数组类型
  int length;             // 表长
} sqlist;

// 线性表结构:动态定义
typedef struct SQList {
  ElemType *elem; // 指针类型，作基地址
  int length;     // 表长
} SQList;

//**********************************************************
// 函数声明开始
bool InitList(SQList &list);
void DestoryList(SQList *list);
void ClearList(SQList &L);
int ListLength(SQList L);
int ListEmpty(SQList L);
bool ListCreate(SQList &list);
int GetElem(SQList *list, int i, ElemType &e);
int GetElem(SQList &list, int i, ElemType &e);
int LocateElem(SQList *list, ElemType e);
int LocateElem(SQList &list, ElemType e);
ElemType *find(SQList *sqlist, ElemType item);
bool ListInsert(SQList &list, int i, ElemType e);
void push_front(SQList *L, ElemType item);
void push_back(SQList *L, ElemType item);
bool ListDelete(SQList &list, int i, ElemType &e);
int Delete_val(SQList *L, ElemType e);
void pop_front(SQList &L);
void pop_back(SQList &L);
void ListReverse(SQList *list);
int ListShow(SQList &list);
void MergeList(SQList &La, SQList &Lb);
void MergeList(SQList la, SQList lb, SQList &lc);
// 函数声明结束
//**********************************************************

// 1.0 初始化
bool InitList(SQList &list) {
  //	list.elem = (ElemType*)malloc(sizeof(ElemType) * MAXSIZE);	//
  //动态分配内存 c语言
  list.elem = new ElemType[MAXSIZE]; // 动态分配内存 c++语言
  if (!list.elem)
    return false;  // 创建失败，返回值0
  list.length = 0; // 空表长度为0
  return true;     // 创建成功，返回值1
}

// 1.1 销毁线性表L
void DestoryList(SQList *list) {
  //	if (list->elem) free(list->elem);
  if (list->elem)
    delete[] list->elem; // 指针判空,释放储存空间
  list->elem = NULL;     // 指针赋空
}

// 1.2 清空线性表L
void ClearList(SQList &L) {
  L.length = 0; // 将线性表的长度置为0
}

// 1.3 取线性表长度
int ListLength(SQList L) { return (L.length); }

// 1.4 判定线性表是否为空表
int ListEmpty(SQList L) {
  if (L.length == 0)
    return 1; // 线性表长度为0，返回值为1
  else
    return 0; // 否则，返回值为1
}

// 2.创建
bool ListCreate(SQList &list) {
  printf("\n请输入要插入的数据（-1结束）:>\n");
  if (list.length >= MAXSIZE)
    return false;
  int x = 0, i = 0;
  cin >> x;
  while (x != -1) { // 设置x != -1 结束读入数据
    list.elem[i++] = x;
    list.length++;
    cin >> x;
    if (i >= MAXSIZE)
      break;
  }
  return true;
}

// 3.1 线性表的取值
int GetElem(SQList *list, int i, ElemType &e) { // i:位序表示
  if (i < 1 || i > list->length)
    return -1; // 判定i值是否合理，若不合理，返回值为-1
  e = list->elem[i - 1];
  return 1;
}

// 3.2 线性表的取值
int GetElem(SQList &list, int i, ElemType &e) { // i:位序表示
  if (i >= 1 && i <= list.length) {
    e = list.elem[i - 1];
    return 1;
  } else
    return e = -1;
}

// 4.1 查找 按值查找
// 算法思路：
// 出发点：从头往后找，挨个比较
int LocateElem(SQList *list, ElemType e) {
  for (int i = 0; i <= list->length - 1; i++)
    if (list->elem[i] == e)
      return i + 1; // 查找成功，返回为序号
  return 0;         // 查找失败，返回0
}
// 4.2 查找 按值查找
int LocateElem(SQList &list, ElemType e) {
  int i = 0;
  while (i < list.length && e != list.elem[i])
    i++;
  if (i < list.length)
    return i + 1; // 查找成功，返回为序号
  return 0;       // 查找失败，返回0
}
// 4.3 查找 按值查找
// 返回所在表中地址
ElemType *find(SQList *sqlist, ElemType item) {
  int i = 0;
  ElemType *p = NULL; // 否则，p=NULL
  for (; i <= sqlist->length - 1; i++) {
    if (item == sqlist->elem[i])
      p = &sqlist->elem[i]; // 找到返回表中所在地址；
  }
  return p; // p返回所在地址
}

//**********************************************************
// 5.1 插入
// 算法思路：
// 判断储存是否已满
// i位置后元素向后面移动,i位置前元素位置不变，并且最先移动表尾元素a[length-1]
// 元素位置为 n+1 个
// 表尾插入元素，速度最快，也是出发点
// 插入范围：0 ~ n+1
//**********************************************************
bool ListInsert(SQList &list, int i, ElemType e) { // i是位序
  if (MAXSIZE == list.length)
    return false; // 判定储存是否已满
  if (i >= MAXSIZE)
    return false; // i值大于容量，不合法
  if (i < 1 || i > list.length + 1)
    return false; // 判定i值是否合法
  for (int j = list.length - 1; j >= i - 1; j--)
    list.elem[j + 1] = list.elem[j]; // 向后移动
  list.elem[i - 1] = e;              // 插入新元素值
  list.length++;                     // 表长加1
  return true;
}

// 头插
void push_front(SQList *L, ElemType item) {
  if (L->length == MAXSIZE)
    return;
  for (int i = L->length - 1; i >= 0; i--)
    L->elem[i + 1] = L->elem[i];
  L->elem[0] = item;
  L->length++;
}

// 尾插
void push_back(SQList *L, ElemType item) {
  if (L->length == MAXSIZE)
    return;
  L->elem[L->length] = item;
  L->length++;
}

//**********************************************************
// 6.1 删除
// 算法思路：
// 本质覆盖元素，元素向前i位置移动
// 其他和插入特性类似
//**********************************************************
bool ListDelete(SQList &list, int i, ElemType &e) { // i是位序
  if (i > list.length || i < 1)
    return false;       // 判定i值是否合法
  e = list.elem[i - 1]; // 保存删除元素值
  for (int j = i; j <= list.length - 1; j++)
    list.elem[j - 1] = list.elem[j]; // 向前移动
  list.length--;                     // 表长减1
  return true;
}

//**********************************************************
// 6.1 删除
// 删除表中元素等于该值的位置
// 删除包括重复元素
int Delete_val(SQList *L, ElemType e) {
  if (L->length == 0)
    return 0;  // 空表直接返回
  SQList list; // 定义临时线性表
  if (!InitList(list)) {
    printf("Failed to Initial node!\n"); // 初始化失败！
    return 0;
  }
  for (int i = 0, j = 0; i <= L->length - 1; i++) {
    if (e != L->elem[i]) {
      list.elem[j] = L->elem[i]; // 拷贝元素
      list.length++, j++;        // 长度加1
    }
  }
  L->length = 0; // 清空原有线性表
  for (int i = 0; i < list.length; i++)
    L->elem[i] = list.elem[i], L->length++;
  DestoryList(&list); // 释放储存空间
  return 1;           // 成功返回为1
}
// 6.2 头删
void pop_front(SQList &L) {
  if (L.length == 0)
    return;
  if (L.length >= 1) {
    // for (int i = 0; i <= L.length - 1; i++) L.elem[i] = L.elem[i+1];
    for (int i = 1; i <= L.length; i++)
      L.elem[i - 1] = L.elem[i];
  }
  L.length--; // 表长减1
}
// 6.3 尾删
void pop_back(SQList &L) {
  if (L.length == 0)
    return;
  if (L.length >= 1)
    L.length--; // 表长减1
}

// 7.0 逆置
// 逆序线性表
void ListReverse(SQList *list) {
  if (list->length == 0)
    return;
  int n = list->length;
  ElemType item;
  for (int i = 0; i < n / 2; i++) {
    item = list->elem[i];
    list->elem[i] = list->elem[n - i - 1];
    list->elem[n - i - 1] = item;
  }
}
// 8.0 打印
int ListShow(SQList &list) {
  if (list.length == 0) {
    printf("null\n");
    return 0;
  }
  for (int i = 0; i <= list.length - 1; i++) {
    if (i != 0)
      cout << " "; // 格式控制
    printf("[%d]=%d", i, list.elem[i]);
  }
  //	cout << " " << "len = " << list.length << "\n";
  return 1;
}
// 9.0 线性表合并
// 最终结果:la <= lb
// 储存表la优点：向左赋值
void MergeList(SQList &La, SQList &Lb) {
  int m = ListLength(La);
  int n = ListLength(Lb);
  ElemType e; // cc元素值
  for (int i = 1; i <= n; i++) {
    GetElem(Lb, i, e); // 遍历表Lb,插入到La后
    if (!LocateElem(La, e))
      ListInsert(La, ++m, e);
  }
}
// 9.1 有序表合并
// 返回合并表lc
void MergeList(SQList la, SQList lb, SQList &lc) {
  ElemType *pa = la.elem;
  ElemType *pb = lb.elem;
  ElemType *pc = lc.elem;
  ElemType *pa_last = la.elem + la.length - 1;
  ElemType *pb_last = lb.elem + lb.length - 1;
  while (pa <= pa_last && pb <= pb_last) {
    if (*pa <= *pb)
      *pc++ = *pa++; // 取值之后，指针偏移
    else
      *pc++ = *pb++;
    lc.length++;
  }
  while (pa <= pa_last)
    *pc++ = *pa++, lc.length++; // 拷贝剩余值
  while (pb <= pb_last)
    *pc++ = *pb++, lc.length++; // 拷贝剩余值
}

// main()
int main(int argc, char **argv) {
  SQList mylist;    // 线性表声明
  InitList(mylist); // 线性表初始化
  ElemType item;    // 元素项
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
    std::printf("please select no.:>>");
    std::scanf("%d", &select);
    if (select == 0)
      break;
    switch (select) {
    case 1:
      printf("please input insert data(endup with -1):>\n");
      while (scanf("%d", &item), item != -1)
        push_back(&mylist, item);
      break;
    case 2:
      printf("please input insert data(endup with -1):>\n");
      while (scanf("%d", &item), item != -1)
        push_front(&mylist, item);
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
      printf("please input insert data(endup with -1):>\n");
      scanf("%d", &item);
      ListInsert(mylist, 1, item);
      break;
    case 7: {
      ElemType *p;
      printf("please input find data(endup with -1):>\n");
      scanf("%d", &item);
      p = find(&mylist, item);
      if (p == NULL)
        printf("find data not exit in the table!\n");
      else
        printf("%d", *p);
    } break;
    case 8:
      printf("line table length is:%d\n", ListLength(mylist));
      break;
    case 9:
      printf("please input delete data:>");
      scanf("%d", &item);
      Delete_val(&mylist, item);
      break;
    case 10:
      // sort(&mylist);
      break;
    case 11:
      ListReverse(&mylist);
      break;
    case 12:
      ClearList(mylist);
      break;
    case 13:
      DestoryList(&mylist);
      break;
    case 14:
      ListCreate(mylist);
      break;
    case 15: {
      int sele = 0;
      ElemType item;
      SQList la, lb, lc;
      InitList(la);
      InitList(lb);
      printf("table La:insert data(endup with -1):>\n");
      while (scanf("%d", &item), item != -1)
        push_back(&la, item);
      printf("table Lb:insert data(endup with -1):>\n");
      while (scanf("%d", &item), item != -1)
        push_back(&lb, item);
      printf("请选择:线性表合并:>1 or 有序表合并:>2\n");
      scanf("%d", &sele);
      switch (sele) {
      case 1:
        printf("线性表合并：\n");
        MergeList(la, lb);
        ListShow(la);
        break;
      case 2: {
        lc.elem = new ElemType[la.length + lb.length];
        lc.length = 0;
        printf("有序表合并：\n");
        MergeList(la, lb, lc);
        ListShow(lc);
      } break;
      default:
        printf("选择错误,请重新选择！\n");
        break;
      }
      DestoryList(&la);
      DestoryList(&lb);
      delete[] lc.elem;
    } break;
    case 16:
      exit(0);
      break;
    default:
      printf("选择错误,请重新选择！\n");
      break;
    }
  }

  return 0;
}
