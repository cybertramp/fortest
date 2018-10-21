#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void sigact_hdlr(int signo, siginfo_t *info, void *uarg)
{
	printf("siginfo si_pid=%d, si_uid=%d\n", info->si_pid, info->si_uid);
	return ;
}

int main()
{
	struct sigaction act;

	act.sa_sigaction = sigact_hdlr;
	act.sa_flags = SA_SIGINFO;
	sigemptyset(&act.sa_mask);

	sigaction(SIGINT, &act, NULL);

	printf("pid: %d\n", getpid());

	while (1) {
		sleep(1);
		printf("wait signal\n");
	}

	return 0;
}
