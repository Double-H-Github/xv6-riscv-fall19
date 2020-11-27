#include "kernel/types.h"
#include "user/user.h"

int main( int argn, char *argv[]){
	if(argn != 2){
		fprintf(2,"请输入睡眠时间\n");
		exit();
	}
	int sleepNum = atoi(argv[1]);
	printf("sleep %d\n", sleepNum);
	sleep(sleepNum);
	exit();
}
