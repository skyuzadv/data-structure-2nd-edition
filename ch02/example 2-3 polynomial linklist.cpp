//**********************************************************
//********************2.8 案例分析与实现******************** 
// 解决目标：一元多项式运算 
// 主要运算：加法 减法 乘法
// 主要特点：递增、递减、唯一 
// 储存方式：链表(链式储存) 
// 编译配置：-std=c++11
//**********************************************************
#define _CRT_SECURE_NO_WARNINGS// vs2017 use scanf() can't warnings
#include<iostream>
#include<cstdio>
#define COMPARE >

// 0.1 数据结构 
typedef struct ElemType {
	float 	coef;	// 系数 
	int 	expn;	// 指数
} ElemType;

// 0.2 链式表 
typedef struct PNode {
	ElemType elem;
	struct PNode *next;
} PNode, *Polynomial;

//**********************************************************
// 函数声明开始
void CreatePolyno_H(Polynomial&, int);
void CreatePolyno_R(Polynomial&, int);
void ShowPolyno(Polynomial&);
void AddPolyno(Polynomial&, Polynomial&);
void SubPolyno(Polynomial&, Polynomial&);
void MulPolyno(Polynomial&, Polynomial&);
// 函数声明结束 
//**********************************************************

int main(void) {
	Polynomial Pa, Pb;
	// Pa polynomial 
	int i = 6, j = 6;
	printf("Pa多项式赋值%d对:\n", i);
	CreatePolyno_R(Pa, i);
	printf("Pa: \n");
	ShowPolyno(Pa);

	// Pb polynomial
	printf("Pb多项式赋值%d对:\n", j);
	CreatePolyno_R(Pb, j);
	printf("Pb: \n");
	ShowPolyno(Pb);

	// add polynomial
	/*
	AddPolyno(Pa, Pb);
	printf("add res: \n");
	ShowPolyno(Pa);
	*/

	// sub polynomial
	/*
	SubPolyno(Pa, Pb);
	printf("sub res：\n");
	ShowPolyno(Pa);
	*/
	printf("mul res: \n");
	MulPolyno(Pa, Pb);
	// exit main
	exit(0);
}
// create polynomial 
// 正序法
void CreatePolyno_R(Polynomial &PList, int n) {
	PList = new PNode;
	PList->next = NULL;
	PNode *prior, *q, *s;
	for (int i = 1; i <= n; i++) {
		s = new PNode;
		scanf("%f%d", &s->elem.coef, &s->elem.expn);
		prior = PList;
		q = PList->next;// q = NULL
		/*
		| 1> q = null 结束循环
		| 2> if (q->elem.expn >= s->elem.expn) 结束循环
		| 3> 每次for循环后，从头结点开始比较
		| 4> 当头结点expn > 插入结点s.expn
		| 5> 直至找到q.expn >= s.enpn 位置找到
		*/
		while (q && q->elem.expn < s->elem.expn) {// 正序 
			prior = q;
			q = q->next;
		}
		s->next = q;
		prior->next = s;
	}
}
// create polynomial 
// 逆序法
void CreatePolyno_H(Polynomial &PList, int n) {
	PList = new PNode;
	PList->next = NULL;
	PNode *pre, *q, *s;
	for (int i = 1; i <= n; i++) {
		s = new PNode;
		scanf("%f%d", &s->elem.coef, &s->elem.expn);
		pre = PList;
		q = PList->next;// q = NULL
		while (q && q->elem.expn > s->elem.expn) {// 逆序 
			pre = q;
			q = q->next;
		}
		s->next = q;
		pre->next = s;
	}
}

// show polynomial
void ShowPolyno(Polynomial &P) {
	PNode *q = P->next;
	if (!q) {
		printf("P is null \n");
		return;
	}
	int flag = 0;
	while (q) {
		if (flag) printf(" + "), flag = 0;
		printf("%1.fX^%d", q->elem.coef, q->elem.expn);
		q = q->next;
		flag = 1;
	}
	printf("\n");// finish result end with charge line
	return;
}

// add polynomial
void AddPolyno(Polynomial& Pa, Polynomial& Pb) {
	// Pa' = Pa + Pb 
	Polynomial p1, p2, p3, r;
	auto coef = Pa->elem.coef;
	p1 = Pa->next;
	p2 = Pb->next;
	p3 = Pa;
	while (p1 && p2) {
		if (p1->elem.expn == p2->elem.expn) {
			coef = p1->elem.coef + p2->elem.coef;
			if (coef == 0) {// result is 0，move ponit:p1, p2 
				r = p1; p1 = p1->next; delete r;	// delete p1 node 
				r = p2; p2 = p2->next; delete r;	// delete p2 node 
			}
			else {
				p1->elem.coef = coef;				// merge coef
				p3->next = p1; p3 = p1;				// 尾插法 
				p1 = p1->next;
				r = p2; p2 = p2->next; delete r;	// delete p2 node
			}
		}
		else if (p1->elem.expn < p2->elem.expn) {
			p3->next = p1;
			p3 = p1;
			p1 = p1->next;
		}
		else {
			p3->next = p2;
			p3 = p2;
			p2 = p2->next;
		}
	}
	p3->next = p1 ? p1 : p2;						// 拷贝剩余项
	delete Pb;										// delete Pb polynomial
}
// sub polynomial 
void SubPolyno(Polynomial& Pa, Polynomial& Pb) {
	PNode *p = Pb->next;
	if (!p) return;
	while (p) {
		p->elem.coef *= -1;
		p = p->next;
	}
	AddPolyno(Pa, Pb);
}
// mul polynomial
void MulPolyno(Polynomial& Pa, Polynomial& Pb) {
	Polynomial Pc = new PNode; Pc->next = NULL;
	PNode* s, *r;
	for (PNode* p = Pa->next; p; p = p->next)
		for (PNode* q = Pb->next; q; q = q->next) {
			s = new PNode;
			s->elem.coef = p->elem.coef * q->elem.coef;
			s->elem.expn = p->elem.expn + q->elem.expn;
			s->next = Pc->next;
			Pc->next = s;
		}
	PNode *p, *q, *prior;
	p = Pc->next;
	ShowPolyno(Pc);
	/*
	| 表合并
	*/
	for (; p->next; p = p->next) {
		q = p->next;
		prior = p;
		while (q->next) {// merge polynomial	
			if (p->elem.expn == q->elem.expn) {
				p->elem.coef += q->elem.coef;
				prior->next = q->next;
				r = q; q = q->next; delete r;	// delete r node
			}
			else {
				prior = prior->next;			// 快慢指针法 
				q = q->next;
			}
		}
	}
	printf("merge res: \n");
	ShowPolyno(Pc);
	/*
	| 有序表 * 有序表 = 局部有序表，然后合并
	| 对合并表排序操作
	*/
	Polynomial Pd = new PNode; Pd->next = NULL;
	PNode *max, *fast, *slow, *tail;
	bool flag;	// flag bits ：max node = first node
	for (tail = Pd, prior = NULL; p = Pc->next; ) {
		prior = Pc;
		fast = Pc->next->next;
		slow = Pc->next, flag = 1;		// flag into first node
		max = slow;
		while (fast) { 					// 逆序排列(也可改大于号即为升序排序) 
			if (max->elem.expn < fast->elem.expn) flag = 0, prior = slow, max = fast;
			slow = fast;				// 快慢指针法 
			fast = fast->next;
		}
		if (flag) Pc->next = max->next;	// max node 等于头结点
		else {
			// max node 等于其他结点
			prior->next = max->next;
		}
		max->next = NULL; tail->next = max; tail = max;// 尾插法
	}
	printf("sort res: \n");
	ShowPolyno(Pd);

	printf("Pc res: \n");
	ShowPolyno(Pc);
}

