#ifndef LIB_SHARED_MEMORY_MANAGER_HPP_
#define LIB_SHARED_MEMORY_MANAGER_HPP_

#include <QSharedMemory>
#include <QSystemSemaphore>

struct SharedData 
{
	int period_t;
	bool beep_enabled;
	bool app_b_running;
	bool app_c_running;
	bool terminate_all;
};

constexpr char kSharedMemName[] = "MultiAppSharedMemory";
constexpr char kSemaphoreName[] = "MultiAppSemaphore";

class SharedMemoryManager 
{
public:
	SharedMemoryManager();
	~SharedMemoryManager();

	bool Initialize();
	void Lock();
	void Unlock();
	SharedData* GetData();

private:
	QSharedMemory shared_mem_;
	QSystemSemaphore semaphore_;
	bool is_attached_;
};

#endif  // LIB_SHARED_MEMORY_MANAGER_HPP_