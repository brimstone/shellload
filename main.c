#include <stdio.h>

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int child() {
	int c, len = 0;
	int codesize = 4096;
	char* shellcode = malloc(codesize * sizeof(char));
	char* resizer;
	while (scanf("%2x", &c) == 1) {
		shellcode[len] = c;
		len++;
		if ( len >= codesize) {
			codesize += 4096;
			resizer = realloc(shellcode, codesize * sizeof(char));
			shellcode = resizer;
		}
	}
	shellcode[len] = 0;
	resizer = realloc(shellcode, len * sizeof(char));
	shellcode = resizer;
	if (len == 0) {
		printf("No shellcode\n");
		return 0;
	}
	(*(int(*)()) shellcode)();
	return 0;
}

int main(int argc, char ** argv) {
	if (argc == 0 || strlen(argv[argc-1]) < 50) {
		return child();
	}

	// handle being called with args
	int fd[2];
	if (pipe(fd) == -1) {
		perror("pipe");
		return 1;
	}
	int cpid;
	if (cpid = fork()) {
		// parent
		close(fd[0]);
		write(fd[1], argv[argc-1], strlen(argv[argc-1]));
		fsync(fd[1]);
		close(fd[1]);
		//wait(NULL);
		return 0;
	}

	// child process
	close(fd[1]);
	char * buf[10];
	close(0);
	if (dup(fd[0]) == -1) {
		perror("dup");
		return 1;
	}
	close(fd[0]);
	close(fd[1]);
	char * me = argv[0];
	for (int i = 1; i < argc - 1; i++)
		argv[i-1] = argv[i];
	argv[argc - 2] = 0;
	//for (int i = 0; argv[i] != 0; i++)
	//	printf("argv[%d]: %s\n", i, argv[i]);
	execve(me, argv, NULL);
	return 0;
}
