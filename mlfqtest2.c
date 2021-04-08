#include "types.h"
#include "user.h"
#include "fcntl.h"

char buf[8192];

int factors(uint n){
	for(uint i = 1; i < n/2 + 1; i++){
		if(n % i == 0){
			printf(1, "%d ", i);
		}
	}
	printf(1, "\n");
	return 0;
}


// TAKEN FROM USERTESTS.C PLEASE DON'T MIND THANKS
int foreverLoop(uint x, uint y){
	int fd = open("testfile1_sb", O_CREATE|O_RDWR);
	if(fd >= 0){
		printf(1, "open success\n");	
	}
	else{
		printf(1, "open fail\n");
		exit();
	}
	for(int i = 0; i < 1000; i++){
		if(write(fd, "aaaaaaaaaa", 10) != 10){
			printf(1, "write error\n");
		}
	}
	close(fd);
	return 5;
}

int main(){

	int startTime = uptime();

	int rc = fork();
	if(rc < 0)
		printf(1, "fork error\n");
	
	else if(rc == 0){
		int rc1 = fork();
		if(rc1 < 0)
			printf(1, "fork error\n");
		else if(rc1 == 0){
			int rc2 = fork();
			if(rc2 < 0)
				printf(1, "fork error\n");
			else if(rc2 == 0){
				int rc3 = fork();
				if(rc3 < 0)
					printf(1, "fork error\n");
				else if(rc3 == 0){
					int rc4 = fork();
					if(rc4 < 0)
						printf(1, "fork error\n");
					else if(rc4 == 0){
						printf(1, "you've reached the toddler process (pid:%d)\n", (int) getpid());
					}
		
					else{
						printf(1, "(pid:%d) (child:%d) n = %d\n", (int) getpid(), rc4, foreverLoop(24007, 21323)); // 511901261 = 24007 * 21323
					}

				}
		
				else{
					printf(1, "(pid:%d) (child:%d) n = %d\n", (int) getpid(), rc3, foreverLoop(12073, 28979)); // 349863467 = 12073 * 28979
				}

			}
		
			else{
				printf(1, "(pid:%d) (child:%d) n = %d\n", (int) getpid(), rc2, foreverLoop(24571, 16087)); // 395273677 = 24571 * 16087
			}

		}
		
		else{
			printf(1, "(pid:%d) (child:%d) n = %d\n", (int) getpid(), rc1, foreverLoop(10667, 28163)); // 300414721 = 10667 * 28163
		}

	}
	
	else{
		printf(1, "(pid:%d) (child:%d) n = %d\n", (int) getpid(), rc, foreverLoop(21647, 19687)); // 426164489 = 21647 * 19687
	}
	
	int endTime = uptime();

	printf(1, "TOTAL TIME: %d\n", endTime - startTime);

	exit();
}