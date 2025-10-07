#ifndef APP_C_BEEPTHREAD_H_
#define APP_C_BEEPTHREAD_H_

#include <QThread>

#include "shared_memory/shared_memory.hpp"

class BeepThread : public QThread 
{
	Q_OBJECT

public:
	explicit BeepThread(SharedMemory* shared_mem, QObject* parent = nullptr);
	void Stop();

protected:
	void run() override;

private:
	SharedMemory* shared_mem_;
	bool          should_stop_;
};
#endif // APP_C_BEEPTHREAD_H_