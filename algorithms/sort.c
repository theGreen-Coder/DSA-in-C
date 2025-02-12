#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

// Generate numbers functions
int* generate_random_numbers(int length);
void print_numbers(int* numbers, int length);
void print_results(int* numbers, int* copy_numbers, double time_taken, const char *algo_name);

// Helper Functions
void benchmark_sort(void (*sort_func)(int*, int), int *numbers, int *copy_numbers, int n, const char *sort_name);
void digit_counting_sort(int* numbers, int digit, int length);
int is_sorted(int* numbers, int* copy_numbers, int length);
int get_digit(int num, int digit);
int count_digits(int num);

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
void radix_sort(int* numbers, int length);

// General Constants (PLAY WITH THESE NUMBERS)
int const N = 9999;
int MAX_NUM = 1000000;
int PRINT_ARRAYS = 0;


int main(void){
	int* numbers = generate_random_numbers(N);
	int* copy_numbers = malloc(sizeof(int)*N);
	clock_t start, end;

	if(PRINT_ARRAYS){
		printf("Array to sort: \n");
		print_numbers(numbers, N);
		printf("\n");
	}
	
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
		{radix_sort, "Raidx Sort"},
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

void print_results(int* numbers, int* copy_numbers, double time_taken, const char *algo_name){
	int sorted_flag = is_sorted(numbers, copy_numbers, N);
	
	printf("%s", algo_name);
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

int compare_ints(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int is_sorted(int* numbers, int* copy_numbers, int length) {
	int* sorted_numbers = malloc(length * sizeof(int));
	if (!sorted_numbers) return 0;

	for (int i = 0; i < length; i++) {
		sorted_numbers[i] = copy_numbers[i];
	}

	qsort(sorted_numbers, length, sizeof(int), compare_ints);

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
	if(PRINT_ARRAYS){
		print_numbers(numbers, N);
	}
	
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
	// I'm cheating here a little bit, cause I know what the MAX_NUM will be
	int max_num = MAX_NUM;

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

int get_digit(int num, int digit){
	int i = digit + 1;
	int result = 0;

	for(int j = 0; j<i; j++){
		result = num % 10;
		num /= 10;
	}

	return result;
}

void digit_counting_sort(int* numbers, int digit, int length){
	int max_num = 10;

	int* b = malloc(sizeof(int) * length);
	int* c = malloc(sizeof(int) * (max_num));

	for(int i=0; i<length; i++){
		c[get_digit(numbers[i], digit)]++;
	}

	for(int i=1; i<max_num; i++){
		c[i] += c[i-1]; 
	}

	for(int i=length-1; i >= 0; i--){
		b[c[get_digit(numbers[i], digit)]-1] = numbers[i];
		c[get_digit(numbers[i], digit)]--;
	}

	memcpy(numbers, b, length*sizeof(numbers[0]));

	free(b);
	b = NULL;
	free(c);
	c = NULL;
}

int count_digits(int num){
	if(num==0){
		return 1;
	}
	return (int)log10(num) + 1;
}

void radix_sort(int* numbers, int length){
	int max_digits = count_digits(MAX_NUM-1);

	for(int i = 0; i < max_digits; i++){
		digit_counting_sort(numbers, i, length);
	}
}