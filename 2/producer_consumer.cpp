#include <stdio.h>
#include <thread>
#include <stdlib.h>
#include <iostream>
#include <queue>
#include <vector>
#include <chrono>
#include <random>
using namespace std;

#define NUM_PRODUCERS 10
#define NUM_CONSUMERS 10
#define REPETICIONES 10
#define BUFFER_SIZE 10

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
        int Size = 0;
	public:
		Buffer(int size) {
            Size = size;
		}

		int GetSize() {
			return Words.size();
		}

		string GetWords() {
			string words = "";
			for(int i = 0; i < Words.size(); i++) {
				words += Words.front();
				Words.pop();
			}
			return words;
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

class Producer {
	private:
		thread t;
        int Waste;
		int k;
        Buffer* buffer;

		void run_thread() {
			int aleatorio;
			for(int i = 0; i < REPETICIONES || buffer->GetSize() == 0; i++) {
				aleatorio = Random(0,25);
				int size =  buffer->Push(letras[aleatorio]);
                if(-1 != size) {
					printf ("Producer-%d estoy produciendo : %c \n", k, letras[aleatorio]);
					int time = Random(1000,1000);
                    this_thread::sleep_for(std::chrono::milliseconds(time));
                }
				else {
					int time = Random(1000,1000);
                    Waste += time;
                    this_thread::sleep_for(std::chrono::milliseconds(time));
				}
			}
		}

	public:

		int GetWaste() {
			return Waste;
		}

		Producer(int id , Buffer* _buffer) {
			k = id;
			t = thread(&Producer::run_thread, this);
            Waste = 0;
            buffer = _buffer;
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
			for (int i = 0; i < REPETICIONES; i++) {
                char getChar = (*buffer).Pop();
				int time = Random(500,1000);
                
				if(getChar != NULL) {
					Chars.push_back(getChar);
					printf ("\t\t\t\t Consumer-%d estoy consumiendo : %c \n", k, getChar);
				}
				else {
					i --;
                	Waste += time;
				}
                this_thread::sleep_for(std::chrono::milliseconds(time));
			}
		}

	public:

		int GetWaste() {
			return Waste;
		}

		string GetChars() {
			string chars = "";
			for(int i = 0; i < Chars.size(); i++) chars += Chars[i];
			return chars;
		}

		Consumer(int id , Buffer* _buffer) {
			k = id;
			t = thread(&Consumer::run_thread, this);
            Waste = 0;
			buffer = _buffer;
		}

		void join_thread(){
			t.join();
		}
};

Producer* Producers[NUM_PRODUCERS];
Consumer* Consumers[NUM_PRODUCERS];

int main(void) {
    int number, number2, number3 = 0;
	
	cout<<"input number of producers: ";
	cin>>number;

	cout<<"input number of consumers: ";
	cin>>number2;

	Buffer* buffer = new Buffer(BUFFER_SIZE);
	
	int i;

	for (i = 0; i < number && i < NUM_PRODUCERS; i++)	{		
		Producers[i] = new Producer(i,buffer); 
	}

	for (i = 0; i < number2 && i < NUM_CONSUMERS; i++)	{		
        Consumers[i] = new Consumer(i,buffer); 
	}

	for (i = 0; i < number && i < NUM_PRODUCERS; i++)	{		
		Producers[i]->join_thread();
	}

	for (i = 0; i < number2 && i < NUM_CONSUMERS; i++)	{		
        Consumers[i]->join_thread();
	}

	for (int j = 0; j < number; j++) {
		printf("Producers-%d, Waste = %d\n", j, (*Producers[j]).GetWaste());
	}

	for (int j = 0; j < number2; j++) {
		printf("Consumers-%d, Waste = %d, Chars = %s\n", j, (*Consumers[j]).GetWaste(), (*Consumers[j]).GetChars().c_str());
	}

	return 0;
}