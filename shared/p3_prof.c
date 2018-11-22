/* code from joinc.co.kr */

#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <string.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 

#define  KEY     77350

int main(void)
{
	int shmid;
	int pid;

	int *cal_num;

	void *shm_addr = (void *)0;

	struct shmid_ds   shm_info;


	// 공유메모리 공간을 만든다.
	shmid = shmget((key_t)KEY, sizeof(int), 0666|IPC_CREAT);

	if (shmid == -1) {
		perror("shmget failed : ");
		exit(0);
	}

	// 공유메모리를 사용하기 위해 프로세스를 메모리에 붙인다. 
	shm_addr = shmat(shmid, (void *)0, 0);

	if (shm_addr == (void *)-1)
	{
		perror("shmat failed : ");
		exit(0);
	}

	cal_num = (int *)shm_addr;

	pid = fork();

	if (pid == 0)
	{
		int i = 0;

		shmid = shmget((key_t)KEY, sizeof(int), 0);
		if (shmid == -1)
		{
			perror("shmget failed : ");
			exit(0);
		}

		shm_addr = shmat(shmid, (void *)0, 0666|IPC_CREAT);
		if (shm_addr == (void *)-1)
		{
			perror("shmat failed : ");
			exit(0);
		}

		cal_num = (int *)shm_addr;

		*cal_num = 1; // 여기서 자식 프로세스가 공유메모리에 값을 처음으로 삽입한다 

		// get the status of the shm
		if ( -1 == shmctl( shmid, IPC_STAT, &shm_info))
		{
			printf( "공유 메모리 정보 구하기에 실패했습니다.\n");
			return -1;
		}

		printf( "ch(pid: %d): no. of process attached: %ld\n", getpid(), shm_info.shm_nattch);

		for(i = 0; i < 20; i++) {
			{
				*cal_num = *cal_num + 1; // 공유메모리에 값을 삽입 
				printf("ch(pid: %d): %d\n", getpid(), *cal_num); 
				sleep(1);
			}
		}

		if ( -1 == shmdt(shm_addr)) {
			printf( "공유 메모리 분리 실패\n");
			return -1;
		}
		else {
			printf( "공유 메모리 분리\n");
		}

		exit(0);

	}

	// 부모 프로세스 공유메모리의 내용을 보여준다. 
	else if(pid > 0)
	{
	
		while(1)
		{
			sleep(1);
			printf("pa(pid: %d): %d\n", getpid(), *cal_num);

			// get the status of the shm
			if ( -1 == shmctl( shmid, IPC_STAT, &shm_info))
			{
				printf( "공유 메모리 정보 구하기에 실패했습니다.\n");
				return -1;
			}

			printf("pa(pid): %d): no. of process attached: %ld\n", getpid(), shm_info.shm_nattch);
		}
	}
}
