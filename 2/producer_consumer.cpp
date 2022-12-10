#include<stdio.h>
#include<thread>
#include<stdlib.h>
#include<iostream>
#include <queue>
#include<vector>
#include <chrono>
#include <random>
using namespace std;

// g++ productores02.cpp -lpthread

#define NUM_PRODUCTORES 3

const char letras[26] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };

int Random(int Min, int Max) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(Min,Max); 

    return dist6(rng);
}

class Buffer {
	private:
		queue<char> Words;
        int Size;
	public:
		Buffer(int size) {
            Size = size;
		}

        int Push(char myChar) {
            if(Words.size() < Size) { 
                Words.push(myChar);
                return Words.size();
            }
            return -1;
        }

        char Pop() {
            if(Words.size() > 0) {
                char result = Words.front();
                Words.pop();
                return result;
            }
            return NULL;
        }
};

//void productor (int k);
class Producer {
	private:
		thread t;
        int Waste;
		int k;
        Buffer* buffer;

		void run_thread() {
			int aleatorio;
			for (int i = 1; true; i++) {
				aleatorio = Random(0,25);
				int size =  buffer->Push(letras[aleatorio]);
                if(-1 != size) {
					printf ("(%d) Producer-%d estoy produciendo : %c \n", size, k, letras[aleatorio]);
                }
				else {
					int time = Random(10000,30000);
                    Waste += time;
                    this_thread::sleep_for(std::chrono::milliseconds(time));
				}
			}
		}

	public:

		Producer(int id , Buffer* _buffer) {
			k = id;
			t = thread(&Producer::run_thread, this);
            Waste = 0;
            buffer = _buffer;
			//t.join();
		}

		void join_thread() {
			t.join();
		}
};

class Consumer {
	private:
		thread t;
        int Waste;
		int k;
        vector<char> Chars;
        Buffer* buffer;

		void run_thread() {
			for (int i = 1; true; i++) {
                char getChar = (*buffer).Pop();
                if(getChar != NULL) {
					Chars.push_back(getChar);
					printf ("\t\t\t\t(%d) Consumer-%d estoy consumiendo : %c \n", i, k, getChar);
				}

                    int time = Random(10000,50000);
                    Waste += time;
                    this_thread::sleep_for(std::chrono::milliseconds(time));

			}
		}

	public:

		Consumer(int id , Buffer* _buffer) {
			k = id;
			t = thread(&Consumer::run_thread, this);
            Waste = 0;
			buffer = _buffer;
			//t.join();
		}

		void join_thread(){
			t.join();
		}
};

int main(void) {
    int number = 0;
	
	cout<<"input number of producers: ";
	cin>>number;

	Buffer* buffer = new Buffer(10);
	Producer* Producers[NUM_PRODUCTORES];
    Consumer* Consumers[NUM_PRODUCTORES];
	int identificadores[NUM_PRODUCTORES];

	int i;

	for (i=0; i<NUM_PRODUCTORES; i++)	{		
		Producers[i] = new Producer(i,buffer); 
        Consumers[i] = new Consumer(i,buffer); 
	}

	for (i=0; i<NUM_PRODUCTORES; i++)	{
		Producers[i]->join_thread();
        Consumers[i]->join_thread();
	}

	//printf ("(Consumer-%d estoy consumiendo : %c \n", i, k, getChar);
	return 0;
}


