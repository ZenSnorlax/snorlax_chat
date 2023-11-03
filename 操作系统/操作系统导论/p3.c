#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int arg, char *argv[]){
	printf("hello world (pid: %d)\n", (int) getpid());
	int rc = fork();
	if(rc < 0){ //fork failed; exit
	fprintf(stderr, "fork failed\n");
	}else if(rc == 0){ //child (new process)
	printf("hello, I am child (pid: %d)\n", (int)getpid());
	char *myargs[3];
	}
}

