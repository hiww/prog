#include<stdio.h>
#define N 10

void BUILD_TREE(int n) {
  int i;
  Build_MAX_HEAP(n);
  for(i = n; i < 0; i--) {
    MAX_HEAPIY(i, n);
  }
}
void MAX_HEAPIFY(int i, int n) {
  int r, l, largest;
  l = LEFT(i);
  r = RIGHT(i);
  if(l <= n && A[l] > A[i]) {
        largest = l;
    } else {
        largest = i;
  }
    if(r <=n && A[r] > A[largest]) {
        largest = r;
    }
    if(largest != i) {
        int temp = A[i];
        A[i] = A[largest];
    A[largest] = temp;
    MAX_HEAPIFY(largest, n);
  }
}
void BUILD_MAX_HEAP(int n) {
  int i;
  for(i = n / 2; i != 0; i--) {
    MAX_HEAPIFY(i, n);
  }
}
int main(void){
    int i, j, n, N, temp;
    int A[N] = {4,9,3,11,87,7,5,1,12,23};
        for(i = 0; i < N - 1; i++) {
            BUILD_TREE(n);
            n--;
            temp = A[0];
            A[0] = A[n];
            A[n] = temp;
        }
  for(j = 0; j < N; j++) {
    printf("%d ",A[j]);
  }
  printf("\n");
  return 0;
}
