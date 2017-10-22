#include <stdio.h>
#include <pthread.h>

#include <unistd.h>

void processParent( );
void processChild( );

void * processParentworker(void *arg);

int main(int argc, const char *argv[])
{

	int pid;

	pid = fork( );

	if(pid != 0)	// fork return child pid in parent process
		processParent( );
	else		// fork return 0 in child process
		processChild( );

	return 0;
}

void processParent( )
{
	pid_t pid = getpid();
	char prefix[] = "ProcessParent: ";
	//char tprefix[] = "thread ";
	int tstatus;
	pthread_t pt;

	printf("%s%d %s\n", prefix, pid, "step1");

	tstatus = pthread_create(&pt, NULL, processParentworker, NULL);
	if(tstatus != 0)
	{
		printf("ProcessParent: Can not create new thread.");
	}

	processParentworker(NULL);
	sleep(1);
}

void * processParentworker(void *arg)
{
	pid_t pid = getpid( );
	pthread_t tid = pthread_self( );
	char prefix[] = "ProcessParentThread: ";
	char tprefix[] = "thread ";

	printf("%s%d %s%ld %s\n", prefix, pid, tprefix, tid, "step2");
	printf("%s%d %s%ld %s\n", prefix, pid, tprefix, tid, "step3");

	return NULL;
}

void processChild( )
{
	pid_t pid = getpid( );
	char prefix[] = "ProcessChild: ";
	printf("%s%d %s\n", prefix, pid, "step1");
	printf("%s%d %s\n", prefix, pid, "step2");
	printf("%s%d %s\n", prefix, pid, "step3");
}
