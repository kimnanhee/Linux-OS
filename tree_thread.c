#include <stdio.h>
#include <pthread.h>

int* thread(void* arg);
int* thread_(void* arg);

int thread_one_state = 0;
int thread_two_state = 0;

int main()
{
	pthread_t tid;

	if(pthread_create(&tid, NULL, thread, "thread one"))
	{
		printf("thread one create fail\n");
		return 0;
	}
	thread_one_state = 1;
	while(thread_one_state);

	return 0;
}
int* thread(void* arg)
{
	printf("%s\n", arg);

	pthread_t ttid;
	if(pthread_create(&ttid, NULL, thread_, "thread two"))
	{
		printf("thread two create fail\n");
		return 0;
	}
	thread_two_state = 1;
	while(thread_two_state);
	thread_one_state = 0;
	
	return 0;
}
int* thread_(void* arg)
{
	printf("%s\n", arg);

	thread_two_state = 0;
	
	return 0;
}
