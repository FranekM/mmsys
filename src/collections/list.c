#include <stdlib.h>
#include <stdio.h>
#include "collections.h"

int add(List list, int a) {
	Node node = malloc(sizeof(node));
	node->next = NULL;
	((Node) list->tail)->value = a;
	((Node) list->tail)->next = node;
	list->tail = node;
	return ++(list->size);
}

int get(List list, int i) {
	Node tmp = list->head;
	while (tmp->next != NULL && --i >= 0)
		tmp = tmp->next;
	return tmp->value;
}

int padd(List list, int *a) {
	pNode node = malloc(sizeof(pnode));
	node->next = NULL;
	((pNode) list->tail)->value = a;
	((pNode) list->tail)->next = node;
	list->tail = node;
	return ++(list->size);
}

int *pget(List list, int i) {
	Node tmp = list->head;
	while (tmp->next != NULL && --i >= 0)
		tmp = tmp->next;
	return (int *) tmp->value;
}

void initList(List list, const char type[]) {
	if (type == "int *") {
		pNode head = malloc(PNODESIZE);
		head->next = NULL;
		list->head = head;
		list->tail = head;	
	} else {
		Node head = malloc(NODESIZE);
		head->next = NULL;
		list->head = head;
		list->tail = head;
	}
	list->size = 0;
}
