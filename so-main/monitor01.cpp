#include<iostream>
#include<thread>

using namespace std;

// g++ monitor01.cpp -lpthread

#define NUM_HILOS 10

int cont=0;

class Monitor {
	public:
	void inc(){		
		for(int i=0; i<10; i++){
			cont++;
		}		
		//return cont;
	}
};

class Hilo {
	private:
		Monitor* monitor;
		thread t;
		void run_thread(){
			monitor->inc();		//	RUN
			cout<<cont<<endl;	//	RUN
		}
			
	public:
		Hilo(){
			monitor = new Monitor;
			t = thread(&Hilo::run_thread, this);
		}
		void join_thread(){
			t.join();	// START
		}
		
};

int main() {

	Hilo* hilos[NUM_HILOS];
	
	int i;
	for(i=0; i<NUM_HILOS; i++) {
		hilos[i] = new Hilo;
	}
	
	for(i=0; i<NUM_HILOS; i++) {
		hilos[i]->join_thread();	//	START
	}

	return 0;
}







