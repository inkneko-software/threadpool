# threadpool
thread pool written in c++ 11 with std::thread + std::future

## Install:
```shell
$ mkdir build && cd build
$ cmake .. && make
$ sudo make install
[ 50%] Built target inkneko_thread_pool
[100%] Built target thread_pool_test
Install the project...
-- Install configuration: ""
-- Installing: /usr/local/include/nekorpc/ThreadPool.h
-- Installing: /usr/local/lib/libinkneko_thread_pool.so
```
## Tests:

```shell
$ tests/thread_pool_test 1 1000 1
1000 times plus finished, with latency set: 1ms, threadNum: 1
counter value: 1000, time elapsed: 1.26811
1000 times plus finished, with latency set: 1ms, threadNum: 1
counter value: 1000, time elapsed: 1.27039
1000 times plus finished, with latency set: 1ms, threadNum: 1
counter value: 1000, time elapsed: 1.26788


$ tests/thread_pool_test 10 1000 1
1000 times plus finished, with latency set: 1ms, threadNum: 10
counter value: 1000, time elapsed: 0.12013
1000 times plus finished, with latency set: 1ms, threadNum: 10
counter value: 1000, time elapsed: 0.123693
1000 times plus finished, with latency set: 1ms, threadNum: 10
counter value: 1000, time elapsed: 0.123175


$ tests/thread_pool_test 100 1000 1
1000 times plus finished, with latency set: 1ms, threadNum: 100
counter value: 1000, time elapsed: 0.0298044
1000 times plus finished, with latency set: 1ms, threadNum: 100
counter value: 1000, time elapsed: 0.035674
1000 times plus finished, with latency set: 1ms, threadNum: 100
counter value: 1000, time elapsed: 0.0312232
```

## Example
To be continued... You can check out the [test](tests/main.cpp).

Mainly in these procedures:
1. Create thread pool with:  `ThreadPool threadPool(threadNum);` 
2. Find a place to save your task, like `std::vector<std::future<TaskFuncRetType>> tasks;`
3. Call `tasks.emplace_back(threadPool.addTask(taskfunc))` to leave your task function executed by the thread.
4. Use `std::future::wait_for(timeout)` to check weather the task finished.
5. Use `std::future::get()` to obtain the task function return value.