/* 쓰레드 생성 예제 */
#include <pthread.h>	// for thread programming
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// 쓰레드 함수
void *t_function(void *data)
{
	int id;
	int i = 0;
	id = *((int *)data);
	
	int count = 0;
	//while(1)
	while(count < 10)
	{
		printf("%d : %d\n", id, i);
		i++;
		count++;
		sleep(1);
	}
}

int main()
{
	pthread_t p_thread[2];
	int thr_id;
	int status;
	int a = 1;
	int b = 2;

	// 쓰레드 생성 아규먼트로 1 을 넘긴다.  
	thr_id = pthread_create(&p_thread[0], NULL, t_function, (void *)&a);
	if (thr_id < 0)
	{
		perror("thread create error : ");
		exit(0);
	}

	// 쓰레드 생성 아규먼트로 2 를 넘긴다. 
	thr_id = pthread_create(&p_thread[1], NULL, t_function, (void *)&b);
	if (thr_id < 0)
	{
		perror("thread create error : ");
		exit(0);
	}

	// 쓰레드 종료를 기다린다. 
	pthread_join(p_thread[0], (void **)&status);
	printf("exit 1 thread!\n");
	pthread_join(p_thread[1], (void **)&status);
	printf("exit 2 thread!\n");
	
	printf("exit master thread!\n");
	return 0;
}
