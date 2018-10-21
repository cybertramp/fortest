#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<signal.h>
#include<time.h>

static void sig_usr(int signo){
	if(signo == SIGUSR1)
		printf("SIGUSR1 received from its child\n");
	else if(signo == SIGUSR2)
		printf("SIGUSR2 received from its child\n");
}

int main(void){
	
	if(!fork()){/* Create child */
		int ppid;
		
		ppid = getppid();
		kill(ppid,SIGUSR1);

		exit(0);
	}
	else{	/* parent */
		if(signal(SIGUSR1,sig_usr) == SIG_ERR)
			perror("can't catch SIGUSR1\n");
		if(signal(SIGUSR2,sig_usr) == SIG_ERR)
			perror("can't catch SIGUSR2\n");
		wait(NULL);
	}
	return 0;
}


