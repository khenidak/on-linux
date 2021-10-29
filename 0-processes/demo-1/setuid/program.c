#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main( void )
{
	uid_t ruid, euid, suid;

	printf( "my userid is %d\n", getuid() );

	if (getresuid(&ruid, &euid, &suid) < 0)
		perror("failed to get real user id");


	printf( "my effective userid is %d\n", euid );

	return EXIT_SUCCESS;
}
