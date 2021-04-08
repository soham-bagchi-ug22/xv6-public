#include "types.h"
#include "user.h"


int main (int argc, char *argv[]){
	printf(1, "hello world (pid:%d (%d))\n", (int) getpid(), (int) getpriority(getpid()));
	int rc = fork();
	if(rc < 0)
		printf(1, "fork error\n");
	else if(rc == 0){
		int pd = (int) getpid();
		printf(1, "child (pid:%d) (priority:%d)\n", (int) getpid(), (int) getpriority(getpid()));
		int xc;
		for(int i = 0; i < 30; i++){
			xc = fork();
			if(xc == 0){
				printf(1, "grandchild (parent:%d) (pid:%d) (priority:%d)\n", pd, (int) getpid(), (int) getpriority(getpid()));
				for(int j = 0; j < 10; j++){
					printf(1, "%d:%d:%d -> %d\n", pd, (int) getpid(), (int) getpriority(getpid()), j);
				}
				exit();
			}
		}
	}
	else{
		printf(1, "parent (child:%d) (pid:%d) (priority:%d)\n", rc, (int) getpid(), (int) getpriority(getpid()));
		for(int i = 31; i < 60; i++){
			printf(1, "%d:%d:%d -> %d\n", (int) getpid(), rc, (int) getpriority(getpid()), i);
		}
	}
	exit();
}