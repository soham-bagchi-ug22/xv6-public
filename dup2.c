#include "types.h"
#include "user.h"

int main(int argc, char *argv[]){
	// using these as args
	int f_1 = 1, f_2 = 8;
	int newfd;
	if((newfd = dup2(f_1, f_2)) < 0){
		printf(2, "dup2 failed lol\n");
		exit();
	}

	printf(1, "dup2 success! newfd: %d\n", newfd);
	exit();
}