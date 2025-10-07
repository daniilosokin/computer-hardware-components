#ifndef APP_A_WINDOW_H_
#define APP_A_WINDOW_H_

#include <QMainWindow>
#include <QProcess>
#include <QTimer>

#include "shared_data/shared_data.hpp"

class QLineEdit;
class QPushButton;

class AppAWindow : public QMainWindow 
{
	Q_OBJECT

public:
	explicit AppAWindow(QWidget* parent = nullptr);
	~AppAWindow() override;

private slots:
	void ApplyPeriodT();
	void StartAppB();
	void TerminateAppB();
	void StartAppC();
	void TerminateAppC();
	void ToggleBeep();
	void MonitorProcesses();
	void UpdateUiFromSharedData();

private:
	void SetupUi();
	void SetupConnections();
	void SetupTimers();

	void closeEvent(QCloseEvent* event) override;

	QLineEdit* t_edit_;
	QPushButton* apply_button_;
	QPushButton* start_b_button_;
	QPushButton* terminate_b_button_;
	QPushButton* start_c_button_;
	QPushButton* terminate_c_button_;
	QPushButton* beep_button_;

	QProcess* process_b_;
	QProcess* process_c_;
	SharedMemoryManager shared_mem_;

	bool manual_termination_b_;
	bool beep_enabled_;
	int period_t_;
};

#endif  // APP_A_WINDOW_H_