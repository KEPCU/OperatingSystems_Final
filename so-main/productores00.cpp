#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

// gcc productores00.cpp -pthread

#define NUM_PRODUCTORES 2

const char letras[26]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

void *productor (void *arg);

int main(void)
{
	pthread_t productores[NUM_PRODUCTORES];
	int identificadores[NUM_PRODUCTORES];

	int i;

	for (i=0; i<NUM_PRODUCTORES; i++)	{
		identificadores[i] = i;
		pthread_create (&productores[i], NULL, &productor, &identificadores[i]);
	}


	for (i=0; i<NUM_PRODUCTORES; i++)	{
		pthread_join(productores[i], NULL);
	}

	return 0;
}

void *productor (void *arg) 
{
	int arg2 = *((int *)arg);
	int aleatorio;
	for (int i=1; true; i++) {
		aleatorio = rand() % 26;
		printf ("(%d) Productor-%d estoy produciendo : %c \n", i, arg2, letras[aleatorio]);
	}
}
