#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

int main() {
	printf("main is at %p\n", main);
	printf("end of data is at:%p\n", sbrk(0));

	void *all;
	char string[4];
	int *somewhereInTheMiddle;


	printf("we allocated stack vars and end of data is at:%p\n", sbrk(0));
	printf("data is at:%p\n", sbrk(0));


	printf("waiting\n");
	printf("allocating 1 GB\n");
	all = malloc(1024 * 1024 * 1024);
	if (all == NULL) perror("failed to allocate 1gb");

	printf("waiting while you check the memory ..\n");
	scanf("%1s", string);

	// let us set a mem somewhere in the middle
	printf("touch the content in the middle page \n");
	somewhereInTheMiddle = (int *) all  + (1024 * 1024 );
	*somewhereInTheMiddle =  ~0;

	printf("waiting while you check the memory ..\n");
	scanf("%1s", string);


	printf("set all \n");
	memset(all, ~0, 1024 * 1024 * 1024);

	printf("waiting while you check the memory ..\n");
	scanf("%1s", string);

	free(all);
	return 0;
}
