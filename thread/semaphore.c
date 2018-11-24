/* ex1.c */

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int cnt = 0; // 공유되는 전역 변수
static int  semid; // 세마포어 아이디 

// 세마포어 설정 함수, 크리티칼 섹션에 들어 가기 전에 설정하는 함수!
void p() {
	struct sembuf pbuf;

	pbuf.sem_num   = 0;
	pbuf.sem_op    = -1;
	pbuf.sem_flg   = SEM_UNDO;

	if ( -1 == semop(semid, &pbuf, 1))
		printf( "p()-semop() 실행 오류\n");
}

// 세마포어 해제 함수, 크리티칼 섹션에서 나올때 사용하는 함수!
void v() {
	struct sembuf vbuf;

	vbuf.sem_num   = 0;
	vbuf.sem_op    = 1;
	vbuf.sem_flg   = SEM_UNDO;

	if ( -1 == semop( semid, &vbuf, 1))
		printf( "v()-semop() 실행 오류\n");
}

// 쓰레드 함수1
void *fun_thread1(void *arg) {
	int randtime = 0;

	while(cnt < 5) {
		p();

		printf("thread1 실행\n");
		cnt++;

		randtime = rand() % 5 + 1;
		sleep(randtime);

		printf("thread1 종료\n");

		v();
	}
	return NULL;
}

// 쓰레드 함수2
void *fun_thread2(void *arg) {
	int randtime = 0;

	while(cnt < 5) {
		p();

		printf("thread2 실행\n");
		printf("thread2 카운터 = %d\n", cnt);

		randtime = rand() % 5 + 1;
		sleep(randtime);

		printf("thread2 종료\n");

		v();
	}
	return NULL;
}

// 쓰레드 함수3
void *fun_thread3(void *arg) {
	int randtime = 0;

	while(cnt < 5) {
		p();

		printf("thread3 실행\n");
		printf("thread3 카운터 = %d\n", cnt);

		randtime = rand() % 5 + 1;
		sleep(randtime);

		printf("thread3 종료\n");

		v();
	}
	return NULL;
}


int main(int argc, char *argv[]) {
	pthread_t thread1;
	pthread_t thread2;
	pthread_t thread3;

	union semun {
		int                  val;
		struct   semid_ds   *buf;
		unsigned short int  *arrary;
	}  arg;

	if ( -1 == (semid = semget(IPC_PRIVATE, 1, IPC_CREAT | 0666))) {
		printf( "semget() 실행 오류\n");
		return -1;
	}

	arg.val  =  1;  // 세마포어 값을 1로 설정

	if ( -1 == semctl(semid, 0, SETVAL, arg)) {
		printf( "semctl()-SETVAL 실행 오류\n");
		return -1;
	}

	pthread_create(&thread1, NULL, fun_thread1, NULL);
	pthread_create(&thread2, NULL, fun_thread2, NULL);
	pthread_create(&thread3, NULL, fun_thread3, NULL);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);

	if ( -1 == semctl(semid, 0, IPC_RMID, arg)) {
		printf( "semctl()-IPC_RMID 실행 오류\n");
		return -1;
	}

	printf("\n프로그램 종료\n");

	return 0;
}
