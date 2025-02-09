#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int* generate_random_numbers(int length);

void bubble_sort(int* numbers, int length);
void insertion_sort(int* numbers, int length);
void selection_sort(int* numbers, int length);
void shell_sort(int* numbers, int length);
int* merge_sort(int* numbers, int length);
int* quick_sort(int* numbers, int length);
void heap_sort(int* numbers, int length);

void print_numbers(int* numbers, int length);

int n = 20;

int main(void){

	int* numbers = generate_random_numbers(n);
	print_numbers(numbers, n);

	quick_sort(numbers, n);

	print_numbers(numbers, n);

	free(numbers);
	numbers = NULL;

	return 0;
}

int* generate_random_numbers(int length) {
	int* numbers = malloc(sizeof(int)*length);

	srand ( time(NULL) );

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

void swap(int* a, int* b){
	int tmp = *a;
	*a = *b;
	*b = tmp;
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

void insertion_sort(int* numbers, int length){
	int j = 0, tmp = 0, key = 0;

	for(int i = 1; i<length; i++){
		key = numbers[i];

		j = i-1;

		while(j >= 0 && numbers[j] > key){
			// print_numbers(numbers, n);
			numbers[j+1] = numbers[j];
			j--;
		}

		numbers[j+1] = key;
	}
}

void selection_sort(int* numbers, int length){
	int min = 0, tmp = 0;

	for(int i = 0; i < length; i++){
		min = i;

		for(int j = i; j < length; j++){
			if(numbers[min] > numbers[j]){
				min = j;
			}
		}

		tmp = numbers[i];
		numbers[i] = numbers[min];
		numbers[min] = tmp;
	}
}

void shell_sort(int* numbers, int length){
	int tmp = 0, key = 0, j = 0;
	
	for(int gap = length/2; gap > 0; gap /= 2){
		for(int i = gap; i < length; i++){
			key = numbers[i];

			j = i;

			while(j >= gap && numbers[j-gap] > key){
				// print_numbers(numbers, n);
				numbers[j] = numbers[j-gap];
				j -= gap;
			}

			numbers[j] = key;
		}
	}
}

int* merge_sort(int* numbers, int length){
	if(length==1){
		return numbers;
	}

	int mid = (length)/2;

	int* left = merge_sort(&numbers[0], mid);
	int* right = merge_sort(&numbers[mid], length-mid);

	int i = 0, j = 0;

	int* tmp = malloc(sizeof(int)*length);

	while(i < mid && j < (length-mid)){
		if(left[i] < right[j]){
			tmp[i+j] = left[i];
			i++;
		}
		else{
			tmp[i+j] = right[j];
			j++;
		}
	}

	while(i < mid){
		tmp[i+j] = left[i];
		i++;
	}

	while(j < (length-mid)){
		tmp[i+j] = right[j];
		j++;
	}

	memcpy(numbers, tmp, length*sizeof(numbers[0]));

	free(tmp);
	tmp = NULL;

	return numbers;
}

int* quick_sort(int* numbers, int length){
	if(length >= 2){
		int pivot = numbers[length-1];
		int i = -1;
	
		for(int j = 0; j < length-1; j++){
			if(numbers[j] < pivot){
				i++;
				swap(&numbers[i], &numbers[j]);
			}
		}
		swap(&numbers[i+1], &numbers[length-1]);

		quick_sort(numbers, i+1);
		quick_sort(&numbers[i+2], length-i-2);
		
	}
}