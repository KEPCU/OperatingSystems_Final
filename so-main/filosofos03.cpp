#include<stdio.h>
#include<pthread.h>

// gcc filosofos03.cpp -pthread

void *filosofo (void *arg);

int main(void)
{
	char filo01[20] = "Sócrates";
	char filo02[20] = "Pitágoras";

	pthread_t socrates, pitagoras;

	pthread_create (&socrates, NULL, &filosofo, &filo01);
	pthread_create (&pitagoras, NULL, &filosofo, &filo02);

	pthread_join(socrates, NULL);
	pthread_join(pitagoras, NULL);

	return 0;
}

void *filosofo (void *arg) 
{
	char *arg2 = (char *)arg;
	for (int i=1; true; i++) {
		printf ("%s estoy comiendo : %d \n", arg2, i);
	}
}
