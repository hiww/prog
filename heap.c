#include <stdio.h>
#define LEFT(i) (2 * i)
#define RIGHT(i) (2 * i + 1)
#define N 10
void Build_Tree(int*, int);
void Max_Heapify(int*, int, int);
void Build_Max_Heap(int*, int);

int main(void) {
	int i, j, n = N, tmp, A[] = {4,1,3,2,16,9,10,14,8,7};
	for (i = 0; i < N - 1; i++) {
		Build_Tree(A, n);
		n--;
		tmp = A[0];
		A[0] = A[n];
		A[n] = tmp;
	}
	for (j = 0; j < N; j++) {
		printf("%d ", A[j]);
	}
	printf("\n");
	return 0;
}

void Build_Tree(int A[], int n) {
	int i;
	Build_Max_Heap(A, n);
	for (i = n; i > 0; i--) {
		Max_Heapify(A, i, n);
	}
}

void Max_Heapify(int A[], int i, int n) {
	int l = LEFT(i), r = RIGHT(i), largest, tmp;
	if (l <= n && A[l - 1] > A[i - 1]) {
		largest = l;
	} else {
		largest = i;
	}
	if (r <= n && A[r - 1] > A[largest - 1]) {
		largest = r;
	}
	if (largest != i) {
		tmp = A[i - 1];
		A[i - 1] = A[largest - 1];
		A[largest - 1] = tmp;
		Max_Heapify(A, largest, n);
	}
}

void Build_Max_Heap(int A[], int n){
	int i;
	for (i = n / 2; i > 0; i--) {
		Max_Heapify(A, i, n);
	}
}
