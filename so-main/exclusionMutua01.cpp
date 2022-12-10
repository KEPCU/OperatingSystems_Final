#include<stdio.h>
#include<pthread.h>
#include<assert.h>
// gcc exclusionMutua01.cpp -pthread

#define NUM_FILOSOFOS 5

void *filosofo (void *arg);

int variable = 0;
int tope = 5;

int main(void)
{

	pthread_t filosofos[NUM_FILOSOFOS];
	int identificadores[NUM_FILOSOFOS];

	int i;
	int result;

	printf ("Ingrese tope : ");
	scanf ("%d", &tope);

	printf ("variable = %d\n",variable);

	for (i=0; i<NUM_FILOSOFOS; i++)	{
		identificadores[i] = i;
		result = pthread_create (&filosofos[i], NULL, &filosofo, &identificadores[i]);
		assert(!result);
	}

	for (i=0; i<NUM_FILOSOFOS; i++)	{
		result = pthread_join(filosofos[i], NULL);
		assert(!result);
	}
	
	printf ("variable = %d\n",variable);

	return 0;
}

void *filosofo (void *arg) 
{
	int arg2 = *((int *)arg);
	for (int i=1; i<=tope; i++) {
		variable = variable + 1;
		//printf ("Filósofo-%d estoy comiendo : %d. variable = %d \n", arg2, i, variable);
	}
	return NULL;
}

