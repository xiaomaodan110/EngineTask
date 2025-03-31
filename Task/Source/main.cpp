#include <iostream>
#include <thread>
#include <vector>
#include <future>

void singleThread(const int num) {
	// cout �����̰߳�ȫ��
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

	// ���߳̿��Լ���ִ����������
	std::cout << "Main thread is doing other things..." << std::endl;

	// ����ֱ���첽�̷߳��ؽ��
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