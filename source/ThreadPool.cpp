#include "ThreadPool.h"
ThreadPool::ThreadPool(int workersNum, bool fullRequire)
{
    for (int i = 0; i < workersNum; ++i)
    {
        workers_.emplace_back(std::bind(&ThreadPool::workerThread, this));
        workersNum_++;
    }
}

ThreadPool::~ThreadPool()
{
    this->terminate.store(true);
    this->taskCV_.notify_all();
    for(auto& thread : workers_)
    {
        thread.join();
    }
}
void ThreadPool::workerThread()
{
    while(terminate != true)
    {
        std::unique_lock<std::mutex> lock(taskMutex_);
        taskCV_.wait(lock, [this]{return this->terminate.load() || this->tasks_.empty() != true;});
        if (this->terminate.load() == true)
        {
            return ;
        }
        auto task = std::move(tasks_.front());
        tasks_.pop();
        lock.unlock();
        task();
    }
}