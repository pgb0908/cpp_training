#ifndef CPP_TRAINING_THREAD_H
#define CPP_TRAINING_THREAD_H

#include <cstdint>
#include <limits>
#include <string>
#include <functional>
#include <memory>

namespace Thread {
    class Thread {
    public:
        virtual ~Thread() = default;

        /**
         * @return the name of the thread.
         */
        virtual std::string name() const = 0;

        /**
         * Blocks until the thread exits.
         */
        virtual void join() = 0;
    };

    using ThreadPtr = std::unique_ptr<Thread>;

    /**
     * Interface providing a mechanism for creating threads.
     */
    class ThreadFactory {
    public:
        virtual ~ThreadFactory() = default;

        /**
         * Creates a thread, immediately starting the thread_routine.
         *
         * @param thread_routine supplies the function to invoke in the thread.
         */
        virtual ThreadPtr createThread(std::function<void()> thread_routine, std::string name)  = 0;

    };

    using ThreadFactoryPtr = std::unique_ptr<ThreadFactory>;


}


#endif //CPP_TRAINING_THREAD_H
