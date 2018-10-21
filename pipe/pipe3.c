#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

/* 표준 입력(stdin) = 0 */
/* 표준 출력(stdout) = 1 */
/* 표준 에러(stderr) = 2 */

int main(void){
	int pfd[2];

	/* create pipe */
	if(pipe(pfd) == -1){
		perror("pipe error");
		exit(1);
	}
	/* Create child */
	if(!fork()){
		close(1);	// 표준 출력 닫기
		dup(pfd[1]);	// 표준 출력을 파이프 입력으로 연결
		close(pfd[0]);

		execlp("ls","ls",NULL);		// 표준 출력으로 나와야 하지만 파이프의 입력으로 들어감
	}
	else{
		close(0);	// 표준 입력 닫기
		dup(pfd[0]);	// 표준 입력을 파이프의 출력으로 연결
		close(pfd[1]);

		execlp("wc","wc","-l",NULL);	// 파이프의 출력(자식의 ls 한 결과)이 wc의 입력이 
	}

	return 0;
}


