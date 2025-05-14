//
// Created by bont on 25. 5. 14.
//

#ifndef CPP_TRAINING_THREADIMPL_H
#define CPP_TRAINING_THREADIMPL_H

#include <thread>
#include <iostream>
#include "Thread.h"


namespace Thread {
    class ThreadHandle {
    public:
        explicit ThreadHandle(std::function<void()> thread_routine);

        /** Returns the thread routine. */
        std::function<void()>& routine();

        /** Returns the thread handle. */
        std::thread& handle();

    private:
        std::function<void()> thread_routine_;
        std::thread thread_handle_;
    };


    class ThreadImpl : public Thread{
    public:

        explicit ThreadImpl(ThreadHandle* threadHandle, std::string name);

        ~ThreadImpl() override;

        std::string name() const override;

        void join() override;

        bool joinable() const;

        std::thread::id threadId() const;

    private:
        std::string name_;
        ThreadHandle* threadHandle_;
        bool joined_{false};


        std::function<void()> thread_routine_;
    };

}



#endif //CPP_TRAINING_THREADIMPL_H
