
#include <iostream>
#include "ThreadImpl.h"
#include "ThreadFactory.h"

void workerTask() {
    std::cout << "Worker " << " started\n";
    // … 실제 작업 …
    std::cout << "Worker " << " done\n";
}

int main(){
    auto factory = Thread::ThreadFactoryImpl::create();

    auto worker1 = factory->createThread(workerTask, "Worker-1");

    auto worker2 = factory->createThread([] {
        std::cout <<  " Lambda thread running\n";}, "Worker-2");


    // 명시적 join(또는 소멸자에서 자동 join)
    worker1->join();
    worker2->join();

    return 0;
}
