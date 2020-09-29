#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    int processID = fork();
    if(processID > 0){
	while(wait(NULL) > 0){
		
	}
	printf("In PARENT: successfully waited child(pid=%i)\n", processID);
    } else {
	printf("IN CHILD: pid=%i\n", getpid());
	execlp("ls", "ls", "-l", "-a");
    } 
    return 0;
}
