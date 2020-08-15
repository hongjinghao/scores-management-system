#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dingyi.h"

#define TYPE student

// 设计链表的节点
typedef struct Node
{
	TYPE data; 			// 节点的数据域
	struct Node* next;  // 节点的指针域
}Node;

// 创建节点
Node* create_node(TYPE data)
{
	// 分配节点所需要的内存
	Node* node = malloc(sizeof(Node));
	node->data = data;
	node->next = NULL;
	return node;
}

// 头添加
void add_head_list(Node* head,TYPE val)
{
	Node* node = create_node(val);
	node->next = head->next;
	head->next = node;
}

// 尾添加
void add_tail_list(Node* head,TYPE val)
{
	// 创建一个新节点
	Node* node = create_node(val);

	// 找到最后一个节点
	Node* n = head;
	while(NULL!=n->next) n = n->next;

	// 最后一个节点指向新的节点
	n->next = node;
}

// 按位置删除
bool del_index_list(Node* head,int index)
{
	// 上到待删除的上一个节点
	Node* n = head;
	for(int i=0; i<index; i++)
	{
		n=n->next;
		if(NULL == n->next) return false;
	}

	// 备份待删除的节点
	Node* temp = n->next;
	n->next = temp->next;
	free(temp);
	return true;
}

// 按值删除
bool del_value_list(Node* head,TYPE val)
{
	Node* n = head;
	while(NULL != n->next)
	{
		if(val == n->next->data)
		{
			Node* temp = n->next;
			n->next = temp->next;
			free(temp);
			return true;
		}
		n = n->next;
	}
	return false;
}

// 插入
bool inster_list(Node* head,int index,TYPE val)
{
	Node* n = head;
	for(int i=0; i<index; i++)
	{
		n = n->next;
		if(NULL == n->next) return false;
	}
	Node* node = create_node(val);
	node->next = n->next;
	n->next = node;
	return true;
}

// 修改
bool modify_list(Node* head,TYPE old,TYPE val)
{
	for(Node* n=head->next; NULL!=n; n=n->next)
	{
		if(old == n->data)
		{
			n->data = val;
			return true;
		}
	}
	return false;
}

// 访问

bool access_list(Node* head,int index,TYPE* val)
{
	Node* n = head->next;
	for(int i=0; i<index; i++)
	{
		n = n->next;
		if(NULL == n) return false;
	}

	*val = n->data;
	return true;
}

// 排序
void sort_list(Node* head)
{
	for(Node* i=head->next; NULL!=i->next; i=i->next)
	{
		for(Node* j=i->next; NULL!=j; j=j->next)
		{
			if(i->data > j->data)
			{
				TYPE temp = i->data;
				i->data = j->data;
				j->data = temp;
			}
		}
	}
}

// 查询
int query_list(Node* head,TYPE key)
{
	Node* n = head->next;
	for(int i=0; n!=NULL; i++)
	{
		if(key == n->data)
			return i;
		n = n->next;
	}

	return -1;
}

// 遍历
void show_list(Node* head)
{
	for(Node* n=head->next; NULL!=n; n=n->next)
	{
		printf("%d ",n->data);
	}
	printf("\n");
}
