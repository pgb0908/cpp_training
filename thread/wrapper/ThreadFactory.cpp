//
// Created by bont on 25. 5. 14.
//

#include "ThreadFactory.h"
#include "ThreadImpl.h"

#include <sys/syscall.h>
#include <unistd.h>
#include <sys/prctl.h>

int64_t getCurrentThreadIdBase() {
    return static_cast<int64_t>(syscall(SYS_gettid));
}

int64_t getCurrentThreadId() {
    // Use the static value rather than the static pointer to suppress ASAN memory leak
    // errors.
    static thread_local const int64_t tid = getCurrentThreadIdBase();
    return tid;
}

Thread::ThreadPtr Thread::ThreadFactoryImpl::createThread(std::function<void()> thread_routine,
                                                          std::string name) {
    auto f = thread_routine;

    auto thread_handle =
            new ThreadHandle(thread_routine);

    thread_handle->handle() = std::thread([this, f, name](){
        setName(name);
        f();
    });






    return std::make_unique<ThreadImpl>(thread_handle, name);
}


Thread::ThreadFactoryPtr Thread::ThreadFactoryImpl::create() {
    return std::make_unique<ThreadFactoryImpl>();
}

void Thread::ThreadFactoryImpl::setName(const std::string &name) {
    ::prctl(PR_SET_NAME, name.c_str());
}
