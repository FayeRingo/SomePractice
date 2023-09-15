#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>

// 线程交替打印
int cnt = 0;
std::mutex mtx;
std::condition_variable cv;
bool index = true;
int main() {

    auto f = [&](std::string id, bool idx) {
        while (1) {
            {
                //condition_variable要用unique_lock，因为需要上锁解锁
                std::unique_lock<std::mutex> lock(mtx);
                //wait第二个参数是等待条件
                cv.wait(lock, [&] {return index == idx; });
                cnt++;
                std::cout << id << " : " << cnt << std::endl; 
                index = !index;
            }
            //唤醒等待线程(可以解锁后执行)
            cv.notify_one();
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    };
    std::thread t1(f,"Thread A",true), t2(f,"Thread B", false);
    t1.join();
    t2.join();
    return 0;
}