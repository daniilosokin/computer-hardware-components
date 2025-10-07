#include "shared_memory.hpp"

#include <QMessageBox>

SharedMemory::SharedMemory()
	: shared_mem_(kSharedMemoryName)
	, semaphore_(kSemaphoreName, 1)
	, is_attached_(false)
{}

SharedMemory::~SharedMemory() 
{
	if (is_attached_) 
		shared_mem_.detach();
}

bool SharedMemory::Initialize() 
{
	Lock();

	if (!shared_mem_.create(sizeof(SharedData)) 
		&& shared_mem_.error() == QSharedMemory::AlreadyExists) 
	{
		if (!shared_mem_.attach()) 
		{
			Unlock();
			return false;
		}
	} 
	else if (!shared_mem_.isAttached()) 
	{
		Unlock();
		return false;
	}

	is_attached_ = true;

	if (shared_mem_.size() == sizeof(SharedData)) 
	{
		SharedData* data = static_cast<SharedData*>(shared_mem_.data());
		data->period_t      = 1000;
		data->beep_enabled  = false;
		data->app_b_running = false;
		data->app_c_running = false;
		data->terminate_all = false;
	}

	Unlock();
	return true;
}

void SharedMemory::Lock() 
{
	semaphore_.acquire();
}

void SharedMemory::Unlock() 
{
	semaphore_.release();
}

SharedData* SharedMemory::GetData()
{
	if (!is_attached_ || !shared_mem_.data()) 
		return nullptr;

	return static_cast<SharedData*>(shared_mem_.data());
}