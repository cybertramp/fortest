/* 

   [Named Pipe]
   표준 입 출력 대신 파일을 통해 구현 

 */

#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>

#define FIFO_NAME "FIFO_FD"

int main(void){
	char buf[100];
	int num,fd;
	
	/* FIFO 에 사용할 파일 지시자 생성 */
	if(mknod(FIFO_NAME,S_IFIFO | 0666,0) == -1){
		perror("mknod error");
	}
	
	/* FIFO 를 통해 데이터 전송 받을 상대 측 프로세스를 기다림 */
	/* 상대 측 프로세스가 FIFO 파일 지시자를 열면, 우리도 연다.*/
	printf("Writer: waiting for a reader.\n");
	fd = open(FIFO_NAME, O_WRONLY);		// O_WRONLY => 쓰기전용
	
	printf("Writer: the reader ready.\n");
	printf("Writer: your input: ");
	
	/* 사용자로 부터 입력 받은 데이터를 FIFO를 통해 상대 측에게 전달 */
	while(fgets(buf,sizeof(buf),stdin),!feof(stdin)){		//feof() : 스트림 상태 리셋 및 확인
		if((num = write(fd,buf,strlen(buf))) == -1)
			perror("wirte error");
		else
			printf("Writer: wrote %d bytes\n",num);
	}
	return 0;
	
}
