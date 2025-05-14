//
// Created by bont on 25. 5. 14.
//

#ifndef CPP_TRAINING_THREADFACTORY_H
#define CPP_TRAINING_THREADFACTORY_H

#include "Thread.h"

namespace Thread{

    class ThreadFactoryImpl : public ThreadFactory{
    public:
        static ThreadFactoryPtr create();

        ThreadPtr createThread(std::function<void()> thread_routine, std::string name) override;

    private:
        void setName(const std::string& name);

    };

}




#endif //CPP_TRAINING_THREADFACTORY_H
