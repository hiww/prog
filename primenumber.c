#include <stdio.h>
#include <math.h>
int isPrime(unsigned long long int n) {
	unsigned long long int i, max = sqrt(1.5 * ((double)n)); //約数を探す上限
	//素数は1より大きな自然数、つまり1以下は素数でない。
	if (n <= 1) {
		return 0;
	}
	if (n == 2) {
		return 1;
	}
	if (n % 2 == 0) {
		return 0;
	}
	//2以上の数に於いて約数が無いか調べる。
	for (i = 3; i <= max; i += 2) {
		if (n % i == 0) {
			return 0; //割り切れた時、約数が存在する。つまり、素数ではない。
		}
	}
	return 1; //割り切れなければ、約数が無いので素数である。
}
int main(void) {
	unsigned long long int n;
	printf("Input the number\n");
	scanf("%llu", &n);
	if (isPrime(n)) {
		printf("Prime\n");
	} else {
		printf("Not Prime\n");
	}
	return 0;
}
