//
// Created by bont on 23. 12. 28.
//


#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>

std::mutex mtx;
std::condition_variable cv;
bool data_ready = false;

void worker_thread() {
    std::this_thread::sleep_for(std::chrono::seconds(4));
    {
        std::lock_guard<std::mutex> lock(mtx);
        data_ready = true;
    }
    cv.notify_all();
}

int main() {
    std::unique_lock<std::mutex> lock(mtx);

    std::thread worker(worker_thread);

    if (cv.wait_for(lock, std::chrono::seconds(3)) == std::cv_status::no_timeout) {
        std::cout << "Data is ready." << std::endl;
    } else {
        std::cout << "Timeout occurred." << std::endl;
        mtx.unlock();
    }


    worker.join();

    return 0;
}
