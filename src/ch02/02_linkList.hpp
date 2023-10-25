/**
 * @file ch02_2_linklist.hpp
 * @author skyadv (you@domain.com)
 * @brief 线性表——单链表
 * 实现模型：带头结点的单链表
 * @version 0.1
 * @date 2023-03-04
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef __link_list_hpp__
#define __link_list_hpp__

#if 1
#define HEADER_NODE  // 是否附设头结点
#else
#undef HEADER_NODE
#endif

// debug mode
#if 1
#define DEBUG  // 调试模式
#else
#undef DEBUG
#endif

#include <cstdlib>
#include <iostream>

template <typename ElemType>
class link_List {
 public:
  typedef struct LNode {
    ElemType data;
    struct LNode* next;
  } LNode, *LinkList;
  /**
   * @brief Construct a new List_link object
   *
   */
  link_List() {
#ifdef HEADER_NODE
    list = new LNode;  // 插入头结点
    if (!list) {
      std::printf("memory allocat failed!\n");
      exit(1);  // exception exit
    }
    list->next = NULL;
#else
    list = NULL;  // create empty list can't write operation:list->next = null
#endif
  }
  /**
   * @brief Destroy the List_link object
   *
   */
  ~link_List() {
#ifdef DEBUG
    std::printf("call dest function\n");
#endif
    DestoryList();
  }
  /**
   * @brief 初始化
   * 算法思路：
   * a.生成新结点作为头结点，用头指针指向头结点
   * b.将头结点的指针域置为空
   * @return true
   * @return false
   */
  bool InitList() {
#ifdef HEADER_NODE
    list = new LNode;         // 创建头结点
    if (!list) return false;  // 创建失败后返回0
    list->next = NULL;        // 指针域赋空
    return true;              // 创建完成后返回1
#else
    list = NULL;  // create empty list
    return true;
#endif
  }
  /**
   * @brief 销毁单链表
   * 算法思路：
   * 从头指针开始，依次释放所有结点
   * 关键词：从表的头指针开始处依次释放
   * 须注意：头结点也被释放占用空间
   * @return true
   * @return false
   */
  bool DestoryList() {
    LNode* p;
#ifdef DEBUG
    int i = 0;
#endif
#ifdef HEADER_NODE
    if (this->ListEmpty()) return false;  // 空表直接返回false
    while (list->next) {
      p = list->next;        // p 指向首元结点
      list->next = p->next;  // list 指针移动
#ifdef DEBUG
      std::printf("%3d:%p\n", i++, p);
#endif
      delete p;
    }
    std::printf("head_node addr:%p\n", list);
    delete list;
    list = NULL;
#else
    if (list == NULL) return false;
    while (list) {
      p = list;
      list = p->next;
      delete p;
    }
#endif
    return true;
  }
  /**
   * @brief 链表判空
   * 空表：链表中无元素，称为空链表(头指针和头结点仍然存在)
   * 算法思路：
   * 判断头结点的指针域是否空
   * @return true
   * @return false
   */
  bool ListEmpty() {
#ifdef HEADER_NODE
    if (list->next == NULL) return true;
    return false;
#else
    if (list == NULL) return true;
    return false;
#endif
  }
  /**
   * @brief 获取链表长度
   * 算法思路：
   * 从首元结点开始，依次计数所有结点
   * @return std::size_t
   */
  std::size_t ListLength() {
    std::size_t length = 0;           // 初始表长置0
    if (this->ListEmpty()) return 0;  // 判断空表，返回值为0
#ifdef HEADER_NODE
    LinkList p = list->next;  // p指向首元结点
#else
    LinkList p = list;
#endif
    while (p) {  // traverse list
      ++length;
      p = p->next;
    }
    return length;
  }
  /**
   * @brief 清空单链表
   * 链表仍然存在，但链表中无元素，成为空表(头指针和头结点仍然存在)
   * 算法思路：
   * 依次释放所有结点，并将头结点指针域置为空
   * @return int
   */
  int ClearList() {
    LNode *p, *q;
#ifdef HEADER_NODE
    p = list->next;  // p 指向首元结点
#else
    p = list;
#endif
    int i = 0;
    while (p) {
      // q = p;
      // p = p->next;
      // std::printf("%d:%p\n", i++, q);
      // delete q;  // 释放结点
      q = p->next;
      std::printf("%3d:%p\n", i++, p);
      delete p;
      p = q;
    }
    list->next = NULL;
    return 1;
  }
  /**
   * @brief 建立链表 头插法
   *
   * @param n
   * @return true
   * @return false
   */
  bool ListCreate_H(std::size_t n) {
    LNode* p;
    while (n--) {
      p = new LNode;
      p->data = n;
#ifdef HEADER_NODE
      p->next = list->next;
      list->next = p;
#else
      p->next = list;
      list = p;
#endif
    }
    return true;
  }
  /**
   * @brief 建立链表 尾插法
   *
   * @param n
   * @return true
   * @return false
   */
  bool ListCreate_R(std::size_t n) {
    LNode* p;
    LNode* rear;  // 尾指针
    rear = list;  // 尾指针指向list
    while (n--) {
      p = new LNode;
      p->data = n;
      p->next = NULL;
      rear->next = p;  // 尾插法重点
      rear = p;        // 尾指针移动
    }
    return true;
  }
  /**
   * @brief push_front
   * 头插法
   * @param elem
   */
  void push_front(ElemType elem) {
    LNode* s = new LNode;
    s->data = elem;
#ifdef HEADER_NODE
    s->next = list->next;
    list->next = s;
#else
    s->next = list;
    list = s;
#endif
  }
  /**
   * @brief push_back
   * 尾插法
   * @param elem
   */
  void push_back(ElemType elem) {
    LNode* s = new LNode;
    s->data = elem;
    LNode* p;
#ifdef HEADER_NODE
    p = list->next;  // 定义指针p指向首结点
#else
    p = list;
#endif
    if (this->ListEmpty()) {
      s->next = list->next;
      list->next = s;
    } else {
      while (p->next) p = p->next;
      s->next = p->next;
      p->next = s;
    }
  }
  /**
   * @brief Get the Elem object
   * 取值 取单链表中第i个元素的内容
   * 算法思路：
   * 从链表的头指针出发，顺着链域next逐个结点向下搜索，直至搜索第i个结点为止
   * 链表不是随机存取结构，而是顺序存取
   * @param index
   * @param elem
   * @return true
   * @return false
   */
  bool GetElem(std::size_t index, ElemType& elem) {
#ifdef HEADER_NODE
    LNode* p = list->next;
#else
    LNode* p = list;
#endif
    std::size_t i = 1;
    while (p && i < index) {
      p = p->next;
      i++;
    }
    // 假设有p == NULL 结束循环
    // 此时有p == NULL and j=5,index=10,仍然满足：j < index
    if (p == NULL || i > index)
      return false;  // p为空，j超过index范围。返回值为false
    elem = list->data;
    return true;
  }
  /**
   * @brief 取值 改进代码
   *
   * @param index
   * @param elem
   * @return true
   * @return false
   */
  bool getelem(std::size_t index, ElemType& elem) {
    LNode* p;
    std::size_t j = 1;
#ifdef HEADER_NODE
    p = list->nextl;
#else
    p = list;
#endif
    while (j < index && p != NULL) {
      p = p->next;  // p指针迭代
      j++;
    }
    if (j < index && p == NULL) return false;
    if (j == index) elem = p->data;
    return true;
  }
  /**
   * @brief 查找 返回结点指针
   *
   * @param elem
   * @return LNode*
   */
  LNode* LocateElem(ElemType elem) {
    LNode* p;
#ifdef HEADER_NODE
    p = list->next;
#else
    p = list;
#endif
    // while (p) {
    //   if (elem == p->data) return p;
    //   p = p->next;
    // }
    while (p && p->data != elem) p = p->next;
    return p;
  }
  /**
   * @brief 查找 返回结点索引：位序
   *
   * @param elem
   * @return std::size_t
   */
  std::size_t LocateElem(ElemType* elem) {
    std::size_t index = 0;
    LNode* p;
#ifdef HEADER_NODE
    p = list->next;
#else
    p = list;
#endif
    while (p && p->data != *elem) {
      index++;
      p = p->next;
    }
    if (p) return index;
    return 0;
  }
  /**
   * @brief 查找 find
   *
   * @param elem
   * @return ElemType*
   */
  ElemType* find(ElemType elem) {
    LNode* p;
#ifdef HEADER_NODE
    p = list->next;
#else
    p = list;
#endif
    ElemType* data = NULL;
    if (this->ListEmpty()) return data;
    while (p && p->data != elem) p = p->next;
    if (p) return (data = &p->data);
    return data;
  }
  /**
   * @brief 查找中间结点
   *
   * @return ElemType*
   */
  ElemType* findMiddle() {
    LNode* fast;  // fast pointer
    LNode* slow;  // slow pointer
    ElemType* data = NULL;
    if (this->ListEmpty()) return data;
    fast = slow = list;
    while (fast && fast->next) {
      fast = fast->next->next;
      slow = slow->next;
    }
    return (data = &slow->data);
  }
  /**
   * @brief 查找倒数第k个元素
   *
   * @param k
   * @return ElemType*
   */
  ElemType* findK(int k) {
    LNode* fast;
    LNode* slow;
    ElemType* data = NULL;
    if (this->ListEmpty()) return data;
    fast = slow = list->next;
    {
        // one way 代码多不一定显得简洁有力，相反不如soso方法2好
        // if (k == this->ListLength())
        //   return data = &(list->next->data);  // return first node data
        // if (k == 0) {
        //   while (fast->next) fast = fast->next;
        //   return data = &(fast->data);
        // }
        // while (--k) {
        //   fast = fast->next;
        //   std::printf("k = %d\n", k);
        // }
        // if (fast->next == NULL) return data;
        // while (fast->next) {
        //   fast = fast->next;
        //   slow = slow->next;
        // }
        // return data = &slow->data;
    }  // other way
    {  // soso
      while (fast->next) {
        if (k - 1 > 0) {
          fast = fast->next;
          k--;
        } else {
          fast = fast->next;
          slow = slow->next;
        }
      }
      return (data = &slow->data);
    }
  }
  /**
   * @brief FIND index
   *
   * @param index
   * @return ElemType*
   */
  ElemType* FINDK(int index) {
    LNode* fast;
    LNode* slow;
    fast = slow = list->next;
    while (fast->next) {
      if (--index <= 0) slow = slow->next;
      fast = fast->next;
    }
    if (index - 1 > 0) return NULL;
    return (&slow->data);
  }
  /**
   * @brief find max node value
   *
   * @return ElemType*
   */
  ElemType* findMax() {
    LNode *pmax, *p;
    pmax = list->next;     // 首元结点
    p = list->next->next;  // 第二结点
    if (pmax == NULL) return NULL;
    while (p) {
      if (pmax->data <= p->data) pmax = p;
      p = p->next;
    }
    return (&pmax->data);
  }
  /**
   * @brief find min node value
   *
   * @return ElemType*
   */
  ElemType* findMin() {
    LNode *pmin, *p;
    pmin = list->next;
    p = list->next->next;
    if (pmin == NULL) return NULL;
    while (p) {
      if (pmin->data >= p->data) pmin = p;
      p = p->next;
    }
    return (&pmin->data);
  }
  /**
   * @brief 插入
   * 在链表中第i个位置插入元素elem
   * 位置：1 <= i <= n+1
   * @param index
   * @param elem
   * @return true
   * @return false
   */
  bool ListInsert(std::size_t index, ElemType elem) {
    std::size_t j = 0;
    LNode* p = list;
    while (p && j < (index - 1)) {
      p = p->next;
      j++;
    }
    if (p == NULL || j > (index - 1)) return false;
    LNode* s = new LNode;  // 插入结点指针
    s->data = elem;        // 插入元素赋值
    s->next = p->next;
    p->next = s;
    return true;
  }
  /**l
   * @brief 删除
   * 在链表中第i个位置删除元素elem
   * 位置：1 <= i <= n
   * @param index
   * @return true
   * @return false
   */
  bool ListDelete(std::size_t index, ElemType& elem) {
    if (this->ListEmpty()) return false;
    LNode* p = list;
    std::size_t j = 0;
    while (p->next && j < (index - 1)) {
      p = p->next;
      j++;
    }
    if (p->next == NULL || j > (index - 1)) return false;
    LNode* s;
    s = p->next;
    elem = s->data;     // 记录删除元素值
    p->next = s->next;  // p->next = p->next->next;
    delete s;
    return true;
  }
  /**
   * @brief 头删
   *
   */
  void pop_front() {
    if (this->ListEmpty()) return;
    LNode* p = list->next;  // p 指向首元结点
    list->next = p->next;
    delete p;
  }
  /**
   * @brief 尾删
   *
   */
  void pop_back() {
    if (this->ListEmpty()) return;
    LNode* p = list->next;
    while (p->next->next != NULL) p = p->next;
    LNode* s = p->next;
    p->next = s->next;
    delete s;
    return;
  }
  /**
   * @brief 删除表中元素等于该值的位置
   * 删除包括重复元素
   * 快慢指针法
   * pfast -> first node
   * pslow -> header node
   * @param elem
   * @return int
   */
  int Delete_rep(ElemType elem) {
    if (this->ListEmpty()) return -1;
    LinkList table = new LNode;  // 声明储存链表
    LNode* ptab = table;         // ptab 指向table
    LNode* fast = list->next;    // fast 指向首元结点
    LNode* slow = list;          // slow 指向头指针
    while (fast) {
      if (elem != fast->data) {
        ptab->next = fast;  // 尾插法
        ptab = fast;
        slow->next = fast->next;
      }
      if (fast->next == NULL) ptab->next = NULL;
      if (elem == fast->data) slow = fast;  // 越过相等结点
      fast = fast->next;
    }
    this->DestoryList();
    this->list = table;
    return 1;
  }
  /**
   * @brief 链表逆置
   * 算法思路：
   * 头插法逆序造表
   */
  void ListReverse() {
    if (this->ListEmpty()) return;
    LinkList ptab = new LNode;
    ptab->next = NULL;
    LNode* p = list->next;
    LNode* q;
    while (p) {
      q = p;  // q -> list first node
      p = q->next;
      q->next = ptab->next;  // 头插法
      ptab->next = q;
    }
    this->list->next = ptab->next;
    delete ptab;
  }
  /**
   * @brief 合并：有序表
   *
   * @param Lsrc
   * @param Ldes
   */
  void MergeList(link_List<ElemType>* Lsrc, link_List<ElemType>* Ldes) {
    LNode *pa, *pb, *pc;
    pa = this->list->next;  // first node
    pb = Lsrc->list->next;  // first node
    pc = Ldes->list;
    while (pa && pb) {
      if (pa->data <= pb->data) {
        this->list->next = pa->next;
        pc->next = pa;
        pc = pa;
        pa = pa->next;
      } else {
        Lsrc->list->next = pb->next;
        pc->next = pb;
        pc = pb;
        pb = pb->next;
      }
    }
    pc->next = pa ? pa : pb;  // copy remind node
    this->list->next = Lsrc->list->next = NULL;
  }
  /**
   * @brief traverse list
   *
   * @return true
   * @return false
   */
  bool traverseList(int select = 2) {
    if (this->ListEmpty()) return false;
    LinkList p = list->next;
    std::size_t i = 0;
    switch (select) {
      case 1: {
        while (p) {
          std::printf("%3lld = :%p\n", i++, p);
          p = p->next;
        }
      } break;
      case 2: {
        while (p) {
          std::cout << "[" << (i++) << "]=" << p->data << std::endl;
          p = p->next;
        }
      } break;
      default:
        break;
    }
    return true;
  }

 private:
  LinkList list;
};

#endif