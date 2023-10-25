/**
 * @file ch02-3_circlinklist.hpp
 * @author skyadv (you@domain.com)
 * @brief 单链循环表:circular linked list
 * 没有NULL空指针
 * 存储方式：链式存储
 * @version 0.1
 * @date 2023-03-08
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __circ_link_list_hpp__
#define __circ_link_list_hpp__

// debug mode
#if 0
#define DEBUG  // 调试模式
#else
#undef DEBUG
#endif

#include <cstdlib>
#include <iostream>

template <typename ElemType>
class cir_LinkList {
 public:
  typedef struct LNode {
    ElemType data;
    struct LNode* next;
  } LNode, *LinkList;

 public:
  /**
   * @brief Construct a new cir LinkList object
   *
   */
  cir_LinkList() {
    if (!InitList()) {
#ifdef DEBUG
      std::printf("call cir_LinkList ctor\n");
#endif
      exit(1);  // exception exit
    }
  }
  /**
   * @brief Destroy the cir LinkList object
   *
   */
  ~cir_LinkList() {
#ifdef DEBUG
    std::printf("call dest function:\n");
#endif
    DestoryList();
#ifdef DEBUG
    std::printf("head_node addr:%p\n", list);
#endif
    delete list;
    list = NULL;
  }
  /**
   * @brief 初始化
   *
   * @return true
   * @return false
   */
  bool InitList() {
    list = new LNode;  // new head_node
    if (!list) {
#ifdef DEBUG
      std::printf("memory allocat failed\n");
#endif
      return false;
    }
    list->next = list;  // 构造一个空表。指针域指向头结点
    return true;
  }
  /**
   * @brief 链表判空
   *
   * @return true
   * @return false
   */
  bool ListEmpty() {
    if (list->next == list) return true;  // 为空，返回值为1
    return false;                         // 否则，返回值为0
  }
  /**
   * @brief 销毁链表
   *
   * @return true
   * @return false
   */
  bool DestoryList() {
    if (this->ListEmpty()) return false;
    LNode* p = list;
    std::size_t i = 0;
    while (list->next != list) {
      p = list->next;
#ifdef DEBUG
      std::printf("%3lld:%p\n", i++, p);
#endif
      list->next = p->next;
      delete p;
    }
    return true;
  }
  /**
   * @brief list length
   *
   * @return std::size_t
   */
  std::size_t ListLength() {
    if (this->ListEmpty()) return 0;
    LNode* p;
    std::size_t length = 0;
    p = list->next;
    while (p != list) {
      p = p->next;
      ++length;
    }
    return length;
  }
  /**
   * @brief 头插法
   *
   * @param n
   * @return true
   * @return false
   */
  bool ListCreate_H(std::size_t n) {
    LNode* s;
    while (n--) {
      s = new LNode;
      if (!s) {
#ifdef DEBUG
        std::printf("memory allocat failed!\n");
#endif
        return false;
      }
      s->data = n + 1;
      s->next = list->next;
      list->next = s;
    }
    return true;
  }
  /**
   * @brief 尾插法
   *
   * @param n
   * @return true
   * @return false
   */
  bool ListCreate_R(std::size_t n) {
    LNode *s, *rear = list;
    while (n--) {
      s = new LNode;
      if (!s) {
#ifdef DEBUG
        std::printf("memory allocat failed!\n");
#endif
        return false;
      }
      s->data = n + 1;
      s->next = rear->next;
      rear->next = s;
      rear = s;
    }
    return true;
  }
  /**
   * @brief 插入
   *
   * @param index
   * @param elem
   * @return true
   * @return false
   */
  bool ListInsert(std::size_t index, ElemType elem) {
    LNode* p = list;
    std::size_t j = 0;
    while (p->next != list && j < index - 1) {
      p = p->next;
      j++;
    }
    if (j + 1 == index) goto INSERT;  // insert node of rear
    if (p->next == list || j > index - 1) return false;
  INSERT:
    LNode* s = new LNode;
    s->data = elem;
    s->next = p->next;
    p->next = s;
    return true;
  }
  /**
   * @brief 删除
   *
   * @param index
   * @param elem
   * @return true
   * @return false
   */
  bool ListDelete(std::size_t index, ElemType& elem) {
    LNode* p = list;
    std::size_t j = 0;
    while (p && j < index - 1) {
      p = p->next;
      j++;
    }
    if (p->next != list && (j + 1) == index) goto DELE;  // only one node delete
    if (p == list || j > index - 1) return false;
  DELE:
    LNode* s = p->next;
    elem = s->data;
    p->next = s->next;
    delete s;
    return true;
  }
  /**
   * @brief traverse list
   *
   * @param select
   * @return true
   * @return false
   */
  bool traverseList(int select = 2) {
    if (this->ListEmpty()) {
      std::printf("\nlist is null\n");
      return false;
    }
    LNode* p = list->next;  // first node
    std::size_t i = 0;
    switch (select) {
      case 1: {
        while (p != list) {
          std::printf("%3lld:%p\n", i++, p);
          p = p->next;
        }
      } break;
      case 2: {
        while (p != list) {
          std::cout << "[" << (i++) << "]=" << (p->data) << std::endl;
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