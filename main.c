/**
 * Inter process programm :
 * Parent ignores SIGINT signal (CTRL + C) and waits until his child is killed
 * Child executes bash script with exec(), and ends after exec() as usual
 *
 * Run "make exec", "make", "make clean", and "./prog"
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>


int main(void){
	pid_t p_id = getpid();	
	int rv = fork();

	if(rv == -1){ // error
		perror(NULL);
		return 1;
	}

	else if (!rv){ // child
		pid_t c_id = getpid();
		printf("%d : I'm the child !\n",c_id);
		char mcewd[1024];
		memset(mcewd,'\0',sizeof(mcewd));
		getcwd(mcewd,sizeof(mcewd));
		strcat(mcewd,"/exe");
		execvp(mcewd,NULL);
		printf("IT IS NOT PRINTED, cause exec made the process die\n");

	}

	else{ // parent
		printf("%d : I'm the parent !\n",p_id);
		struct sigaction s_sig;
		s_sig.sa_handler = SIG_IGN;
		sigaction(SIGINT,&s_sig,NULL);
		wait(NULL);
		printf("\r%d : Son stopped :/\n",p_id);
	}

	printf("%d : Who is here ? \n",getpid());
	return 0;
}
