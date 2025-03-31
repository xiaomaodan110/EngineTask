#include <iostream>
#include <thread>
#include <vector>
#include <future>

void singleThread(const int num) {
	// cout 不是线程安全的
	std::cout << "call thread " << num << std::endl;
}

void callManyThread() {
	std::vector<std::thread> threads;

	for (int i = 0; i < 5; ++i) {
		threads.emplace_back(singleThread, i);
	}

	for (auto& thread : threads) {
		thread.join();
	}
}

int add(const int a, const int b) {
	std::cout << "single thread." << std::endl; 
	return a + b;
}

void callAsyncThread() {
	std::future<int> result = std::async(add, 3, 4);

	// 主线程可以继续执行其他任务
	std::cout << "Main thread is doing other things..." << std::endl;

	// 阻塞直到异步线程返回结果
	int sum = result.get();
	std::cout << "Sum is: " << sum << std::endl;

	return;
}

int main() {
	std::cout << "====================== Call main" << std::endl;

	callAsyncThread();

	std::cout << "====================== All threads have finished" << std::endl;

	return 0;
}