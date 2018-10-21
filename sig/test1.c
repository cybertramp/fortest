#include <signal.h> 
#include <unistd.h> 

void sig_handler(int signo); // 비프음 발생 함수

int main()
{
	int i = 0;
	signal(SIGINT,SIG_DFL);

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
	printf("#\n");
}
