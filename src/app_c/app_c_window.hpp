#ifndef APP_C_WINDOW_H_
#define APP_C_WINDOW_H_

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>

#include "beep_thread.hpp"

class AppCWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit AppCWindow(QWidget* parent = nullptr);
	~AppCWindow() override;

private slots:
	void ApplyPeriodT();
	void CheckTermination();
	void UpdateUiFromSharedData();

private:
	void SetupUi();
	void SetupConnections();
	void SetupTimers();

	void closeEvent(QCloseEvent* event) override;

	QLineEdit* t_edit_;
	QPushButton* apply_button_;
	SharedMemory shared_mem_;
	BeepThread* beep_thread_;

	int period_t_;
};

#endif  // APP_C_WINDOW_H_