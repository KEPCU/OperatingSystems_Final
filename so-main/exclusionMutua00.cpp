#include<stdio.h>
#include<pthread.h>

// gcc exclusionMutua00.cpp -pthread

#define NUM_FILOSOFOS 5

void *filosofo (void *arg);

int variable = 0;

int main(void)
{

	pthread_t filosofos[NUM_FILOSOFOS];
	int identificadores[NUM_FILOSOFOS];

	int i;

	printf ("variable = %d\n",variable);

	for (i=0; i<NUM_FILOSOFOS; i++)	{
		identificadores[i] = i;
		pthread_create (&filosofos[i], NULL, &filosofo, &identificadores[i]);
	}


	for (i=0; i<NUM_FILOSOFOS; i++)	{
		pthread_join(filosofos[i], NULL);
	}
	
	printf ("variable = %d\n",variable);

	return 0;
}

void *filosofo (void *arg) 
{
	int arg2 = *((int *)arg);
	for (int i=1; i<=5; i++) {
		variable = variable + 1;
		printf ("Filósofo-%d estoy comiendo : %d. variable = %d \n", arg2, i, variable);
	}
	return NULL;
}
