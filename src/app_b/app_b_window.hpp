#ifndef APP_B_WINDOW_H_
#define APP_B_WINDOW_H_

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>

#include "shared_data/shared_data.hpp"

class AppBWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit AppBWindow(QWidget* parent = nullptr);
	~AppBWindow() override;

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

	int period_t_;
};

#endif  // APP_B_WINDOW_H_