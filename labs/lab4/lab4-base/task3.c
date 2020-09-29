#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define INPUT_FILE "./input/if1"

int main(int argc, char * argv[]) {
    int processID = fork();
    if(processID > 0){
	while(wait(NULL) > 0){
		
	}
	printf("In PARENT: successfully waited child (pid=%i)\n", processID);
    } else {
	printf("In CHILD: pid=%i\n", getpid());
	int inputNum = open(INPUT_FILE, O_RDONLY);
	dup2(inputNum, 0);
	int resultNum = open("result.txt", O_RDWR | O_CREAT, 0777);
	dup2(resultNum, 1);
	execvp(argv[1], argv + 1);
    }
    return 0;
}
