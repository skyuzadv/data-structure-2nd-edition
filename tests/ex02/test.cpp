#include <iostream>

#include "01_seqList.hpp"
#include "02_linkList.hpp"
#include "03_duLinkList.hpp"
#include "04_circLinkList.hpp"
#include "05_crduLinkList.hpp"

int main(int argc, char** argv) {
  // link_List<int> la, lb, lc;
  // du_LinkList<int> la, lb, lc;
  // cir_LinkList<int> la, lb, lc;
  crdu_LinkList<int> la, lb, lc;

  // la.ListCreate_H(5);
  // std::printf("la traverse list\n");
  // la.traverseList();
  // int elem;
  // int index = 5;
  // la.ListDelete(index, elem);
  // std::cout << "list delete index:" << index << " elem:" << elem <<
  // std::endl; std::printf("la traverse list\n"); la.traverseList();

  la.ListCreate_H(5);
  std::printf("la traverse list\n");
  la.traverseList();
  std::cout << "list length:" << (la.ListLength()) << std::endl;

  lb.ListCreate_R(5);
  std::printf("lb traverse list\n");
  lb.traverseList();
  std::cout << "list length:" << (lb.ListLength()) << std::endl;

  int index = 1;
  int insert = 100;
  la.ListInsert(index, insert);
  std::printf("list insert index = %d, elem = %d\n", index, insert);
  la.traverseList();

  int dele;
  la.ListDelete(index, dele);
  std::cout << "list delete index:" << index << " elem:" << dele << std::endl;
  std::printf("la delete list\n");
  la.traverseList();

  return 0;
}