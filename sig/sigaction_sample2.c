#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void signalHandler(int signo);

main() 
{ 
	struct sigaction act;

	/* 시그널이 오면 signalHandler 실행 */
	act.sa_handler = signalHandler;

	/* act.sa_mask : 시그널 처리하는 동안 블록 시킬 시그널 
		sigfillset => 모두                                 */
	sigfillset(&act.sa_mask);
	
	/* 옵션을 설정하지 않음 */
	act.sa_flags = 0;

	/* SIGINT가 오는 경우 act 행동*/
	sigaction(SIGINT, &act, NULL);
	
	while(1)
		sleep(5);
}

/* 핸들러 정의 */
void signalHandler(int signo)
{
	printf("start handler\n");
	sleep(3);
	printf("end handler\n");
}

