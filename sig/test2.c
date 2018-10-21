#include <signal.h> 
#include <unistd.h> 

void sig_handler(int signo); // 비프음 발생 함수

int main()
{
	sigaction *act
	int i = 0;
	printf("Program start\n");
	sigaction(SIGUSR1, sig_handler, NULL);
	
	
	while(1)
	{
		printf("%d\n", i);
		i++;
		sleep(1);
	}
	return 1;
}


void sig_handler(int signo)
{
	sleep(10);
}

