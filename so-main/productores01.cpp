#include<stdio.h>
#include<thread>
#include<stdlib.h>

using namespace std;

// g++ productores01.cpp -lpthread

#define NUM_PRODUCTORES 2

const char letras[26]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

void productor (int k);

int main(void)
{
	thread productores[NUM_PRODUCTORES];
	int identificadores[NUM_PRODUCTORES];

	int i;

	for (i=0; i<NUM_PRODUCTORES; i++)	{
		
		productores[i] = thread(productor, i);
	}


	for (i=0; i<NUM_PRODUCTORES; i++)	{
		productores[i].join();
	}

	return 0;
}

void productor (int k) 
{	
	int aleatorio;
	for (int i=1; true; i++) {
		aleatorio = rand() % 26;
		printf ("(%d) Productor-%d estoy produciendo : %c \n", i, k, letras[aleatorio]);
	}
}
