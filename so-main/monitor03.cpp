#include<iostream>
#include<thread>
#include<mutex>

using namespace std;

// g++ monitor03.cpp -lpthread

#define NUM_HILOS 10

int cont=0;
mutex flag;

class Monitor {
	public:
	void inc(){
		//flag.lock();	// LOCK
		for(int i=0; i<10; i++){
			cont++;
		}
		//flag.unlock();	// UNLOCK
		//return cont;
	}
};

class Hilo {
	private:
		Monitor* monitor;
		thread t;
		void run_thread(){
			flag.lock();	// LOCK	----ERROR
			monitor->inc();		//	RUN
			cout<<cont<<endl;	//	RUN
			flag.unlock();	// UNLOCK	----ERROR
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







