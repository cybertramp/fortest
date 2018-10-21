#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void signalHandler(int signo);

main() 
{ 
	struct sigaction act;

	/* 시그널이 오면 signalHandler 실행 */
	act.sa_handler = SIG_IGN;

	/* act.sa_mask : 시그널 처리하는 동안 블록 시킬 시그널 
		sigfillset => 모두                                 */
	//sigfillset(&act.sa_mask);		// fillset을 하면 signal 요소 모두포함
									// emptyset을 하면 signal 요소 X
	sigemptyset(&act.sa_mask);

	/* 옵션을 설정하지 않음 */
	act.sa_flags = 0;

	/* SIGINT가 오는 경우 act 행동*/
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	sigaction(SIGINT, &act, NULL);

	printf("call sigaction\n");

	while(1)
		sleep(5);
}

/* 핸들러 정의 */
void signalHandler(int signo)
{
	printf("start!\n");
	sleep(5);
	printf("end\n");
}

