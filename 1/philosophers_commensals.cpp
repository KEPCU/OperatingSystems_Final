#include <stdio.h>
#include <pthread.h>
#include <thread>
#include <iostream>
#include <vector>
#include <chrono>
#include <random>

using namespace std;
#define REPETICIONES 3
#define NUM_FILOSOFOS 10
int Noodles = 100000;
vector<bool> forks;

void *Think(void *arg);

int Random(int Min, int Max) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(Min,Max); 
    return dist6(rng);
}

class Philosopher {
	private:
		int Stomach;
		int Id;
	public:
		pthread_t t;

		int GetStomach() {
			return Stomach;
		}
		
		void Eat() {
			int upperLimit = Id + 1;
			if(Id == forks.size() - 1) upperLimit = 0;
			
			if(forks[Id] && forks[upperLimit]) {
				forks[Id] = forks[upperLimit] = false;
				printf("Philosopher-%d, picking up left fork (%d) \n", Id, upperLimit);
				printf("Philosopher-%d, picking up right fork (%d) \n", Id, Id);

				int meal = Random(50,100);
				Noodles -= meal;

				int prevStomach = Stomach;
				Stomach += meal;

				int time = Random(1000,2000);
				printf("Philosopher-%d, I am eating (%d) \n", Id, time);

				printf("Philosopher-%d, Stomach (%d + %d = %d)\n", Id, prevStomach,meal, Stomach );
				this_thread::sleep_for(std::chrono::milliseconds(time));
				
				forks[Id] = forks[upperLimit] = true;
			}
			else {
				printf("Philosopher-%d, waiting.....\n", Id);
				while (!forks[Id] && !forks[upperLimit]);
				Eat();
			}
		}

		Philosopher(int id) {
			Id = id;
			Stomach = 0;
		}
};

Philosopher* Philosophers[NUM_FILOSOFOS];
int IDs[NUM_FILOSOFOS];

int main(void) {
	int number = 0;
	cout<<"input number of philosophers: ";
	cin>>number;
	
	printf("Noodles = %d \n", Noodles);

	int i;
	int result;

	for (i = 0; i < number && i < NUM_FILOSOFOS; i++)	{
		Philosophers[i] = new Philosopher(i);
		IDs[i] = i;
		forks.push_back(true);
		pthread_create(&(Philosophers[i]->t), NULL, &Think, &IDs[i]);
	}

	for (i = 0; i < number && i < NUM_FILOSOFOS; i++) {
		pthread_join(Philosophers[i]->t, NULL);	
	}

	int stomachs = 0;
	for (int j = 0; j < number; j++) {
		stomachs += (*Philosophers[j]).GetStomach();
		printf("Philosopher-%d, Stomach = %d\n", j, (*Philosophers[j]).GetStomach());
	}

	printf("Philosophers Stomachs = %d\n", stomachs);
	printf("Noodles = %d \n", Noodles);

	return 0;
}

void *Think(void *arg) {
	int id = *((int *)arg);
	printf("ID = %d \n",id);
	int count = 0;
	for(int i = 0; i < REPETICIONES; i++) {
		int time = Random(1000,2000);
		printf("Philosopher-%d, I am thinking (%d) \n", id, time);

		this_thread::sleep_for(std::chrono::milliseconds(time));

		printf("Philosopher-%d, I am hungry \n", id);
		(*Philosophers[id]).Eat();
	}
}