#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/types.h>

// To calculate the difference between two timevals:
//    timeval_subtract(&diff, &end, &start)
// ------
// Subtract the ‘struct timeval’ values X and Y,
// storing the result in RESULT.
// Return 1 if the difference is negative, otherwise 0.
// source: https://www.gnu.org/software/libc/manual/html_node/Elapsed-Time.html
int timeval_subtract (struct timeval *result, struct timeval *x, struct timeval *y)
{
  /* Perform the carry for the later subtraction by updating y. */
  if (x->tv_usec < y->tv_usec) {
    int nsec = (y->tv_usec - x->tv_usec) / 1000000 + 1;
    y->tv_usec -= 1000000 * nsec;
    y->tv_sec += nsec;
  }
  if (x->tv_usec - y->tv_usec > 1000000) {
    int nsec = (x->tv_usec - y->tv_usec) / 1000000;
    y->tv_usec += 1000000 * nsec;
    y->tv_sec -= nsec;
  }

  /* Compute the time remaining to wait.
     tv_usec is certainly positive. */
  result->tv_sec = x->tv_sec - y->tv_sec;
  result->tv_usec = x->tv_usec - y->tv_usec;

  /* Return 1 if result is negative. */
  return x->tv_sec < y->tv_sec;
}

void lab3(int argc, char* argv[]){
	int processID = fork();
	struct timeval current_time;
	if(processID > 0){
		printf("Parent (%i) created child (%i)\n", getpid(), processID);
	} else {
		int retValue = execvp(argv[1], argv + 1);
		if(retValue == -1){
			printf("Command %s does not exist\n", argv[1]);
			exit(1);
		}
	}
	while(wait(NULL) > 0){
		
	}
}

// USE THE FOLLOWING COMMAND TO COMPILE:
//		gcc timer.c -o timer
int main(int argc, char * argv[]) {
  struct timeval start, end, diff;
  
  // TODO: Add you implementation here
  	gettimeofday(&start, NULL);
	lab3(argc, argv);
	gettimeofday(&end, NULL);
	timeval_subtract(&diff, &end, &start);

  // Use the following print statement to output the reslts once you've calcualted the time of execution (i.e., diff)
  printf("Run Time: %ld.%04ld (s)\n", diff.tv_sec, diff.tv_usec/1000);
  
  return 0;
}
