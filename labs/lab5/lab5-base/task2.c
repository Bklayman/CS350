#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    char * argv1[] = {"cat", "Makefile", 0};
    char * argv2[] = {"head", "-4", 0};
    char * argv3[] = {"wc", "-l", 0};

    setbuf(stdout, NULL);

    int fd1[2];
    pipe(fd1);

    int processID = fork();

    if(processID == 0){
	printf("In Child-1 (PID=%i): executing command %s ...\n", getpid(), argv1[0]);
	dup2(fd1[1], 1);
	close(fd1[0]);
	close(fd1[1]);
	execvp(argv1[0], argv1);
	fprintf(stderr, "Child 1 failed\n");
	exit(1);
    }

    int fd2[2];
    pipe(fd2);

    processID = fork();
    if(processID == 0){
	printf("In CHILD-2 (PID=%i): executing command %s ...\n", getpid(), argv2[0]);
	dup2(fd2[1], 1);
	dup2(fd1[0], 0);
	close(fd1[0]);
	close(fd1[1]);
	close(fd2[0]);
	close(fd2[1]);
	execvp(argv2[0], argv2);
	fprintf(stderr, "Child 2 failed\n");
	exit(1);
    }
	
    processID = fork();
    if(processID == 0){
	printf("In CHILD-3 (PID=%i): executing command %s ...\n", getpid(), argv3[0]);
	dup2(fd2[0], 0);
	close(fd1[0]);
	close(fd1[1]);
	close(fd2[0]);
	close(fd2[1]);
	execvp(argv3[0], argv3);
	fprintf(stderr, "Child 3 failed\n");
	exit(1);
    }

    close(fd1[0]);
    close(fd1[1]);
    close(fd2[0]);
    close(fd2[1]);
    int reapID = wait(NULL);
    while(reapID > 0){
	printf("In PARENT (PID=%i): successfully reaped child (PID=%i)\n", getpid(), reapID);
	reapID = wait(NULL);
    }

    return 0;
}
