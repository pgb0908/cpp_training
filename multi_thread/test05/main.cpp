#include <iostream>
#include <thread>
#include <mutex>

std::once_flag flag;

void initialize_shared_resource() {
    std::cout << "Initializing shared resource..." << std::endl;
    // 공유 자원 초기화
}

void use_shared_resource() {
    std::call_once(flag, initialize_shared_resource);
    // 공유 자원 사용
}

int main() {
    std::thread t1(use_shared_resource);
    std::thread t2(use_shared_resource);
    std::thread t3(use_shared_resource);
    std::thread t4(use_shared_resource);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return 0;
}
