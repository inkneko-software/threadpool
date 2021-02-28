#include <functional>
#include <mutex>
#include <thread>
#include <future>
#include <vector>
#include <queue>
#include <stdexcept>

class ThreadPool
{
public:
    using Task = std::function<void()>;
protected:
    std::atomic<bool> terminate{false};
    std::mutex workerPoolMutex_;
    int workersNum_ = 0;
    std::vector<std::thread> workers_;

    std::mutex taskMutex_;
    std::condition_variable taskCV_;
    std::queue<Task> tasks_;

    void workerThread();

public:
    ThreadPool(int workersNum, bool fullRequire=false);

    template <class F, typename ...Args>
    auto addTask(F&& f, Args&&... args) -> std::future<decltype(f(args...))>
    {
        using RetType = decltype(f(args...));
        auto task = std::make_shared<std::packaged_task<RetType()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );
        std::future<RetType> future = task->get_future();
        {
            std::lock_guard<std::mutex> lg(taskMutex_);
            tasks_.emplace(
                [task]()
                {
                    (*task)();
                }
            );
            taskCV_.notify_one();
        }
        return future;
    }

    ~ThreadPool();
};