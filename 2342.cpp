#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <stdbool.h>
using namespace std;
// 函数结果状态代码
#define TRUE 		1
#define FALSE 		0
#define OK 			1
#define ERROR 		0
#define INFEASIBLE 	-1
#define OVERFLOW 	-2

// 定义数据类型 
typedef int STATUS;

// 定义数据结构体
typedef struct {
	int elem;	
} ElemType; 

// 单链表结构:静态定义
typedef struct LNode {
	ElemType data;
	struct LNode* next;
} LNode, *LinkList;

// 循环链表的特点是无须增加存储量，仅对表的链接方式稍作改变，即可使得表处理更加方便灵活。
// 【例】在链表上实现将两个线性表（a1，a2，…，an）和（b1，b2，…，bm）连接成一个线性表（a1，…，an，b1，…bm）的运算。
// 分析：若在单链表或头指针表示的单循环表上做这种链接操作，都需要遍历第一个链表，找到结点an，然后将结点b1链到an的后面，其执行时间是O(n)。
// 若在尾指针表示的单循环链表上实现，则只需修改指针，无须遍历，其执行时间是O(1)。
// 相应的算法如下：

LinkList Connect(LinkList A,LinkList B)
{//假设A，B为非空循环链表的尾指针
	LinkList p=A->next;//①保存A表的头结点位置
	A->next=B->next->next;//②B表的开始结点链接到A表尾
	free(B->next);//③释放B表的头结点
	B->next=p;//④
	return B;//返回新循环链表的尾指针
} 
// 注意：
// ①循环链表中没有NULL指针。涉及遍历操作时，其终止条件就不再是像非循环链表那样判别p或p->next是否为空，而是判别它们是否等于某一指定指针，如头指针或尾指针等。
// ②在单链表中，从一已知结点出发，只能访问到该结点及其后续结点，无法找到该结点之前的其它结点。而在单循环链表中，从任一结点出发都可访问到表中所有结点，
// 这一优点使某些运算在单循环链表上易于实现。

/* 设立尾指针的单循环链表的12个基本操作 */
void InitList(LinkList *L) {
	/* 操作结果：构造一个空的线性表L */
	*L=(LinkList)malloc(sizeof(struct LNode));
	/* 产生头结点，并使L指向此头结点 */
	if(!*L) /* 存储分配失败 */
		exit(OVERFLOW);
	(*L)->next=*L;
	/* 指针域指向头结点 */
}

void DestroyList(LinkList *L) {
	/* 操作结果：销毁线性表L */
	LinkList q,p=(*L)->next;
	/* p指向头结点 */
	while(p!=*L) { /* 没到表尾 */
		q=p->next;
		free(p);
		p=q;
	}
	free(*L);
	*L=NULL;
}
void ClearList(LinkList *L)	/* 改变L */
{
	/* 初始条件：线性表L已存在。操作结果：将L重置为空表 */
	LinkList p,q;
	*L=(*L)->next;
	/* L指向头结点 */
	p=(*L)->next;
	/* p指向第一个结点 */
	while(p!=*L){
		/* 没到表尾 */
		q=p->next;
		free(p);
		p=q;
	}
	(*L)->next=*L;
	/* 头结点指针域指向自身 */
}

STATUS ListEmpty(LinkList L) {
	/* 初始条件：线性表L已存在。操作结果：若L为空表，则返回TRUE，否则返回FALSE */
	if(L->next==L)	/* 空 */
		return TRUE;
	else
		return FALSE;
}

int ListLength(LinkList L) {
	/* 初始条件：L已存在。操作结果：返回L中数据元素个数 */
	int i=0;
	LinkList p=L->next;
	/* p指向头结点 */
	while(p!=L)
	{	/* 没到表尾 */
		i++;
		p=p->next;
	}
	return i;
}

STATUS GetElem(LinkList L,int i,ElemType *e) {
	/* 当第i个元素存在时，其值赋给e并返回OK，否则返回ERROR */
	int j=1;
	/* 初始化，j为计数器 */
	LinkList p=L->next->next;
	/* p指向第一个结点 */
	if(i<=0||i>ListLength(L))
	/* 第i个元素不存在 */
	return ERROR;
	while(j< i) {
		/* 顺指针向后查找，直到p指向第i个元素 */
		p=p->next;
		j++;
	}
	*e=p->data; /* 取第i个元素 */ return OK;
}

int LocateElem(LinkList L,ElemType e, STATUS(*compare)(ElemType,ElemType)) {
	/* 初始条件：线性表L已存在，compare()是数据元素判定函数 */ 
	/* 操作结果：返回L中第1个与e满足关系compare()的数据元素的位序。*/ 
	/* 若这样的数据元素不存在，则返回值为0 */ 
	int i=0;
	LinkList p=L->next->next; /* p指向第一个结点 */ 
	while(p!=L->next) {
		i++;
		if(compare(p->data,e)) /* 满足关系 */
		return i;
		p=p->next;
	}
	return 0;
}

STATUS PriorElem(LinkList L,ElemType cur_e,ElemType *pre_e) {
	/* 初始条件：线性表L已存在 */ 
	/* 操作结果：若cur_e是L的数据元素，且不是第一个，则用pre_e返回它的前驱，*/ 
	/* 否则操作失败，pre_e无定义 */ 
	LinkList q,p=L->next->next; /* p指向第一个结点 */ 
	q=p->next;
	while(q!=L->next) { /* p没到表尾 */
		if(q->data.elem == cur_e.elem) {
			*pre_e=p->data;
			return TRUE;
		}
		p=q;
		q=q->next;
	}
	return FALSE; /* 操作失败 */
}
STATUS NextElem(LinkList L,ElemType cur_e,ElemType *next_e) {
	/* 初始条件：线性表L已存在 */ 
	/* 操作结果：若cur_e是L的数据元素，且不是最后一个，则用next_e返回它的后继，*/ 
	/* 否则操作失败，next_e无定义 */ 
	LinkList p=L->next->next; /* p指向第一个结点 */ 
	while(p!=L) { /* p没到表尾 */
		if( p->data.elem == cur_e.elem) {
			*next_e=p->next->data;
			return TRUE;
		}
		p=p->next;
	}
	return FALSE; /* 操作失败 */
}

STATUS ListInsert(LinkList *L,int i,ElemType e) { /* 改变L */
	/* 在L的第i个位置之前插入元素e */ 
	LinkList p=(*L)->next,s; /* p指向头结点 */ 
	int j=0;
	if(i<=0||i>ListLength(*L)+1) /* 无法在第i个元素之前插入 */
	return ERROR;
	while(j< i-1) { /* 寻找第i-1个结点 */
		p=p->next;
		j++;
	}
	s=(LinkList)malloc(sizeof(struct LNode)); /* 生成新结点 */ 
	s->data=e; /* 插入L中 */ 
	s->next=p->next;
	p->next=s;
	if(p==*L) /* 改变尾结点 */
		*L=s;
	return OK;
}
STATUS ListDelete(LinkList *L,int i,ElemType *e) { /* 改变L */
	/* 删除L的第i个元素，并由e返回其值 */ 
	LinkList p=(*L)->next,q; /* p指向头结点 */ 
	int j=0;
	if(i<=0||i>ListLength(*L)) /* 第i个元素不存在 */
	return ERROR;
	while(j< i-1) { /* 寻找第i-1个结点 */
		p=p->next;
		j++;
	}
	q=p->next; /* q指向待删除结点 */ 
	p->next=q->next;
	*e=q->data;
	if(*L==q) /* 删除的是表尾元素 */
		*L=p;
	free(q); /* 释放待删除结点 */ return OK;
}
void ListTraverse(LinkList L,void(*vi)(ElemType)) {
	/* 初始条件：L已存在。操作结果：依次对L的每个数据元素调用函数vi() */ 
	LinkList p=L->next->next; /* p指向首元结点 */ 
	while(p!=L->next) { /* p不指向头结点 */
		vi(p->data);
		p=p->next;
	}
	printf("\n");
}

