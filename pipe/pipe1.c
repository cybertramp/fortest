#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>

int main(void){
	int pfd[2];
	char buf[30];

	/* create pipe */
	if(pipe(pfd) == -1){
		perror("pipe error");
		exit(1);
	}

	/* pfd[1] write only */
	printf("Writing to the file descriptor #%d\n",pfd[1]);
	write(pfd[1],"pipe!",5);	// pfd[1]로 "pipe!" 보내버림
	
	/* pfd[2] read only*/
	printf("Reading from the file descriptor #%d\n",pfd[0]);
	read(pfd[0],buf,5);		// pfd[0]를 buf로 읽어옴

	printf("%s\n",buf);

	return 0;
}


