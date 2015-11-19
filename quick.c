#include <stdio.h>

void swap(int* i, int* j) {
	int k;
	k = *i;
	*i = *j;
	*j = k;
}
void QuickSort(int data[], int left, int right) {
	int x = left, y = right;
	int base = data[(left + right) / 2];
	while (1) {
		while (data[x] < base) {
			x++;
		}
		while (data[y] > base) {
			y--;
		}
		/* 重なるとbreak */
		if (x >= y) {
			break;
		}
		/* 見つけた値の入れ替え */
		swap(&data[x], &data[y]);
		x++;
		y--;
	}
	/* 左右の要素がまだ分割可能ならソート */
	if (left < x - 1) {
		QuickSort(data, left, x - 1);
	}
	if (right > y + 1) {
		QuickSort(data, y + 1, right);
	}
}
int main (void) {
	int i, n, A[] = {1, 30, 2, 11, 3, 5, 12, 0, 4, 6};
	/* 配列の長さを求める */
	n = sizeof(A) / sizeof(int);
	/* クイックソートをする */
	QuickSort(A, 0, n);	
	/* 結果の表示をする */
	for (i = 0; i < n; i++) {
		printf("%d ", A[i]);
	}
	printf("\n");
	return 0;
}
