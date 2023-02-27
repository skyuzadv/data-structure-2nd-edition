//**********************************************************
//********************2.8 案例分析与实现********************
// 解决目标：一元多项式运算
// 主要运算：加法 减法 乘法
// 主要特点：递增、递减、唯一
// 储存方式：线性表(动态数组)
// 编译配置：-std=c++11，auto
// #include<bits/stdc++.h>
//**********************************************************

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <stdbool.h>

using namespace std;

#define MAXSIZE 30
#define FILE_Import "polynomial seqlist.in"
#define FILE_Export "polynomial seqlist.ans"

#define DATA_Import "polynomial seqlist_a.in"

// 0.1 数据结构
typedef struct ElemType {
  float coef; // 系数
  int expn;   // 指数
} ElemType;

// 0.2 线性表
typedef struct polyno {
  ElemType *elem; // 指针类型，作基地址
  int length;     // 表长
} polyno;

//**********************************************************
// 函数声明开始
int isfileNull(const char *);
template <typename T> bool InitialPolyno(T *ptab);
template <typename T> void DestoryPolyno(T *ptab);
template <typename T> void pop_front(T *ptab);
template <typename T> void pop_back(T *ptab);
template <typename T> void AddPolyno(T *, T *, T *);
template <typename T> void SubPolyno(T *, T *, T *);
template <typename T> void MulPolyno(T *Pa, T *Pb, T *merge);
template <typename T> bool PolynoShow(T *ptab);
template <typename T> int GetLength(T *ptab);
template <typename T1, typename T2> void push_front(T1 *, T2);
template <typename T1, typename T2> void push_back(T1 *, T2);
template <typename T1, typename T2> void dataInput(T1 *, T1 *, T2 *);

// 函数声明结束
//**********************************************************

// main()
int main(int argc, char **argv) {
  polyno table;
  InitialPolyno(&table);
  int select = 1;
  while (select) {
    printf("\n");
    printf("*******************************************\n");
    printf("*[01] push_back		[02] push_front	  *\n");
    printf("*[03] show_list		[04] pop_back	  *\n");
    printf("*[05] pop_front		[06] addPolyno	  *\n");
    printf("*[07] subPolyno		[08] mulPolyno	  *\n");
    printf("*[09] delete_val	[10] sort	  *\n");
    printf("*[11] reverse		[12] clear	  *\n");
    printf("*[13] destroy     	[14] CreateList   *\n");
    printf("*[15] merge     	[16] exit	  *\n");
    printf("*******************************************\n");
    printf("请选择：>>");
    scanf("%d", &select);
    if (select == 0)
      break;
    switch (select) {
    case 1: {
      ElemType item;
      printf("请输入要插入的数据（-1,0结束）:>\n");
      while (scanf("%f%d", &item.coef, &item.expn), item.coef != -1.0f)
        push_back<polyno, ElemType>(&table, item);
    } break;
    case 2: {
      ElemType item;
      printf("请输入要插入的数据（-1,0结束）:>\n");
      while (scanf("%f%d", &item.coef, &item.expn), item.coef != -1.0f)
        push_front<polyno, ElemType>(&table, item);
    } break;
    case 3:
      PolynoShow(&table);
      break;
    case 4:
      pop_back(&table);
      break;
    case 5:
      pop_front(&table);
      break;
    case 6: {
      ElemType item;
      polyno pa, pb;
      InitialPolyno<polyno>(&pa);
      InitialPolyno<polyno>(&pb);

      /*
      printf("请给Pa输入要插入的数据(x, n)（-1,0结束）:>\n");
while ( scanf("%f %d", &item.coef, &item.expn), item.coef != -1.0f )
push_back(&pa, item); printf("请给Pb输入要插入的数据(x, n)（-1,0结束）:>\n");
while ( scanf("%f %d", &item.coef, &item.expn), item.coef != -1.0f )
push_back(&pb, item);
      */

      dataInput<polyno, ElemType>(&pa, &pb, &item);

      PolynoShow(&pa);
      PolynoShow(&pb);
      polyno ans;                // add resulut
      AddPolyno(&pa, &pb, &ans); // call addpolyno()
      PolynoShow(&ans);
      delete[] ans.elem;
      ans.elem = nullptr;

      polyno res;
      SubPolyno(&pa, &pb, &res); // sub resulut
      PolynoShow(&res);
      delete[] res.elem;
      res.elem = nullptr;
    } break;
    case 8: {
      polyno pa, pb, pc;
      InitialPolyno<polyno>(&pa);
      InitialPolyno<polyno>(&pb);
      InitialPolyno<polyno>(&pc);
      printf("从文件调用数据! \n");
      FILE *fp;
      int n1, n2, expn;
      float coef;
      if (isfileNull(FILE_Import)) {
        printf("file is null! please input some data, end with '$' \n");
        fp = fopen(FILE_Import, "w"); // write data
        // clear stdin buffer
        // fseek(stdin, 0, SEEK_SET);						/*
        // 清空输入缓冲区 */ rewind(stdin); fflush(stdin);
        int ch = getchar(); // 读取整数
        int cnt = 1;        // 缓存区存在\n
        while (ch != '$') {
          if (ch == '\n' && cnt == 1)
            cnt = 0, ch = getchar(); // 如果是换行取出来
          fputc(ch, fp);
          ch = getchar();
        }
        fclose(fp);
      } else {
        printf("file is good! \n");
        fp = fopen(FILE_Import, "r"); // read data
        // Pa polyno
        fscanf(fp, "%d", &n1);
        for (int i = 0; i < n1; i++) {
          fscanf(fp, "%f %d", &coef, &expn);
          pa.elem[pa.length].coef = coef;
          pa.elem[pa.length].expn = expn;
          pa.length++;
        }
        // Pb polyno
        fscanf(fp, "%d", &n2);
        for (int i = 0; i < n2; i++) {
          fscanf(fp, "%f %d", &coef, &expn);
          pb.elem[pb.length].coef = coef;
          pb.elem[pb.length].expn = expn;
          pb.length++;
        }
        fclose(fp);
      }
      PolynoShow(&pa);
      PolynoShow(&pb);

      MulPolyno(&pa, &pb, &pc);
      printf("merge result:\n");
      PolynoShow(&pc);
    } break;
    case 13:
      DestoryPolyno(&table);
      break;
    case 16:
      exit(0);
      break;
    }
  }
  return 0;
}

// 判定文本文件是否为空
// 文件空，返回值为1
int isfileNull(const char *fileName) {
  FILE *fp = fopen(fileName, "r");
  if (!fp) {
    printf("Can't open file! \n");
    return 1;
  }
  int ch = fgetc(fp);
  fclose(fp);
  if (ch == EOF)
    return 1;
  else
    return 0;
}
// data Input
template <typename T1, typename T2> void dataInput(T1 *pa, T1 *pb, T2 *item) {
  printf("++++++++++++++++++++++++++++++++++++\n");
  printf("读取数据:(系数, 指数)格式\n");
  printf("读取选择:\n");
  printf("3>终端输入 4>文件读取 \n");
  printf("++++++++++++++++++++++++++++++++++++\n");
  FILE *fp;
  item->coef = 0;
  int select = 1;
  do {
    scanf("%d", &select);
    if (select == 0)
      break;
    switch (select) {
    case 3: {
      rewind(stdin); // clear stdin buffer
      int n1, n2;
      printf("请给Pa输入元素长度:>\n");
      scanf("%d", &n1);
      printf("请给Pa输入要插入的数据(x, n):>\n");
      while (n1--) {
        scanf("%f %d", &item->coef, &item->expn);
        push_back<polyno, ElemType>(pa, *item);
      }
      rewind(stdin); // clear stdin buffer
      printf("请给Pb输入元素长度:>\n");
      scanf("%d", &n2);
      printf("请给Pb输入要插入的数据(x, n):>\n");
      while (n2--) {
        scanf("%f %d", &item->coef, &item->expn);
        push_back<polyno, ElemType>(pb, *item);
      }
      printf("Pa :\n");
      PolynoShow(pa);
      printf("Pb :\n");
      PolynoShow(pb);
      select = 0; // exit case 懒得输入0
    } break;
    case 4: {
      FILE *fp;
      int n1, n2;
      if (isfileNull(DATA_Import)) {
        printf("data file is null, please input some datas in files end with "
               "'$'! \n");
        fseek(stdin, 0, SEEK_SET); // clean stdin buffer
        fp = fopen(DATA_Import, "w");
        int ch = getchar();
        while (ch != '$') {
          fputc(ch, fp);
          ch = getchar();
        }
        fclose(fp);
      } else {
        printf("file is good! \n");
        fp = fopen(DATA_Import, "r");
        auto coef = item->coef;
        auto expn = item->expn;
        fscanf(fp, "%d", &n1);
        for (int i = 0; i < n1; i++) {
          //							fscanf(fp, "%f %d", &coef,
          //&expn); 							pa->elem[pa->length].coef = coef; 							pa->elem[pa->length].expn
          //= expn; 							pa->length++;
          fscanf(fp, "%f %d", &pa->elem[i].coef, &pa->elem[i].expn);
          pa->length++;
        }
        fscanf(fp, "%d", &n2);
        for (int i = 0; i < n2; i++) {
          fscanf(fp, "%f %d", &coef, &expn);
          pb->elem[pb->length].coef = coef;
          pb->elem[pb->length].expn = expn;
          pb->length++;
        }
        fclose(fp);
        printf("Pa :\n");
        PolynoShow(pa);
        printf("Pb :\n");
        PolynoShow(pb);
        select = 0; // exit case
      }
    } break;
    default:
      printf("输入错误！请重新选择！\n");
      break;
    }
  } while (select);
}

// 1.0 初始化函数
template <typename T> bool InitialPolyno(T *ptab) {
  ptab->elem = new ElemType[MAXSIZE]; // 最大容量
  if (!ptab->elem)
    return false;   // 分配失败返回0
  ptab->length = 0; // 初始长度为0
  return true;
}

// 1.1 析构函数
// 销毁所占用内存空间
template <typename T> void DestoryPolyno(T *ptab) {
  if (!ptab)
    return;
  ptab->length = 0;
  delete[] ptab->elem;
  ptab->elem = nullptr;
}

// 2.1 头插
template <typename T1, typename T2> void push_front(T1 *ptab, T2 item) {
  if (ptab->length == MAXSIZE)
    return;
  for (int i = ptab->length - 1; i >= 0; i--) {
    ptab->elem[i + 1].coef = ptab->elem[i].coef;
    ptab->elem[i + 1].expn = ptab->elem[i].expn;
  }
  ptab->elem[0].coef = item.coef;
  ptab->elem[0].expn = item.expn;
  ptab->length++;
}

// 2.2 尾插
template <typename T1, typename T2> void push_back(T1 *ptab, T2 item) {
  if (ptab->length == MAXSIZE)
    return;
  if (ptab->elem == NULL)
    return;
  ptab->elem[ptab->length++] = item;
}

// 2.3 头删
template <typename T> void pop_front(T *ptab) {
  if (ptab->length == 0)
    return; // if seqlist is empty
  if (ptab->length >= 1) {
    for (int i = 1; i <= ptab->length; i++)
      ptab->elem[i - 1] = ptab->elem[i];
  }
  ptab->length--;
}

// 2.4 尾删
template <typename T> void pop_back(T *ptab) {
  if (ptab->length == 0)
    return;
  if (ptab->length >= 1)
    ptab->length--;
}

// 3.0 返回表长
template <typename T> int GetLength(T *ptab) {
  if (ptab->elem)
    return ptab->length;
  else
    return -1;
}

// 4.0 加法
template <typename T> void AddPolyno(T *Pa, T *Pb, T *Res) {
  T tab;
  tab.elem = new ElemType[Pa->length + Pb->length]; // 创建线性表
  tab.length = 0;                                   // 初始长度为0
  int i = 0, j = 0;
  while ((i <= Pa->length - 1) && (j <= Pb->length - 1)) {
    if (Pa->elem[i].expn == Pb->elem[j].expn) { // auto c++11
      auto coef = Pa->elem[i].coef + Pb->elem[j].coef;
      if (coef != 0.0f) {
        tab.elem[tab.length].expn = Pa->elem[i].expn;
        tab.elem[tab.length].coef = coef;
        tab.length++;
      }
      i++, j++; // at the same move
    } else if (Pa->elem[i].expn < Pb->elem[j].expn) {
      tab.elem[tab.length++] = Pa->elem[i];
      cout << "<" << endl; // for test code
      i++;                 // just i move
    } else if (Pa->elem[i].expn > Pb->elem[j].expn) {
      tab.elem[tab.length++] = Pb->elem[j];
      j++; // just j move
    }
  }
  while (i + 1 <= Pa->length) {
    tab.elem[tab.length++] = Pa->elem[i]; // Pa拷贝剩余元素
    i++;
  }
  while (j + 1 <= Pb->length) {
    tab.elem[tab.length++] = Pb->elem[j]; // Pb拷贝剩余元素
    j++;
  }

  // PolynoShow
  /*
  cout << "tab.length = " << tab.length << endl;
  PolynoShow(&tab);
  */

  // return value
  Res->length = tab.length;
  Res->elem = tab.elem;
}

// 4.1 减法
template <typename T> void SubPolyno(T *Pa, T *Pb, T *Res) {
  T tab;
  /*
  | 	1> 假设多项式Pa与多项式Pb每项次幂均不相同，
  |	2> 那么合并后的多项式个数等于二者之和
  |	3> 动态数组长度 = 二者之和
  */
  tab.elem = new ElemType[Pa->length + Pb->length];
  tab.length = 0;
  for (int i = 0; i < Pb->length; i++)
    Pb->elem[i].coef *= -1;
  AddPolyno(Pa, Pb, &tab);
  Res->length = tab.length;
  Res->elem = tab.elem;
}

// 4.2 乘法
template <typename T> void MulPolyno(T *Pa, T *Pb, T *merge) {
  T ptab;
  ptab.elem = new ElemType[Pa->length * Pb->length]; // mul result
  ptab.length = 0;
  // 展开项
  for (int i = 0; i < Pa->length; i++)
    for (int j = 0; j < Pb->length; j++) {
      ptab.elem[ptab.length].coef =
          Pa->elem[i].coef * Pb->elem[j].coef; // 系数相乘
      ptab.elem[ptab.length].expn =
          Pa->elem[i].expn + Pb->elem[j].expn; // 指数相加
      ptab.length++;                           // lens + 1
    }
  printf("mul result: \n");
  PolynoShow(&ptab);
  // 合并项(升序排序)
  int *visit = new int[ptab.length]; // 创建标记数组，长度与其等长
  memset(visit, 0, sizeof(int) * ptab.length);
  merge->elem = new ElemType[ptab.length];
  float coef;
  int index = 0, flag = 0;
  for (int i = 0; i < ptab.length; flag ? i = index, flag = 0 : i++)
    for (int j = i + 1; j < ptab.length; j++) {
      if (ptab.elem[i].expn == ptab.elem[j].expn &&
          (visit[i] == 0 && visit[j] == 0)) {
        coef = ptab.elem[i].coef + ptab.elem[j].coef;
        if (coef != 0) { // merge same expn item
          merge->elem[merge->length].expn = ptab.elem[i].expn;
          merge->elem[merge->length].coef += coef;
          merge->length++;
          visit[i] = 1;
          visit[j] = 1;
        }
      } else if (ptab.elem[i].expn < ptab.elem[j].expn &&
                 (visit[i] == 0 && visit[j] == 0)) {
        if (j == ptab.length - 1) {
          merge->elem[merge->length].expn = ptab.elem[i].expn;
          merge->elem[merge->length].coef = ptab.elem[i].coef;
          merge->length++;
          visit[i] = 1;
        }
      } else if (ptab.elem[i].expn > ptab.elem[j].expn &&
                 (visit[i] == 0 && visit[j] == 0)) {
        index = i;
        flag = 1;
        i = j;
      }
    }
  delete[] ptab.elem;
}

// 8.0 打印
template <typename T> bool PolynoShow(T *ptab) {
  if (!ptab->elem) {
    printf("null \n");
    return false;
  }
  for (int i = 0; i <= ptab->length - 1; i++) {
    if (i != 0)
      printf(" ");
    if (i % 4 == 0 && i != 0)
      printf("\t\n");
    printf("[%d].(%.1f, %d)", i, ptab->elem[i].coef, ptab->elem[i].expn);
  }
  printf("\n");
  return true;
}
