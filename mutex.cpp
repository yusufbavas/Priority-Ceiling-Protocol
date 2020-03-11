#include "mutex.hpp"
#include "OSPriority.hpp"
#include <iostream>
#include <algorithm>

int gtu::mutex::lockedCeiling = 0;
std::thread::id gtu::mutex::lockedId = (std::thread::id) 0;

void gtu::mutex::lock(){
	
	
	if (!isRegistered())
		throw std::runtime_error("Error: Thread is not is not registered!");

	OSPriority pri;
	
	if (pri.getPriority() > lockedCeiling || lockedId == std::this_thread::get_id()){

		lockedCeiling = ceiling;
		lockedId = std::this_thread::get_id();
		std::cout<<"deneme"<<std::endl;

	}
	else{
		std::unique_lock<std::mutex> lck(m);
		while(locked && pri.getPriority() > lockedCeiling){
    		cv.wait(lck);
		}
    	std::cout<<"deneme2"<<std::endl;
    	lockedCeiling = ceiling;
    	lockedId = std::this_thread::get_id();
	}
	locked = true;
	std::cout<<"locked"<<std::endl;
}

bool gtu::mutex::try_lock(){
	
	std::cout<<"try lock"<<std::endl;
}

void gtu::mutex::unlock(){
//	locked = false;
	lockedCeiling = 0;
	locked = false;
	cv.notify_one();
	std::cout<<"unlocked"<<std::endl;
}

void gtu::mutex::mutexRegister(){
	OSPriority pri;
	pri.getPriority() > ceiling ? ceiling = pri.getPriority() : 0;
	threads.push_back(std::this_thread::get_id());
}

void gtu::mutex::get(){
	std::cout<<ceiling<<std::endl;
	
}

bool gtu::mutex::isRegistered(){

	auto res = std::find(threads.begin(), threads.end(), std::this_thread::get_id());
	
	if (res == threads.end())
		return false;
	else
		return true;
}