#include "types.h"
#include "user.h"

int factors(int n){
	for(int i = 1; i < n/2 + 1; i++){
		if(n % i == 0){
			printf(1, "%d ", i);
		}
	}
	printf(1, "\n");
	return 0;
}


int main(){

	if(factors(1643838401) == 0){
		exit();
	}

	exit();
}