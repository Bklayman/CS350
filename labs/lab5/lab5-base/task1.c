#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    char * argv1[] = {"cat", "Makefile", 0};
    //char * argv2[] = {"head", "-4", 0};
    char * argv2[] = {"wc", "-l", 0};
    
    setbuf(stdout, NULL);

    int fd[2];
    if(pipe(fd) != 0){
	printf("Pipe creation error\n");
    }

    int processID = fork();

    if(processID == 0){
	printf("In CHILD-1 (PID=%i): executing command %s ...\n", getpid(), argv1[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	execvp(argv1[0], argv1);
	fprintf(stderr, "Child 1 Failed\n");
	exit(1);
    }
    processID = fork();
    if(processID > 0){
	close(fd[0]);
	close(fd[1]);
	int reapID = wait(NULL);
	while(reapID > 0){
		printf("In PARENT (PID=%i): successfully reaped child (PID=%i)\n", getpid(), reapID);
		reapID = wait(NULL);
	}
    } else {
	printf("In Child-2 (PID=%i): executing command %s ...\n", getpid(), argv2[0]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	close(fd[0]);
	execvp(argv2[0], argv2);
	fprintf(stderr, "Child 2 failed\n");
	exit(1);
    }

    return 0;
}
