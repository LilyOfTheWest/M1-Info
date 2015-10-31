#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv) {
	int i;
	int n;

	if (argc != 2) {
		printf("usage: %s n\n", argv[0]);
		return -1;
	}

	n = atoi(argv[1]);

	srand(time(NULL));

	printf("%d\n", n);
	for(i=0; i < n; i++) {
		printf("%d\n", i/*(rand()%(n*2))*/);
	}

	return 1;
}