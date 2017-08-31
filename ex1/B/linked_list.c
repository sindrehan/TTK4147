#include <stdlib.h>
#include <stdio.h>
#include "linked_list.h"

list_t list_create()
{
    list_t new_list = (list_t) malloc(sizeof(struct list));
    new_list->head = NULL;
    new_list->tail = NULL;
    new_list->length = 0;
    return new_list; 
}

void list_delete(list_t list)
{
    struct node* current_node = list-> head;
    while (current_node != NULL){
	struct node* temp = current_node;
	current_node = current_node->next;
	free(temp);
    }
    free(list);
}

void list_insert(list_t list, int index, int data)
{
    struct node* new_node = (struct node*) malloc(sizeof(struct node));
    if (list->length == 0){
	list->head = new_node;
	list->tail = new_node;
	new_node->prev = NULL;
	new_node->next = NULL;
    } else if (list->length <= index) {
	new_node->next = NULL;
	list->tail->next = new_node;
	new_node->prev = list->tail;
	list->tail = new_node;
    } else if (index == 0) {
	new_node->prev = NULL;
	new_node->next = list->head;
	list->head = new_node;
    } else {
	struct node* current_node = list->head;
	for (int i = 0; i < index; i++) {
	    current_node = current_node->next;
	}

	current_node->prev->next = new_node;
	new_node->prev = current_node->prev;
	current_node->prev = new_node;
	new_node->next = current_node;
    }
    new_node->data = data;
    list->length++;
}

void list_append(list_t list, int data)
{
    list_insert(list, list->length, data);
}

void list_print(list_t list)
{
    struct node* current_node;
    for (current_node = list->head; current_node != NULL; current_node = current_node->next) {
	printf("%i ", current_node->data);
    }
    printf("\n");
}

long list_sum(list_t list)
{
    long sum = 0;
    for (struct node* i = list->head; i != NULL; i=i->next) {
	sum += (long) i->data;
    }
    return sum;
}

int list_get(list_t list, int index)
{
    struct node* cur_node = list->head;
    for (int i = 0; i < index; i++) {
	cur_node = cur_node->next;
    }
    return cur_node->data;
    
}

int list_extract(list_t list, int index)
{
    int data;
    if (list->length == 0){
	return -1;
    } else if (list->length <= index) {
	data = list->tail->data;
	struct node* temp = list->tail;
	list->tail = list->tail->prev;
	free(temp);
    } else if (index == 0){
	data = list->head->data;
	struct node* temp = list->head;
	list->head = list->head->next;
	free(temp);
    } else {
	struct node* cur_node = list->head;
	for (int i = 0; i < index; i++) {
	    cur_node = cur_node->next;
	}

	data = cur_node->data;
	cur_node->prev->next = cur_node->next;
	cur_node->next->prev = cur_node->prev;
	free(cur_node);
    }
    list->length--;
    return data;
}
