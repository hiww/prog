/*********
 * Heap Sort
 *******/
 
#include <stdio.h>
#define LEFT(i) (2 * i)
#define RIGHT(i) (2 * i + 1)
#define N 10
void HEAPSORT(int*, int);
void MAX_HEAPIFY(int*, int, int);
void BUILD_MAX_HEAP(int*, int);

int main(void) {
	int i, j, n = N, temp, A[] = {4,1,3,2,16,9,10,14,8,7};
	for (i = 0; i < N - 1; i++) {
		HEAPSORT(A, n);
		n--;
		temp = A[0];
		A[0] = A[n];
		A[n] = temp;
	}
	for (j = 0; j < N; j++) {
		printf("%d ", A[j]);
	}
	printf("\n");
	return 0;
}

void HEAPSORT(int A[], int n) {
	int i;
	BUILD_MAX_HEAP(A, n);
	for (i = n; i > 0; i--) {
		MAX_HEAPIFY(A, i, n);
	}
}

void MAX_HEAPIFY(int A[], int i, int n) {
	int l = LEFT(i), r = RIGHT(i), largest, temp;
	if (l <= n && A[l - 1] > A[i - 1]) {
		largest = l;
	} else {
		largest = i;
	}
	if (r <= n && A[r - 1] > A[largest - 1]) {
		largest = r;
	}
	if (largest != i) {
		temp = A[i - 1];
		A[i - 1] = A[largest - 1];
		A[largest - 1] = temp;
		MAX_HEAPIFY(A, largest, n);
	}
}

void BUILD_MAX_HEAP(int A[], int n){
	int i;
	for (i = n / 2; i > 0; i--) {
		MAX_HEAPIFY(A, i, n);
	}
}
