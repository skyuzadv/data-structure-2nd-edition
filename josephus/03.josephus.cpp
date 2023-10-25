#include <iostream>

typedef struct node {
  int data;
  struct node* next;
} Node;

void josephusFunc(int num, int m) {
  Node *head = NULL, *rear = NULL, *s = NULL;
  head = new Node;
  if (NULL == head) {
    std::cout << "Memory Failed!";
    return;
  }
  head->data = 1;  // 从1开始编号
  head->next = NULL;
  rear = head;

  for (int i = 2; i <= num; i++) {  // 创建剩下的n-1个结点
    s = new Node;
    s->data = i;
    s->next = NULL;
    rear->next = s;
    rear = s;
  }
  rear->next = head;  // 指向头结点
  rear = head;

  while (rear->next != rear) {
    for (int i = 1; i < m; i++) {
      s = rear;
      rear = rear->next;
    }
    std::cout << rear->data << " ";
    s->next = rear->next;
    rear = rear->next;
  }
  std::cout << rear->data;
}

int main(void) {
  int num, m;
  std::cin >> num >> m;
  josephusFunc(num, m);
  return 0;
}