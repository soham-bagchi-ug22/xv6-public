#include "types.h"
#include "user.h"

int factors(uint n){
	for(uint i = 1; i < n/2 + 1; i++){
		if(n % i == 0){
			printf(1, "%d ", i);
		}
	}
	printf(1, "\n");
	return 0;
}

int foreverLoop(uint x, uint y){
	uint n = 1;
	while(n % x != 0 && n % y != 0){
		n++;
	}
	//printf(1, "%d x %d = %d\n", x, y, n);
	return n;
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
						printf(1, "you've reached the toddler process\n");
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