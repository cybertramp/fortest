#include <stdio.h>

int main(void){
	// error_modification1
	//int i;
	double i;
	double j;
	// error modification2
	//char *bug = NULL;
	char bug[50];
	for(i=0;i<5;i++){
		j=i/2+i;
		printf("j is %lf \n",j);
	}

	strcpy(bug,"hi");
	printf("bug is %s \n",bug);

	return 0;
}
