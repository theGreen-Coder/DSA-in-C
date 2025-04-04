#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

typedef struct node node_t;

typedef struct node
{
	int key;
	node_t* next;
};



// Generate linked lists
int* generate_random_linked_list(int length);

// General Constants (PLAY WITH THESE NUMBERS)
int const N = 100;
int MAX_NUM = 150;
// int PRINT_ARRAYS = 0;

int main(void){

	node_t* head = generate_random_linked_list(5);

	return 0;
}

int* generate_random_linked_list(int length){
	node_t last_node;
	node_t next_node;

	node_t* head = &last_node;

	srand ( time(NULL) );	

	for(int i=0; i < length; i++){
		last_node.key = rand() % MAX_NUM;

		node_t next_node;
		next_node.key = 0;
		last_node.next = &next_node;

		last_node = next_node;
		last_node.next = NULL;
	}

	return head;
}