#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

/*
fork-----pfd[1]----->wait(null)		 // 부모
ㄴ-------pfd[0]-->			// 자식
*/

int main(void){
	int pfd[2];
	char buf[30];

	/* create pipe */
	if(pipe(pfd) == -1){	// -1인 경우 pipe 에러
		perror("pipe error");
		exit(1);
	}
	/* Create child */
	if(!fork()){		// pid에 해당하는 자식이 생성됨
		printf("CHILD(PID: %d): Writing to the pipe\n",getpid());

		write(pfd[1], "pipe!",5);	// pfd[1]에 "pipe!" 전달

		exit(0);
	}
	/* for parent */
	else{			// 부모
		printf("PARENT(PID: %d): Reading from the pipe\n",getpid());

		read(pfd[0],buf,5);	// pfd[0] 값을 받아 buf에 저장
		printf("PARENT(PID : %d): %s\n",getpid(),buf);

		wait(NULL);	// 기다림
	}
	return 0;
}


