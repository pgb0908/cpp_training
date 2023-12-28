
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

void producer(std::queue<std::string>* pages, std::mutex* m, int index, std::condition_variable* cv){
    for(int i=0; i< 5; i++){
        std::this_thread::sleep_for(std::chrono::milliseconds(100 * index));
        std::string content = "website : " + std::to_string(i) + " from thread(" + std::to_string(i+1) + ")\n";

        m->lock();
        pages->push(content);
        m->unlock();

        cv->notify_one();
    }
}

void consumer(std::queue<std::string>* pages, std::mutex* m, int* num_processed, std::condition_variable* cv){

    while(*num_processed < 25){
        // lock_guard와 동일하지만 unique_lock은 생성자
        // 외에도 lock을 할 수 있음
        std::unique_lock<std::mutex> lk(*m); // 현시점에 lock을 함

        cv->wait(
                // false 이면 lk를 unlock하고 sleep 상태가됨
                // true이면 lk가 lock이됨
                lk, [&](){return !pages->empty() || *num_processed == 25;}
                );

        if(*num_processed == 25){
            lk.unlock();
            return;
        }

        auto content = pages->front();
        pages->pop();

        (*num_processed)++;
        lk.unlock();

        std::cout << content;
        std::this_thread::sleep_for(std::chrono::milliseconds(80));
    }
}

int main()
{
    std::queue<std::string> downloaded_pages;
    std::mutex m;
    std::condition_variable cv;

    std::vector<std::thread> producers;
    for(int i=0; i< 5; i++){
        producers.push_back(
                std::thread(producer, &downloaded_pages, &m, i+1, &cv));
    }

    int num_processed = 0;
    std::vector<std::thread> consumers;
    for(int i=0; i<3; i++){
        consumers.push_back(
                std::thread(consumer, &downloaded_pages, &m, &num_processed, &cv)
                );
    }

    for(int i=0; i< 5; i++){
        producers[i].join();
    }

    cv.notify_all();

    for(int i=0; i<3; i++){
        consumers[i].join();
    }

    return 0;
}