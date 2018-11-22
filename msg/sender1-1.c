////////////////////////// main_sender.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define  BUFF_SIZE   1024

typedef struct {
	long  data_type;
	int   data_num;
	char  data_buff[BUFF_SIZE];
} t_data;

int main( void)
{
	int      msqid;     // key로 할당 받은 id
	int      ndx   = 0;
	t_data   data;
	if(-1 == (msqid = msgget((key_t)4547, IPC_CREAT | 0600))){
		perror( "msgget() 실패");
		exit(1);
	}
	printf("success create msqid!\n");
	while(1)
	{
		data.data_type = ( ndx++ % 3) +1;   // data_type 1,2,3
		data.data_num  = ndx;
		sprintf( data.data_buff, "type=%d, ndx=%d", data.data_type, ndx);

		// msgsnd 파라미터 id, data 구조체, userdata 크기,옵션 0
		if ( -1 == msgsnd( msqid, &data, sizeof( t_data) - sizeof( long), 0))
		{
			perror( "msgsnd() error or msg queue is full");
			exit( 1);
		}

		printf("sender: %d - %s\n",data.data_num, data.data_buff);
		sleep(1);
	}
	return 0;
}
