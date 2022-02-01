#include <iostream>
#include <thread>
#include <list>
#include <iterator>
#include <algorithm>
#include <chrono>
#include <mutex>
#include <cstdlib>

using namespace std;

std::mutex lk; 
std::list<int> data;
bool status = false;

void producer1() // producer function 
{
    while(true)
    {
        std::unique_lock<std::mutex> ul(lk);
        int j = rand() % 1000;
        data.push_back(j);
        std::cout << "produced data = " << j << "\n";
        status = true;
        ul.unlock();
        while(status)
        {
            std::this_thread::sleep_for (std::chrono::seconds(1));
        }
    }
}

void consumerd(list<int> a) //consumer function
{
    list<int>::iterator it;
    for (it = a.begin(); it != a.end(); ++it)
        cout << "\t received data = "<< *it;
        cout<<"\n";

}
void consumer()
{
    while (true) 
    {
    while (!status) {
      std::this_thread::sleep_for (std::chrono::seconds(1));
    }
    std::unique_lock<std::mutex> ul(lk);
    consumerd(data);
    status = false;
  }
}
void consumerThread() 
{ 
    consumer(); 
}

void producerThread1() 
{ 
    producer1(); 
    
}
void producerThread2() 
{ 
    producer1(); 
    
}

int main()
{
    
    std::thread t1(consumerThread);
    std::thread t2(producerThread1);
    std::thread t3(producerThread2);
    t1.join();
    t2.join();
    t3.join();
    return 0;
  
}
