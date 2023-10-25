#include <iostream>

typedef struct node {
  int data;
  struct node* next;
} LNode, *LinkList;

void InitList(LinkList list) {
  list = new LNode;
  list->next = list;
}
// rear insert node
void ListCreate_R(LinkList list, int n) {
  InitList(list);
  LNode *s, *rear = list;
  while (n--) {
    s = new LNode;
    if (s == NULL) std::printf("memory allocat failed!\n");
    s->data = 0;
    s->next = rear->next;
    rear->next = s;
    rear = s;
  }
}

void josephusRing(LinkList list, int num, int m) {
  ListCreate_R(list, num);
  LNode *p, *s;
  int tal = 0, spk = 0, i = 0;
  p = list->next;
  s = list;
  while (1) {
    if (p == list) continue;  // jump head node
    spk++;
    if (spk == m) {
      tal++, spk = 0, std::cout << i + 1 << " ";
      s->next = p->next;
      delete p;
      p = s->next;
    }
    if (tal == num - 1) break;
    s = p;
    p = p->next;
    i++;
    if (i > num - 1) i = 0;
  }
}

int main(void) {
  int num, m;
  std::cin >> num >> m;
  LinkList list;
  josephusRing(list, num, m);
  return 0;
}