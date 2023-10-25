/**
 * @file ch02_1_seqlist.hpp
 * @author skyadv (you@domain.com)
 * @brief 线性表——顺序表
 * 实现模型：静态表和动态表
 * @version 0.1
 * @date 2023-03-03
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef __seq_list_hpp__
#define __seq_list_hpp__

#include <cstdlib>
#include <iostream>

// 定义数据类型
// typedef int STATUS;
// typedef int ElemType;

#define MAXSIZE 100  // 线性表容量
#define ARRAY        // 静态定义宏

template <typename ElemType>
class seq_List {
 private:
#ifdef ARRAY
  // 线性表结构:静态表定义
  typedef struct sqlist {
    std::size_t length;      // 表长
    ElemType elem[MAXSIZE];  // 数组类型
  } sqlist;
#else
  // 线性表结构:动态表定义
  typedef struct SQList {
    std::size_t length;  // 表长
    ElemType* elem;      // 指针类型，作基地址
  } SQList;
#endif
 public:
  /**
   * @brief Construct a new List_seq object
   *
   */
  seq_List() {
#ifdef ARRAY
    if (list.elem == nullptr) {
      std::printf("array allocat failed!\n");
      exit(1);  // exception exit
    }
#else
    list.elem = new ElemType[MAXSIZE];
    if (!list.elem) {
      std::printf("memory allocat failed!\n");
      std::exit(1);  // exception exit
    }
#endif
    list.length = 0;
  }
  /**
   * @brief Construct a new List_seq object
   *
   * @param length
   */
  seq_List(std::size_t length) {
#ifndef ARRAY
    list.elem = new ElemType[length];
    if (!list.elem) {
      std::printf("memory allocat failed!\n");
      exit(1);  // exception exit
    }
#endif
  }
  /**
   * @brief Destroy the List_seq object
   *
   */
  ~seq_List() {
#ifdef ARRAY
    list.length = 0;
#else
    if (list.elem) delete[] list.elem;
    list.elem = nullptr;
    list.length = 0;
#endif
  }
  /**
   * @brief 初始化
   *
   * @return true
   * @return false
   */
  bool InitList() {
#ifndef ARRAY
    if (list.elem == nullptr) {
      list.elem = (ElemType*)malloc(sizeof(ElemType) * MAXSIZE);
      list.length = 0;
      if (!list.elem) return false;
      return true;
    }
#endif
    list.length = 0;
    return true;
  }
  /**
   * @brief 销毁线性表
   *
   * @tparam ElemType
   */
  void DestoryList() {
#ifdef ARRAY
    list.length = 0;
#else
    if (list.elem) free(list.elem);
    list.elem = nullptr;
    list.length = 0;
#endif
  }
  /**
   * @brief 清空线性表
   *
   * @tparam ElemType
   */
  void ClearList() {
    list.length = 0;  // linerlist length set 0
  }
  /**
   * @brief 取线性表长度
   *
   * @tparam ElemType
   * @return std::size_t
   */
  std::size_t ListLength() { return (list.length); }
  /**
   * @brief 判定线性表是否为空表
   *
   * @tparam ELemtype
   * @return std::size_t 线性表长度为0，返回值为1
   */
  std::size_t ListEmpty() {
    if (ListLength() == 0) return 1;  // 线性表长度为0，返回值为1
    return 0;                         // 否则，返回值为1
  }
  /**
   * @brief 创建新表数据
   * 线性表注入新的数据，从表头开始注入数据
   * @tparam ElemType
   * @return true
   * @return false
   */
  bool ListCreate_Data() {
    if (list.length >= MAXSIZE) {
      std::printf("\nlist had been full!\n");
      return false;
    }
    std::printf("\n input data number:\n");
    ElemType value;
    int number = 0;
    std::scanf("%d", &number);
    std::printf("\nplease input data length:\n");
    std::cin >> value;
    for (int i = 0; i < number; i++) {
      list.elem[i++] = value;
      list.length++;
      std::cin >> value;
      if (list.length >= MAXSIZE) break;
    }
    return true;
  }
  /**
   * @brief 线性表的取值
   *
   * @tparam ElemType
   * @param i
   * @param getValue
   * @return true
   * @return false
   */
  bool GetElem(int index, ElemType& getValue) {
    if (index < 1 || index > list.length) return false;
    getValue = list.elem[index - 1];
    return true;
  }
  /**
   * @brief 线性表的取值
   *
   * @tparam ElemType
   * @param i
   * @param getValue
   * @return true
   * @return false
   */
  bool GetElem(int index, ElemType* getValue) {
    if (index >= 1 && index <= list.length) {
      *getValue = list.elem[index - 1];
      return true;
    }
    return false;
  }
  /**
   * @brief 查找 按值查找
   *
   * @tparam ElemType
   * @param findElem
   * @return int
   */
  int LocateElem(ElemType& findElem) {
    for (int i = 0; i < list.length - 1; i++) {
      if (findElem == list.elem[i]) return i + 1;  // 查找成功，返回为序号
    }
    return -1;  // 查找失败，返回-1
  }
  /**
   * @brief 查找 按值查找
   * 方法：夹逼准则
   * @tparam ElemType
   * @param findElem
   * @return int
   */
  int LocateElem(ElemType* findElem) {
    int i = 0;
    while (i < list.length && *findElem != list.elem[i]) i++;
    if (i < list.length) return i + 1;  // 注意不能取等号，否则查找错误
    return -1;
  }
  /**
   * @brief 查找 按值查找
   * 返回所在表中地址
   * @tparam ElemType
   * @param elem
   * @return ElemType*
   */
  ElemType* find(ElemType& elem) {
    ElemType* p = nullptr;
    std::size_t i = 0;
    for (; i < list.length; i++) {
      if (elem == list.elem[i]) {
        p = &list.elem[i];
        break;
      }
    }
    return p;
  }
  /**
   * @brief 查找 按值查找
   * 方法：夹逼准则
   * @tparam ElemType
   * @param elem
   * @return ElemType*
   */
  ElemType* find(ElemType* elem) {
    ElemType* p = nullptr;
    std::size_t i = 0;
    while (i < list.length && *elem != list.elem[i]) i++;
    if (i < list.length) p = &list.elem[i];
    return p;
  }
  /**
   * @brief
   * 插入算法思路：
   * 判断储存是否已满
   * i位置后元素向后面移动,i位置前元素位置不变，并且最先移动表尾元素a[length-1]
   * 元素位置为 n+1 个
   * 表尾插入元素，速度最快，也是出发点
   * 插入范围：0 ~ n+1
   * @tparam ElemType
   * @param i
   * @param elem
   * @return true
   * @return false
   */
  bool ListInsert(std::size_t index, ElemType elem) {  // i是位序
    if (list.length == MAXSIZE) return false;          // 储存是否已满
    if (index >= MAXSIZE) return false;  // i值大于容量，不合法
    if (index < 1 || index > list.length + 1) return false;  // i值是否合法
    for (std::size_t j = list.length - 1; j >= index - 1; j--)
      list.elem[j + 1] = list.elem[j];  // 向后移动
    list.elem[index - 1] = elem;        // 插入新元素值
    list.length++;                      // 表长加1
    return true;
  }
  /**
   * @brief 头插
   *
   * @tparam ElemType
   * @param elem
   */
  void push_front(ElemType elem) {
    if (list.length == MAXSIZE) return;
    for (std::size_t i = list.length - 1; i >= 0; i--)
      list.elem[i + 1] = list.elem[i];
    list.elem[0] = elem;
    list.length++;
  }
  /**
   * @brief 尾插
   *
   * @tparam ElemType
   * @param elem
   */
  void push_back(ElemType elem) {
    if (list.length == MAXSIZE) return;
    list.elem[list.length] = elem;
    list.length++;
  }
  /**
   * @brief
   * 删除算法思路：
   * 本质覆盖元素，元素向前i位置移动
   * 其他和插入特性类似
   * @tparam ElemType
   * @param index
   * @param elem
   * @return true
   * @return false
   */
  bool DeleteValue(int index, ElemType& elem) {
    if (list.length == 0) return false;  // 空表返回
    if (index < 1 || index > list.length) return false;
    elem = list.elem[index - 1];
    for (std::size_t i = index; i < list.length; i++)
      list.elem[i] = list.elem[i + 1];  // 向前移动
    list.length--;                      // 表长减1
    return true;
  }
  /**
   * @brief 删除
   * 删除表中元素等于该值的位置
   * 删除包括重复元素
   * @tparam ElemType
   * @param elem
   * @return true
   * @return false
   */
  bool DeleteValue(ElemType elem) {
    if (list.length == 0) return false;  // 空表返回
    seq_List<ElemType> item;             // 定义临时表
    for (std::size_t i = 0, j = 0; i < this->list.length; i++) {
      if (elem != this->list.elem[i]) {
        item.list.elem[j++] = this->list.elem[i];  // 拷贝元素
        item.list.length++;                        // 长度加1
      }
    }
    this->list.length = 0;  // 清空原表
    for (std::size_t i = 0; i < item.list.length; i++) {
      this->list.elem[i] = item.list.elem[i];
      this->list.length++;
    }
    return true;
  }
  /**
   * @brief 头删
   *
   * @tparam ElemType
   */
  void pop_front() {
    if (list.length == 0) return;
    for (std::size_t i = 0; i < list.length; i++)
      list.elem[i] = list.elem[i + 1];
    // for (std::size_t i = 1; i <= list.length; i++) {
    //     list.elem[i - 1] = list.elem[i];
    // }
    list.length--;  // 表长减1
  }
  /**
   * @brief 尾删
   *
   * @tparam ElemType
   */
  void pop_back() {
    if (list.length == 0) return;
    if (list.length >= 1) list.length--;  // 表长减1
  }
  /**
   * @brief 逆置
   * 逆序线性表
   * @tparam ElemType
   */
  void ListReverse() {
    if (list.length == 0) return;
    std::size_t n = list.length;
    ElemType elem;
    for (std::size_t i = 0; i < n / 2; i++) {
      elem = list.elem[i];
      list.elem[i] = list.elem[n - 1 - i];
      list.elem[n - 1 - i] = elem;
    }
  }
  /**
   * @brief 返回前驱结点
   *
   * @param cur_e
   * @param pre_e
   * @return true
   * @return false
   */
  bool priorElem(ElemType cur_e, ElemType& pre_e) {
    if (this->list.length == 0) return false;  // 空表
    if (this->list.elem[0] == cur_e) return false;
    std::size_t i = 1;
    while (i < this->list.length) {
      if (cur_e == this->list.elem[i]) {
        pre_e = this->list.elem[i - 1];
        break;
      }
      i++;
    }
    return true;
  }
  /**
   * @brief 返回前驱结点
   *
   * @param cur_e
   * @param pre_e
   * @return true
   * @return false
   */
  bool priorElem(ElemType* cur_e, ElemType* pre_e) {
    if (this->list.length == 0) return false;  // 空表
    std::size_t i = 1;
    if (*cur_e != this->list.elem[0]) {  // 查找元素不是第一个
      while (i < this->list.length && *cur_e != this->list.elem[i]) i++;
      if (i < this->list.length) {
        *pre_e = this->list.elem[i - 1];
        return true;
      }
    }
    return false;
  }
  /**
   * @brief 返回后继结点
   *
   * @param cur_e
   * @param next_e
   * @return true
   * @return false
   */
  bool nextElem(ElemType cur_e, ElemType& next_e) {
    if (this->list.length == 0) return false;  // 空表
    if (this->list.elem[list.length - 1] == cur_e) return false;
    std::size_t i = 0;
    while (i < this->list.length - 1) {
      if (cur_e == this->list.elem[i]) {
        next_e = this->list.elem[i + 1];
        break;
      }
      i++;
    }
    return true;
  }
  /**
   * @brief 返回后继结点
   *
   * @param cur_e
   * @param next_e
   * @return true
   * @return false
   */
  bool nextElem(ElemType* cur_e, ElemType* next_e) {
    if (this->list.length == 0) return false;  // 空表
    std::size_t i = 0;
    // 查找元素不是最后一个
    if (*cur_e != this->list.elem[this->list.length - 1]) {
      while (i < this->list.length - 1 && *cur_e != this->list.elem[i]) i++;
      if (i < list.length - 1) {
        *next_e = this->list.elem[i + 1];
        return true;
      }
    }
    return false;
  }
  /**
   * @brief traverse list
   * 遍历线性表
   * @tparam ElemType
   * @return true
   * @return false
   */
  bool TraverseList() {
    if (this->ListEmpty()) {  // 空表
      std::printf("\nliner list is null!\n");
      return false;
    }
    for (std::size_t i = 0; i < list.length; i++) {
      if (i != 0) std::printf(" ");
      std::cout << "[" << i << "]=" << list.elem[i];
    }
    std::printf("\n");
    return true;
  }
  /**
   * @brief 线性表合并
   * 简单合并:合并表元素唯一，无序
   * @tparam ElemType
   * @param LS
   */
  void MergeList(seq_List<ElemType> LS) {
    int n = LS.list.length;
    ElemType item;
    for (std::size_t i = 0; i < n; i++) {
      GetElem(i, item);  // LS：获取元素
      if (this->LocateElem(item) == -1) ListInsert(++(this->list.length), item);
    }
  }
  /**
   * @brief 有序表合并
   * 有序合并:合并表元素并不唯一，有序
   * @param LSdes 目标表
   * @param LSres 存储表
   */
  void MergeList(seq_List<ElemType> const& LSdes, seq_List<ElemType>& LSres) {
#ifndef ARRAY
    ElemType* pa = this->list.elem;  // pa point to LA
    ElemType* pb = LSdes.list.elem;  // pb point to LB
    ElemType* pc = nullptr;
    ElemType* pa_last = pa + this->list.length - 1;
    ElemType* pb_last = pb + LSdes.list.length - 1;
    LSres.list.length =
        this->list.length + LSdes.list.length;  // calc LSres length
    delete[] LSres.list.elem;
    LSres.list.elem = new ElemType[LSres.list.length];
    LSres.list.length = 0;                    // lc.length reset 0
    pc = LSres.list.elem;                     // pc point to LC
    while (pa <= pa_last && pb <= pb_last) {  // notes: equal operation
      if (*pa < *pb)
        *pc++ = *pa++;
      else if (*pa == *pb) {  // consider equal operation
        *pc++ = *pa++, pb++;
        LSres.list.length++;
        continue;
      } else {
        *pc++ = *pb++;
      }
      LSres.list.length++;
    }
    // notes:equal operation
    while (pa <= pa_last) *pc++ = *pa++, LSres.list.length++;
    while (pb <= pb_last) *pc++ = *pb++, LSres.list.length++;
#endif
  }

 private:
#ifdef ARRAY
  sqlist list;  // pointer or reference or object
#else
  SQList list;
#endif
};

#endif