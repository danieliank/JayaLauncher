#include <stdio.h>

int main(){
	// Cara 1
	int n;
	// n = number
	scanf("%d", &n);
	printf("%d %d", n/10, n%10)

	
	// Cara 2
	char p, s;
	/*
	p = puluhan
	s = satuan
	*/
	scanf("%c%c", &p, &s);
	printf("%c %c", p, s);
	
	return 0;
}
