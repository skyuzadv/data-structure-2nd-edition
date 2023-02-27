//**********************************************************
//********************2.8 案例分析与实现******************** 
// 解决目标：图书馆信息管理系统
// 项目标题：LIMS Library information management system
// 主要功能：查找、插入、删除、修改、排序、计数 
// 储存方式：链表(链式储存)、顺序表 
// 编译配置：-std=c++11
//**********************************************************

#include<iostream>
#include<cstdio>
#include<cstdlib>
#define MAXS 200
struct Book{
	char id[20];		// ISBN
	char name[50];		// 书名 
	float price;		// 定价 
};

// 0.1 顺序表 
typedef struct {
	Book *elem;
	int length;
} SqList;

// 0.2 链式表 
typedef struct LNode {
	Book data;
	struct LNode *next;
} LNode, *LinkList; 


int main(void) {
	
	exit(0);
}
