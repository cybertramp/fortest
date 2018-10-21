#include <stdio.h>
#include <signal.h>
#include <unistd.h>

main() 
{ 
	struct sigaction act;

	/* 시그널이 오면 무시 
		SIG_IGN : 무시하겠다. */
	act.sa_handler = SIG_IGN;

	/* act.sa_mask : 시그널 처리하는 동안 블록 시킬 시그널 
	    sigempty() => 아무것도*/
	sigemptyset(&act.sa_mask);
	
	/* 옵션을 설정하지 않음 */
	act.sa_flags = 0;
	
	/* SIGINT가 오는 경우 act 행동*/
	sigaction(SIGINT, &act, NULL);

	while(1) { 
		printf("Hello World\n"); 
		sleep(1); 
	} 
}

