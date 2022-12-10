#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <stdio.h>
#include <thread>
#include <stdlib.h>
#include <iostream>
#include <queue>
#include <vector>
#include <chrono>
#include <random>
#include <string>
using namespace std;

MainWindow main;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}
//-------------------------------------------

#define NUM_PRODUCERS 10

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


class Producer {
    private:
        thread t;
        int Waste;
        int k;
        Buffer* buffer;

        void run_thread() {
            int aleatorio;
            for (int i = 0; true; i++) {
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
                    string message = "Consumer-" + to_string(k) + " estoy consumiendo :" + getChar + "\n";
                    //sendMessageConsumer(message);
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
        }

        void join_thread(){
            t.join();
        }
};

Buffer* buffer = new Buffer(15);
Producer* Producers[NUM_PRODUCERS];
Consumer* Consumers[NUM_PRODUCERS];

int producers = 0;
int consumers = 0;

//-------------------------------------------
void MainWindow::on_addProducer_clicked() {
    if(producers < NUM_PRODUCERS) {
        producers++;
        Producers[producers] = new Producer(producers,buffer);
        Producers[producers]->join_thread();
    }
}


void MainWindow::on_stop_clicked() {
    /*ui->buffer->setText("Perro!");
    ui->textConsumer->setText("Perro!");*/
    ui->textConsumer->insertPlainText("asdasd");
}


void MainWindow::on_addConsumer_clicked() {
    if(consumers < NUM_PRODUCERS) {
        consumers++;
        Consumers[consumers] = new Consumer(consumers,buffer);
        Consumers[consumers]->join_thread();
    }
}

void MainWindow::sendMessageConsumer(std::string message) {
    QString qmessage = QString::fromStdString(message);
    ui->textConsumer->insertPlainText(qmessage);
}

void MainWindow::sendMessageProducer(std::string message) {
    QString qmessage = QString::fromStdString(message);
    ui->textProducer->insertPlainText(qmessage);
}



