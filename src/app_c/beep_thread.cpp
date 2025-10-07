#include "beep_thread.hpp"

#ifdef _WIN32
	#include <Windows.h>
#elif
	#include <stdio.h>
#endif

BeepThread::BeepThread(SharedMemory* shared_mem, QObject* parent)
	: QThread(parent)
	, shared_mem_(shared_mem)
	, should_stop_(false)
{}

void BeepThread::Stop() 
{
	should_stop_ = true;
}

void BeepThread::run() 
{
	while (!should_stop_ && !isInterruptionRequested()) 
	{
		shared_mem_->Lock();
		SharedData* data = shared_mem_->GetData();
		if (!data)
		{
			shared_mem_->Unlock();
			break;
		}

		int       period_t = data->period_t;
		bool  beep_enabled = data->beep_enabled;
		bool terminate_all = data->terminate_all;
		shared_mem_->Unlock();

		if (terminate_all) 
			break;

		if (beep_enabled)
		{	
			#ifdef _WIN32
				Beep(440, 1000);
			#else
				system("echo -e "\007" >/dev/tty10");
			#endif
			
			msleep(period_t);
		} 
		else 
			msleep(100);
	}
}