#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int* generate_random_numbers(int length);

void bubble_sort(int* numbers, int length);
void insertion_sort(int* numbers, int length);
void selection_sort(int* numbers, int length);
void shell_sort(int* numbers, int length);
void merge_sort(int* numbers, int length);
void quick_sort(int* numbers, int length);
void heap_sort(int* numbers, int length);

void print_numbers(int* numbers, int length);

int n = 20;

int main(void){

	int* numbers = generate_random_numbers(n);
	print_numbers(numbers, n);

	bubble_sort(numbers, n);

	print_numbers(numbers, n);

	free(numbers);
	numbers = NULL;

	return 0;
}

int* generate_random_numbers(int length) {
	int* numbers = malloc(sizeof(int)*length);

	if(numbers == NULL){
		return NULL;
	}
	else{
		for(int i = 0; i < length; i++){
			numbers[i] = rand() % 100;
		}
		return numbers;
	}
}

void print_numbers(int* numbers, int length){
	printf("[");

	for(int i = 0; i < length; i++){
		printf("%d", numbers[i]);
		if(i < length - 1){
			printf(", ");
		}
	}
	
	printf("]\n");
}

void bubble_sort(int* numbers, int length){
	int tmp = 0;

	for(int i=length-1; i >= 0; i--){
		for(int j=1; j <= i; j++){
			if(numbers[j-1] >= numbers[j]){
				tmp = numbers[j];
				numbers[j] = numbers[j-1];
				numbers[j-1] = tmp;
			}
		}
	}
}

