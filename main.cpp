#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>
#include <queue>
#include <ctime>
#include <cstdlib>


#define n_max 10


int mtx;
std::mutex mtx_mutex;
std::queue <int> q;
int nr_rand, item;

void produce(int item)
{
     std::cout <<"introducem in coada numarul "<<item<<" \n";
     std::this_thread::sleep_for(std::chrono::seconds(5));
     q.push(item);



}

void consume()
{
     std::cout <<"extragem din coada \n";
     std::this_thread::sleep_for(std::chrono::seconds(5));
     q.pop();



}

void producer()
{
    while(true)
    {
        if(mtx < n_max)
        {
            mtx_mutex.lock();
            srand( time(0));
            item = rand()%100;
            produce(item);

            mtx = q.size();
            std::cout << "n => " << mtx << '\n';
            mtx_mutex.unlock();
        }
    }
}


void consumer()
{
    while(true)
    {
       if(mtx > 0)
        {
            mtx_mutex.lock();
            consume();
            mtx = q.size();
            std::cout << "n => " << mtx << '\n';
            mtx_mutex.unlock();
        }
    }
}



int main()
{
    mtx = 0;
    int i;
    for(i = 0;i<2;i++)
    {
        srand( time(0));
        item = rand()%100;
        std::cout <<"introducem in coada numarul "<<item<<" \n";
        q.push(item);

    }




    std::thread t1(producer);
    std::thread t2(consumer);
    t1.join();
    t2.join();
}
