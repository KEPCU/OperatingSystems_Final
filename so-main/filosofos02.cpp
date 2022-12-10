#include<stdio.h>

void filosofo (char *arg);

int main(void)
{
	char filo01[20] = "Sócrates";
	char filo02[20] = "Pitágoras";

	filosofo(filo01);
	filosofo(filo02);

	return 0;
}

void filosofo (char *arg) 
{
	for (int i=1; true; i++) {
		printf ("%s estoy comiendo : %d \n", arg, i);
	}
}
