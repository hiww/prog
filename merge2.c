/***********************************
  Merge Sort
  2015. 10. 6
  Miyagawa Shinya
  ************************************/
#include <stdio.h>
#include <stdlib.h>
#define LENGTH 10000
void merge(int A[], int p, int q, int r) {
	int i, j, k, n1, n2, *L, *R;
	n1 = q - p;
	n2 = r - q;
	L = (int*)malloc(sizeof(int)*(n1 + 1));
	R = (int*)malloc(sizeof(int)*(n2 + 1));
	for (i = 0; i <= n1 - 1; i++) {
		L[i] = A[p + i];
	}
	for (j = 0; j <= n2 - 1; j++) {
		R[j] = A[q + j];
	}
	L[n1] = LENGTH;
	R[n2] = LENGTH;
	i = 0, j = 0;
	for (k = p; k <= r - 1; k++) {
		if (L[i] <= R[j]) {
			A[k] = L[i];
			i++;
		} else {
			A[k] = R[j];
			j++;
		}
	}
	free(L);
	free(R);
}
void mergeSort(int A[], int p, int r) {
	int q;
	if (p + 1 < r) {
		q = (p + r) / 2;
		mergeSort(A, p, q);
		mergeSort(A, q, r);
		merge(A, p, q, r);
	}
}
int main(void) {
	int i, n, A[] = {1, 2, 3, 4, 42, 76, 6 , 0, 9, 8, 7, 6, 5};
	/* 配列の長さを求める */
	n = sizeof(A) / sizeof(int);
	/* マージソートをする */
	mergeSort(A, 0, n);
	/* 結果の表示をする */
	for (i = 0; i < n; i++) {
		printf("%d", A[i]);
		if(i < n - 1) {
			printf(" ");
		}
	}
	printf("\n");
	return 0;
}
