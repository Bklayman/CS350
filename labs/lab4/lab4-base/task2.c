#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char * argv[]) {
    int processID = fork();
    if(processID > 0){
	while(wait(NULL) > 0){

	}
	printf("In PARENT: successfully waited child (pid=%i)\n", processID);
    } else {
	printf("IN CHILD: pid=%i\n", getpid());
	execvp(argv[1], argv + 1);
    }
    return 0;
}
