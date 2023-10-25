#include <cstdio>
#include <iostream>

#if 0
#define DEBUG
#define DEBUGVAR
#else
#undef DEBUG
#undef DEBUGVAR
#endif

typedef struct Node {
  int data;
  struct Node* next;
} LNode, *LinkList;

void InitList(LinkList& list) {
  if (!list)
    return;
  else {
    list = new LNode;
    list->next = list;
  }
}
// rear insert node
void ListCreate_R(LinkList& list, int n, int val) {
  LNode *s, *rear = list;
  while (n--) {
    s = new LNode;
    if (s == NULL) std::printf("memory allocat failed!\n");
    s->data = val++;
    s->next = rear->next;
    rear->next = s;
    rear = s;
  }
}

void traverseList(LinkList& list) {
  if (list->next == list) return;
  LNode* p = list->next;
  std::printf("list:%p\n", list);
#ifdef DEBUGVAR
  std::size_t i = 0;
#endif
  while (p != list) {
#ifdef DEBUG
    i = p->data;
    std::printf("%d [%lld]=%p\n", p->data, i, p);
#endif  // DEBUG
    p = p->next;
  }
}

void josephusRing(LinkList& list, int num, int m) {
  LNode *p, *s;
  p = list->next;  // p point to first node
  int spk = 1;
  s = NULL;
#ifdef DEBUGVAR
  std::size_t i = 0;
#endif  //  debugvar
  while (list->next != list) {
    if (spk == m) {
      std::cout << p->data << " ";
      p == list->next ? list->next = p->next : s->next = p->next;
#ifdef DEBUG
      i = p->data;
      std::printf("debug:[%lld]=%p\n", i, p);
#endif
      delete p;
      p = s->next;
      p == list ? spk = 0 : spk = 1;
    }
    s = p;
    p = p->next;
    if (p != list) spk++;
  }
}

// 创建不含头结点循环链表
void josephus_Nhead(LinkList& list, int num, int m) {
  list = new Node;
  if (list == NULL) return;
  list->next = list;
  list->data = 1;
  LNode *s, *rear = list;
  for (size_t i = 2; i <= num; i++) {
    s = new Node;
    if (s == NULL) {
#ifdef DEBUG
      std::printf("memory allocat failed!\n");
#endif
      return;
    }
    s->data = i;
    s->next = rear->next;
    rear->next = s;
    rear = s;
  }
  // josephus ring traverse list.
  LNode* p = list;
  int spk = 1;
  s = p;
  while (s->next != s) {
    if (spk == m) {  // m >= 2
      spk = 1, std::cout << p->data << " ";
      s->next = p->next;
      delete p;
      p = s->next;
    }
    s = p;
    p = p->next;
    spk++;
  }
  std::cout << s->data << std::endl;
}

void josephus_Array(LinkList& list, int num, int m) {
  list = new LNode;  // list first node
  if (list == NULL) return;
  list->next = list;
  list->data = 0;
  LNode* s;
  for (int i = 2; i <= num; i++) {  // list no head node.
    s = new LNode;
    if (s == NULL) {
      std::printf("memory allocat failed!\n");
      return;
    }
    s->data = 0;
    s->next = list->next;
    list->next = s;
  }
  // josephus array traverse list.
  LNode* p = list;
  int spk = 0, tal = 0, i = 0;
  while (tal != num) {
    if (p->data == 0) {
      spk++;
      if (spk == m) spk = 0, tal++, p->data = -1, std::cout << i + 1 << " ";
    }
    p = p->next;
    i = (i + 1) % num;
  }
}

void testSample_a(void) {
  int num, m;
  std::cin >> num >> m;
  LinkList list;
  InitList(list);
  ListCreate_R(list, num, 1);
  traverseList(list);
  josephusRing(list, num, m);
}

void testSample_b(void) {
  int num, m;
  std::cin >> num >> m;
  LinkList list;
  josephus_Nhead(list, num, m);
}

void testSample_c(void) {
  int num, m;
  std::cin >> num >> m;
  LinkList list;
  josephus_Array(list, num, m);
}

int main(void) {
  testSample_c();
  return 0;
}