#include<stdio.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>

//#define	KEY_NUM 7735
#define MEM_SIZE 1024


int main(int argc, char *argv){
	int shm_id;
	void *shm_addr;

	int i;

	//create the shared memory
	if(-1 == (shm_id = shmget((key_t)(int)argv[1], MEM_SIZE, IPC_CREAT|0666))){
		printf("공유 메모리 생성 실패\n");
		return -1;
	}

	// use the shared memory associated with shd_id
	// shm_addr is the base address of the shared memory
	// so we need that address for accessing
	if((void *)-1 == (shm_addr = shmat(shm_id, (void *)0,0))){
		printf("공유 메모리 첨부 실패\n");
		return -1;
	}
	
	for(i=0;i<20;i++){
		printf("shm_id: %d\n",shm_id);
		printf("%s\n",(char *)shm_addr);
		sleep(1);
	}

	if(-1 == shmdt(shm_addr)){
		printf("공유 메모리 분리 실패\n");
		return -1;
	}else{
		printf("공유 메모리 분리\n");
	}

	
	return 0;
}
