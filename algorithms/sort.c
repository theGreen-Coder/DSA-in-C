#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

// Generate numbers functions
int* generate_random_numbers(int length);
void print_numbers(int* numbers, int length);
void print_results(int* numbers, int* copy_numbers, double time_taken, char algo_name[]);

// Helper Functions
void benchmark_sort(void (*sort_func)(int*, int), int *numbers, int *copy_numbers, int n, const char *sort_name);
int is_sorted(int* numbers, int* copy_numbers, int length);
int find_max(int* numbers, int length);

// Sorting Algorithms
void bubble_sort(int* numbers, int length);
void insertion_sort(int* numbers, int length);
void selection_sort(int* numbers, int length);
void shell_sort(int* numbers, int length);
void merge_sort(int* numbers, int length);
int* recursive_merge_sort(int* numbers, int length);
void quick_sort(int* numbers, int length);
void heap_sort(int* numbers, int length);
void counting_sort(int* numbers, int length);

// General Constants (PLAY WITH THESE NUMBERS)
int const N = 100;
int MAX_NUM = 100;


int main(void){
	int* numbers = generate_random_numbers(N);
	int* copy_numbers = malloc(sizeof(int)*N);
	clock_t start, end;

	printf("Numbers to sort: \n");
	print_numbers(numbers, N);
	printf("\n");

	memcpy(copy_numbers, numbers, sizeof(int)*N);

	struct {
		void (*sort_func)(int*, int);
		const char *name;
	} sort_algorithms[] = {
		{bubble_sort, "Bubble Sort"},
		{insertion_sort, "Insertion Sort"},
		{selection_sort, "Selection Sort"},
		{shell_sort, "Shell Sort"},
		{merge_sort, "Merge Sort"},
		{quick_sort, "Quick Sort"},
		{heap_sort, "Heap Sort"},
		{counting_sort, "Counting Sort"},
	};

	for (size_t i = 0; i < sizeof(sort_algorithms) / sizeof(sort_algorithms[0]); i++) {
		benchmark_sort(sort_algorithms[i].sort_func, numbers, copy_numbers, N, sort_algorithms[i].name);
	}

	free(numbers);
	numbers = NULL;

	free(copy_numbers);
	copy_numbers = NULL;

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
			numbers[i] = rand() % MAX_NUM;
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

void print_results(int* numbers, int* copy_numbers, double time_taken, char algo_name[]){
	int sorted_flag = is_sorted(numbers, copy_numbers, N);
	
	printf(algo_name);
	if(sorted_flag){
		printf(" Successful ✅! ");
		printf("Time taken: %lf\n", time_taken);
	}
	else{
		printf(" Failed ❌!\n");
	}

}

void swap(int* a, int* b){
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int is_sorted(int* numbers, int* copy_numbers, int length) {
	int* sorted_numbers = malloc(length * sizeof(int));
	if (!sorted_numbers) return 0;

	for (int i = 0; i < length; i++) {
		sorted_numbers[i] = copy_numbers[i];
	}

	qsort(sorted_numbers, length, sizeof(int), (int (*)(const void*, const void*)) strcmp);

	int result = 1;
	for (int i = 0; i < length; i++) {
		if (numbers[i] != sorted_numbers[i]) {
			result = 0;
			break;
		}
	}

	free(sorted_numbers);
	return result;
}

void benchmark_sort(void (*sort_func)(int*, int), int *numbers, int *copy_numbers, int n, const char *sort_name) {
	clock_t start, end;
	start = clock();
	sort_func(numbers, n);
	end = clock();
	print_results(numbers, copy_numbers, ((double)(end - start)) / CLOCKS_PER_SEC, sort_name);
	print_numbers(numbers, N);
	printf("\n");
	memcpy(numbers, copy_numbers, sizeof(int) * n);
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

void merge_sort(int* numbers, int length){
	recursive_merge_sort(numbers, length);
}

int* recursive_merge_sort(int* numbers, int length){
	if(length==1){
		return numbers;
	}

	int mid = (length)/2;

	int* left = recursive_merge_sort(&numbers[0], mid);
	int* right = recursive_merge_sort(&numbers[mid], length-mid);

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

void quick_sort(int* numbers, int length){
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

void max_heapify(int* numbers, int i, int length){
	int left = (2*i)+1;
	int right = (2*i)+2;
	int largest = 0;

	if(left < length && numbers[left] > numbers[i]){
		largest = left;
	}
	else{
		largest = i;
	}

	if(right < length && numbers[right] > numbers[largest]){
		largest = right;
	}

	if(largest != i){
		swap(&numbers[i], &numbers[largest]);
		max_heapify(numbers, largest, length);
	}
}

void heap_sort(int* numbers, int length){
	// Build the heap
	for(int i = (length/2)-1; i >= 0; i--){
		max_heapify(numbers, i, length);
	}

	for(int i = length-1; i >= 1; i--){
		swap(&numbers[0], &numbers[i]);
		length--;
		max_heapify(numbers, 0, length);
	}
}

void counting_sort(int* numbers, int length){
	int max_num = MAX_NUM; //find_max(numbers, length);

	int* b = malloc(sizeof(int) * length);
	int* c = malloc(sizeof(int) * (max_num));

	for(int i=0; i<length; i++){
		c[numbers[i]]++;
	}

	for(int i=1; i<max_num; i++){
		c[i] += c[i-1]; 
	}

	for(int i=length-1; i >= 0; i--){
		b[c[numbers[i]]-1] = numbers[i];
		c[numbers[i]]--;
	}

	memcpy(numbers, b, length*sizeof(numbers[0]));

	free(b);
	b = NULL;
	free(c);
	c = NULL;
}