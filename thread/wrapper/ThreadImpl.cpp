//
// Created by bont on 25. 5. 14.
//


#include "ThreadImpl.h"

#include <cassert>
#include <utility>

std::string Thread::ThreadImpl::name() const {
    return name_;
}

void Thread::ThreadImpl::join() {
    assert(!joined_);
    if(threadHandle_->handle().joinable()){
        joined_ = true;
        threadHandle_->handle().join();
    }
}

bool Thread::ThreadImpl::joinable() const {
    return threadHandle_->handle().joinable();
}


Thread::ThreadImpl::ThreadImpl(ThreadHandle *threadHandle, std::string  name)
: threadHandle_(threadHandle), name_(std::move(name)) {}



Thread::ThreadImpl::~ThreadImpl() {
    assert(joined_);
    delete threadHandle_;
}

std::thread::id Thread::ThreadImpl::threadId() const {
    return std::this_thread::get_id();
}


Thread::ThreadHandle::ThreadHandle(std::function<void()> thread_routine):
        thread_routine_(std::move(thread_routine)){

}

std::function<void()> &Thread::ThreadHandle::routine() {
    return thread_routine_;
}

std::thread &Thread::ThreadHandle::handle() {
    return thread_handle_;
}
