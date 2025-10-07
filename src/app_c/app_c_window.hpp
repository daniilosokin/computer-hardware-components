#ifndef APP_C_WINDOW_H_
#define APP_C_WINDOW_H_

#include <QMainWindow>
#include <QThread>

#include "shared_data/shared_data.hpp"

class QLineEdit;
class QPushButton;

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

class AppCWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit AppCWindow(QWidget* parent = nullptr);
	~AppCWindow() override;

private slots:
	void ApplyPeriodT();
	void CheckTermination();

private:
	void SetupUi();
	void SetupConnections();
	void SetupTimers();

	void closeEvent(QCloseEvent* event) override;

	QLineEdit* t_edit_;
	QPushButton* apply_button_;
	SharedMemoryManager shared_mem_;
	BeepThread* beep_thread_;

	int period_t_;
};

#endif  // APP_C_WINDOW_H_