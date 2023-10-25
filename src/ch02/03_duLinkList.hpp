/**
 * @file ch02_3_duLinklist.hpp
 * @author skyadv (you@domain.com)
 * @brief 线性表——双链表
 * 存储方式：链式存储
 * @version 0.1
 * @date 2023-03-09
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef __du_link_list_hpp__
#define __du_link_list_hpp__

#if 1
#define DEBUG
#else
#undef DEBUG
#endif

#include <cstdlib>
#include <iostream>

template <typename ElemType>
class du_LinkList {
 public:
  typedef struct LNode {
    ElemType data;
    struct LNode* prev;
    struct LNode* next;
  } LNode, *LinkList;
  /**
   * @brief Construct a new du LinkList object
   *
   */
  du_LinkList() {
    if (!this->InitList()) {
      std::printf("call du_LinkList ctor failed!\n");
      exit(1);  // exception exit
    }
  }
  /**
   * @brief Destroy the du LinkList object
   *
   */
  ~du_LinkList() {
    std::printf("call dest function:\n");
    DestoryList();
    std::printf("head_node addr:%p\n", list);
    delete list;
    list = NULL;
  }
  /**
   * @brief 初始化空表
   *
   * @return true
   * @return false
   */
  bool InitList() {
    list = new LNode;  // new header node
    if (!list) {
      std::printf("memory allocat failed!\n");
      return false;
    }
    list->prev = list->next = NULL;
    return true;
  }
  /**
   * @brief 销毁链表
   *
   * @return true
   * @return false
   */
  bool DestoryList() {
    if (this->ListEmpty()) return false;
    LNode* p = list->next;  // first node
    std::size_t i = 0;
    while (p) {
      std::printf("%3lld:%p\n", i++, p);
      list->next = p->next;
      if (p->next) p->next->prev = list;
      delete p;
      p = list->next;
    }
    return true;
  }
  bool ListEmpty() {
    if (list->next == NULL) return true;
    return false;
  }
  std::size_t ListLength() {
    if (ListEmpty()) return 0;
    std::size_t length = 0;
    LinkList p = list->next;
    while (p) {
      p = p->next;
      ++length;
    }
    return length;
  }
  /**
   * @brief traverse list
   *
   * @param select
   * @return true
   * @return false
   */
  bool traverseList(int select = 2) {
    if (ListEmpty()) return false;
    LinkList p = list->next;
    std::size_t i = 0;
    switch (select) {
      case 1: {
        while (p) {
          std::printf("%3lld:%p\n", i++, p);
          p = p->next;
        }
      } break;
      case 2: {
        while (p) {
          std::cout << "[" << (i++) << "]=" << (p->data) << std::endl;
          p = p->next;
        }
      } break;
      default:
        break;
    }
    return true;
  }
  /**
   * @brief 建立链表 头插法
   *
   * @param n
   * @return true
   * @return false
   */
  bool ListCreate_H(std::size_t n) {
    LNode* s;
    while (n--) {
      s = new LNode;
      s->data = n;
      if (s == NULL) {
        std::printf("memory allocat failed!\n");
        return false;
      }
      s->next = list->next;
      s->prev = list;
      if (list->next) list->next->prev = s;  // list->next != NULL
      list->next = s;
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
    LNode* s;
    LNode* rear;
    rear = list;
    while (n--) {
      s = new LNode;
      s->data = n;
      if (s == NULL) {
        std::printf("memory allocat failed!\n");
        return false;
      }
      s->next = NULL;
      s->prev = rear;
      rear->next = s;
      rear = s;
    }
    return true;
  }
  /**
   * @brief 插入
   * 在链表中第i个位置插入元素elem
   * @param index
   * @param elem
   * @return true
   * @return false
   */
  bool ListInsert(std::size_t index, ElemType elem) {
    LNode* p = list;
    std::size_t j = 0;
    while (p && j < index) {
      p = p->next;
      j++;
    }
    if (p == NULL || j > index) {
      std::printf("insert node failed!\n");
      return false;
    }
    LNode* s = new LNode;
    s->data = elem;
    s->next = p;
    s->prev = p->prev;
    p->prev->next = s;
    p->prev = s;
    return true;
  }
  /**
   * @brief 删除
   * 在链表中第i个位置删除元素elem
   * @param index
   * @param elem
   * @return true
   * @return false
   */
  bool ListDelete(std::size_t index, ElemType& elem) {
    LNode* p = list;
    std::size_t j = 0;
    while (p->next && j < index) {
      p = p->next;
      j++;
    }
    if ((p->next == NULL) || j > index) return false;
    elem = p->data;
    p->prev->next = p->next;
    if (p->next) p->next->prev = p->prev;  // p->next != NULL
    delete p;
    return true;
  }

 private:
  LinkList list;  // header pointer
};
#endif