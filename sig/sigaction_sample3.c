#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void signalHandler(int signo);

main() 
{ 
	struct sigaction act;
	int k=0;
	/* 시그널 오면 signalHandler를 실행하도록 설정 */
	act.sa_handler = signalHandler;

	sigemptyset(&act.sa_mask);
	/* 시그널을 처리하는 동안에 전달되는 시그널이 블록되지 않도록 하는 옵션 설정 */
	
	act.sa_flags = SA_RESTART;
	//act.sa_flags = 0;
	//act.sa_flags = 0;
	/* SIGINT에 대해 act 행동을 하도록 설정 */

	sigaction(SIGINT, &act, NULL);
	printf("call sigaction\n");
	
	for(;;){
		puts("#@\n");
		sleep(3);
	}
}

void signalHandler(int signo)
{
	printf("start handler\n");
	sleep(10);
	printf("end handler\n");
}

