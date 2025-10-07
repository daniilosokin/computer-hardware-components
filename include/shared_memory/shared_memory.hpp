#ifndef LIB_SHARED_MEMORY_HPP_
#define LIB_SHARED_MEMORY_HPP_

#include <QSharedMemory>
#include <QSystemSemaphore>

struct SharedData 
{
	int  period_t;
	bool beep_enabled;
	bool app_b_running;
	bool app_c_running;
	bool terminate_all;
};

constexpr char kSharedMemoryName[] = "SHMEM-4HD461312DHS";
constexpr char    kSemaphoreName[] = "SEM-S612DFH8RR78";

class SharedMemory 
{
public:
	SharedMemory();
	~SharedMemory();

	bool        Initialize();
	void        Lock();
	void        Unlock();
	SharedData* GetData();

private:
	bool             is_attached_;
	QSharedMemory    shared_mem_;
	QSystemSemaphore semaphore_;
};

#endif  // LIB_SHARED_MEMORY_HPP_