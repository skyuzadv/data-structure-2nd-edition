/**
 * @file ch02_5_crdulinklist.hpp
 * @author skyadv (you@domain.com)
 * @brief 双链循环表:circular double linked list
 * @version 0.1
 * @date 2023-03-11
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef __crdu_link_list_hpp__
#define __crdu_link_list_hpp__

#include <cstdlib>
#include <iostream>

template <typename ElemType>
class crdu_LinkList {
 public:
  typedef struct LNode {
    ElemType data;
    struct LNode *prev, *next;
  } LNode, *LinkList;
  /**
   * @brief Construct a new crdu LinkList object
   *
   */
  crdu_LinkList() {
    if (!InitList()) {
      std::printf("call crdu_LinkList ctor\n");
      exit(1);  // exception exit
    }
  }
  /**
   * @brief Destroy the crdu LinkList object
   *
   */
  ~crdu_LinkList() {
    std::printf("call dest function:\n");
    DestoryList();
    std::printf("head_node addr:%p\n", list);
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
    list = new LNode;
    if (!list) {
      std::printf("memory allocat failed!\n");
      return false;
    }
    list->prev = list->next = list;
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
    LNode* p;
    std::size_t i = 0;
    while (list->next != list) {
      p = list->next;
      p->next->prev = list;
      list->next = p->next;
      std::printf("%3lld:%p\n", i++, p);
      delete p;
    }
    return true;
  }
  /**
   * @brief 空表判断
   *
   * @return true
   * @return false
   */
  bool ListEmpty() {
    if ((list->next == list) && (list->prev == list)) return true;
    return false;
  }
  /**
   * @brief list length
   *
   * @return std::size_t
   */
  std::size_t ListLength() {
    if (this->ListEmpty()) return 0;
    LNode* p = list->next;
    std::size_t length = 0;
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
        std::printf("memory allocat failed!\n");
        return false;
      }
      s->data = n + 1;
      s->next = list->next;
      s->prev = list;
      list->next->prev = s;
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
        std::printf("memory allocat failed!\n");
        return false;
      }
      s->data = n + 1;
      s->next = rear->next;
      s->prev = rear;
      rear->next = s;
      list->prev = s;
      rear = s;
    }
    return true;
  }
  /**
   * @brief 插入 1 <= index <= n
   *
   * @param index
   * @param elem
   * @return true
   * @return false
   */
  bool ListInsert(std::size_t index, ElemType elem) {
    LNode* p = list;
    std::size_t j = 0;
    while (p->next != list && j < index) {
      p = p->next;
      j++;
    }
    if (p->next == list && j == index) goto INSERT;  // insert node of rear
    if (p->next == list || j > index) return false;
  INSERT:
    LNode* s = new LNode;
    s->data = elem;
    s->prev = p->prev;
    s->next = p;
    p->prev->next = s;
    return true;
  }
  /**
   * @brief 删除 1 <= index <= n
   *
   * @param index
   * @param elem
   * @return true
   * @return false
   */
  bool ListDelete(std::size_t index, ElemType& elem) {
    LNode* p = list;
    std::size_t j = 0;
    while (p->next != list && j < index) {
      p = p->next;
      j++;
    }
    if (p->next == list && j == index) goto DELE;  // only one node delete
    if (p->next == list || j > index) return false;
  DELE:
    elem = p->data;
    p->prev->next = p->next;
    p->next->prev = p->prev;
    delete p;
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