#include <iostream>
#include <chrono>
#include "../source/ThreadPool.h"
using namespace std::chrono;
int main(int argc, const char** argv)
{
    int threadNum = 10;
    int runTimes = 1000;
    int latency = 1;
    if (argc == 4)
    {
        threadNum = std::stoi(argv[1]);
        runTimes = std::stoi(argv[2]);
        latency = std::stoi(argv[3]);
    }

    std::atomic_int counter(0);
    ThreadPool threadPool(threadNum);
    std::vector<std::future<void>> tasks;
    
    steady_clock::time_point start_time = steady_clock::now();
    for(int i = 0; i < runTimes; ++i)
    {

        tasks.emplace_back(
            threadPool.addTask(
                [&counter, &latency]()->void
                {
                    std::this_thread::sleep_for(milliseconds(latency));
                    counter++;
                }
            )
        );
    }

    for(auto& task : tasks)
    {
        task.get();
    }

    steady_clock::time_point end_time = steady_clock::now();

    duration<double> time_span = duration_cast<duration<double>>(end_time - start_time);
    std::cout << runTimes <<" times plus finished, with latency set: " << latency << "ms, threadNum: " << threadNum << std::endl
              << "counter value: "<< counter << ", time elapsed: " << time_span.count() << std::endl;

    main(argc, argv);
    return 0;
}