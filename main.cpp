#include "mutex.hpp"
#include "OSPriority.hpp"


#include <thread> 

#include <iostream>

using namespace std;
using namespace gtu;

gtu::mutex m1;
gtu::mutex m2;
gtu::mutex m3;

void thread1(int x){
	OSPriority pri;
	pri.setPriority(x);
	
	m1.mutexRegister();
	m2.mutexRegister();

	std::cout<<"t1 locklamaya calisti yaptı"<<std::endl;
	m1.lock();
	std::this_thread::sleep_for (std::chrono::seconds(1));
	m2.lock();
	std::cout<<"t1 lock"<<std::endl;

	std::this_thread::sleep_for (std::chrono::seconds(3));
	std::cout<<"t1 iş yaptı"<<std::endl;

	m1.unlock();
	m2.unlock();

}

void thread2(int x){
	OSPriority pri;
	pri.setPriority(x);
	
	m1.mutexRegister();
	m2.mutexRegister();

	std::cout<<"t2 loclamaya calisti yaptı"<<std::endl;
	m2.lock();
	std::this_thread::sleep_for (std::chrono::seconds(1));
	m1.lock();
	std::cout<<"t2 lock"<<std::endl;

	std::this_thread::sleep_for (std::chrono::seconds(3));
	std::cout<<"t2 iş yaptı"<<std::endl;

	m2.unlock();
	m1.unlock();
}

void thread3(int x){
	OSPriority pri;
	pri.setPriority(x);
	m3.mutexRegister();

	std::cout<<"t3 loclamaya calisti yaptı"<<std::endl;
	m3.lock();
	std::cout<<"t3 lock"<<std::endl;
	
	std::this_thread::sleep_for (std::chrono::seconds(1));
	std::cout<<"t3 iş yaptı"<<std::endl;

	m3.unlock();
	

}
/*
void thread4(int x){
	OSPriority pri;
	pri.setPriority(x);
	m.mutexRegister();
}*/

int main(int argc, char const *argv[])
{
	thread t1 (thread1,10);
	thread t2 (thread2,9);
	thread t3 (thread3,40);
	/*thread t4 (thread4,30);
*/
	t1.join();
	t2.join();
	t3.join();
	/*t4.join();*/

	return 0;
}