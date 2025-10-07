#ifndef APP_C_BEEPTHREAD_H_
#define APP_C_BEEPTHREAD_H_

#include <QThread>

#include "shared_data/shared_data.hpp"

class BeepThread : public QThread 
{
	Q_OBJECT

public:
	explicit BeepThread(SharedMemoryManager* shared_mem, QObject* parent = nullptr);
	void Stop();

protected:
	void run() override;

private:
	SharedMemoryManager* shared_mem_;
	bool should_stop_;
};
#endif // APP_C_BEEPTHREAD_H_