#include <mutex>
#include <chrono>
#include <condition_variable>
#include <thread>
#include <deque>

namespace gtu{
	
	class mutex
	{
	public:
		//mutex();
		//~mutex();
		void mutexRegister();
		void lock();
		bool try_lock();
    	void unlock();
    	void get();
		
	private:
		bool isRegistered();
		int ceiling = 0;
		static int lockedCeiling;
		static std::thread::id lockedId;
		bool locked = false;
		int oldPriority;
		std::deque<std::thread::id> threads;
		std::condition_variable cv;
		std::mutex m;
	};
	

}
template class std::lock_guard<gtu::mutex>;
template class std::unique_lock<gtu::mutex>;
template class std::scoped_lock<gtu::mutex>;

/************

condition_variable ile lock yapılabilir?
condition_variable lock ta mutex lazım ?

--UNIQUE_LOCK--
lock Lock mutex (public member function ) eğer lock varsa block
try_lock Lock mutex if not locked (public member function ) eğer locklu değil ise lockla true dön eğer lock varsa error?
try_lock_for Try to lock mutex during time span -bool try_lock_for (const chrono::duration<Rep,Period>& rel_time); verilen zaman kadar locklamaya çalış(veya sleep ?) olmazsa false dön
try_lock_until Try to lock mutex until time point (public member function ) o zamana kadar locklamaya çalış
unlock Unlock mutex (public member function )

--LOCK_GUARD--










***************/