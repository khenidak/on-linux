#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


// code is based on man page example: https://man7.org/linux/man-pages/man2/pipe.2.html

int
main(int argc, char *argv[])
{
	int pipefd[2];
	pid_t cpid;
	char buf;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <string>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if (pipe(pipefd) == -1) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	printf("parent pid:%d\n", getpid());
	cpid = fork();
	if (cpid == -1) {
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (cpid == 0) {    /* Child reads from pipe */
		printf("child forked to pid:%d\n", getpid());
		close(pipefd[1]);          /* Close unused write end */

		while (read(pipefd[0], &buf, 1) > 0)
			write(STDOUT_FILENO, &buf, 1);

			write(STDOUT_FILENO, "\n", 1);

			printf("child CLOSING pid:%d\n", getpid());
			close(pipefd[0]);
			_exit(EXIT_SUCCESS);

		} else {            /* Parent writes argv[1] to pipe */
			close(pipefd[0]);          /* Close unused read end */
			write(pipefd[1], argv[1], strlen(argv[1]));
			close(pipefd[1]);          /* Reader will see EOF */
			wait(NULL);                /* Wait for child DO NOT CREATE ZOMBIE https://man7.org/linux/man-pages/man2/wait.2.html */
			printf("parent CLOSING pid:%d\n", getpid());
			exit(EXIT_SUCCESS);
	}
}
