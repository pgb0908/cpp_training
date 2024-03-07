#include <iostream>
#include <thread>
#include <future>

void compute(std::promise<int>& prom) {
    // 비동기 작업 수행
    int result = 42; // 예시로 42를 결과로 설정

    // 결과를 promise에 저장
    prom.set_value(result);
}

/*int main() {
    // 비동기 작업을 수행, 중간 결과를 저장
    std::promise<int> prom;

    // 나중에 결과를 받게될 대상
    std::future<int> fut = prom.get_future();

    // 비동기 작업 시작
    std::thread t(compute, std::ref(prom));

    // 결과를 가져와서 출력
    std::cout << "Result: " << fut.get() << std::endl;

    t.join(); // 스레드 종료 대기
    return 0;
}*/

class TestA {
public:
    TestA() : thread_([this](){
        /// thread2가 수행되는 부분
        hello();
    }){

    }
    void run(){
        std::call_once(once_, [this]() {
            /// thread1이 수행되는 부분
            auto f = promiseForRun_.get_future();
            (void)f.get();

            std::cout << "run" << std::endl;

        });
    }

    void wait(){
        thread_.join();
    }

private:
    void hello(){
        std::cout << "hi" << std::endl;
        promiseForRun_.set_value(1);
        std::cout << "h2" << std::endl;
    }

    std::thread thread_;
    std::promise<int> threadHello_;
    std::promise<int> promiseForRun_;
    std::once_flag once_;
};


int main() {
    int a = 0;
    while(a != 100){
        std::cout << "------------------------" << std::endl;
        auto aa = TestA();
        aa.run();
        aa.wait();
        std::cout << "------------------------" << std::endl;
        a++;
    }


    return 0;
}