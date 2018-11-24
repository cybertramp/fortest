/* ex2.c */
/* http://forum.falinux.com/zbxe/index.php?mid=C_LIB&page=2&document_srl=428639 */
/* 예제에서는 두개의 쓰레드를 만들어 첫번째 쓰레드는 카운터 값을 증가 시키고 두번째 쓰레드는 카운터를 화면에 출력합니다. 카운터가 5 이상의 값이 되면 두 개의 쓰레드는 모두 종료하고 프로그램이 종료되면서 세마포어를 삭제합니다. */

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int         cnt   = 0;
static int  semid;

// 세마포어 설정, 크리티칼 섹션 들어 가기 전 
void p() {
	struct sembuf pbuf;

	pbuf.sem_num   = 0;
	pbuf.sem_op    = -1; // 요거!!!
	pbuf.sem_flg   = SEM_UNDO;

	if ( -1 == semop(semid, &pbuf, 1))
		printf( "p()-semop() 실행 오류\n");
}

// 세마포어 해제, 크리티칼 섹션에서 나오면서 콜하는 함수 
void v() {
	struct sembuf vbuf;

	vbuf.sem_num   = 0;
	vbuf.sem_op    = 1; // 요거!!!
	vbuf.sem_flg   = SEM_UNDO;

	if ( -1 == semop( semid, &vbuf, 1))
		printf( "v()-semop() 실행 오류\n");
}

// 첫번째 쓰레드 함수
void *fun_thread1(void *arg) {
	while(1) {

		// 크리티칼 섹션 시작
		p();

		printf("thread1 실행\n");

		if ( 5 < cnt) {
			printf( "thread1 완전 종료\n");
			v();
			//크리티칼 섹션 끝
			break;
		}
		else {
			cnt++;
			usleep( 100);
			printf( "thread1 완료\n");
		}

		v();
		//크리티칼 섹션 끝

	}
	return NULL;
}

// 두번째 쓰레드 함수 
void *fun_thread2(void *arg) {
	while(1) {

		// 크리티칼 섹션 시작
		p();
		printf("thread2 실행\n");

		if ( 5 < cnt) {
			printf( "thread2 완전 종료\n");
			v();
			//크리티칼 섹션 끝
			break;
		}
		else {
			printf( "thread2 카운터= %d\n", cnt);
			usleep( 100);
			printf( "thread2 완료\n");
		}

		v();
		//크리티칼 섹션 끝
	}
	return NULL;
}

int main(int argc, char *argv[]) {
	pthread_t thread1;
	pthread_t thread2;

	union semun{
		int                  val;
		struct   semid_ds   *buf;
		unsigned short int  *arrary;
	}  arg;

	if ( -1 == (semid = semget( IPC_PRIVATE, 1, IPC_CREAT | 0666))) {
		printf( "semget() 실행 오류\n");
		return -1;
	}

	arg.val  =  1; // 세마포어 값을 1로 설정

	if ( -1 == semctl(semid, 0, SETVAL, arg)) {
		printf( "semctl()-SETVAL 실행 오류\n");
		return -1;
	}

	// 쓰레드 실행 
	pthread_create(&thread1, NULL, fun_thread1, NULL);
	pthread_create(&thread2, NULL, fun_thread2, NULL);

	// 쓰레드 종료하기를 기다림 
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	if ( -1 == semctl(semid, 0, IPC_RMID, arg)) {
		printf( "semctl()-IPC_RMID 실행 오류\n");
		return -1;
	}

	printf("\n프로그램 종료\n");

	return 0;
}
