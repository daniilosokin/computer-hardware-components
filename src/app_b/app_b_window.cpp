#include "app_b_window.hpp"

#include <QApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QTimer>

AppBWindow::AppBWindow(QWidget* parent)
	: QMainWindow(parent)
	, period_t_(0) 
{
	if (!shared_mem_.Initialize()) 
	{
		QMessageBox::critical(this, 
							"Ошибка", 
							"Не удалось инициализировать разделяемую память");
		return;
	}

	SetupUi();
	SetupConnections();
	SetupTimers();

	shared_mem_.Lock();
	SharedData* data = shared_mem_.GetData();
	if (data)
		data->app_b_running = true;
	shared_mem_.Unlock();
}

AppBWindow::~AppBWindow() 
{
	shared_mem_.Lock();
	SharedData* data = shared_mem_.GetData();
	if (data) 
		data->app_b_running = false;
	shared_mem_.Unlock();
}

void AppBWindow::ApplyPeriodT() 
{
	bool ok;
	int new_t = t_edit_->text().toInt(&ok);
	if (ok && new_t > 0) 
	{
		shared_mem_.Lock();
		SharedData* data = shared_mem_.GetData();
		if (data) 
			data->period_t = new_t;
		shared_mem_.Unlock();
	} 
	else 
	{
		QMessageBox::warning(this, 
							"Ошибка", 
							"Введите корректное значение T");
	}
}

void AppBWindow::CheckTermination() 
{
	shared_mem_.Lock();
	SharedData* data = shared_mem_.GetData();

	if (!data)
	{
		shared_mem_.Unlock();
		return;
	}

	if (data->terminate_all)
	{
		shared_mem_.Unlock();
		close();
		return;
	}

	int current_t = data->period_t;
	shared_mem_.Unlock();

	if (period_t_ != current_t)
	{
		period_t_ = current_t;
		t_edit_->setText(QString::number(current_t));
	}
}

void AppBWindow::SetupUi() 
{
	QWidget*     central_widget = new QWidget(this);
	QVBoxLayout*    main_layout = new QVBoxLayout(central_widget);
	QHBoxLayout*       t_layout = new QHBoxLayout();

	      t_edit_ = new QLineEdit();
	apply_button_ = new QPushButton("Применить период Т");

	t_layout->addWidget(new QLabel("Период T:"));
	t_layout->addWidget(t_edit_);

	main_layout->addLayout(t_layout);
	main_layout->addWidget(apply_button_);

	setCentralWidget(central_widget);
	setWindowTitle("Приложение B");
	setFixedSize(260, 75);
}

void AppBWindow::SetupConnections() 
{
	connect(apply_button_, &QPushButton::clicked, this, &AppBWindow::ApplyPeriodT);
}

void AppBWindow::SetupTimers() 
{
	QTimer* check_timer = new QTimer(this);
	connect(check_timer, &QTimer::timeout, this, &AppBWindow::CheckTermination);
	check_timer->start(100);
}

void AppBWindow::closeEvent(QCloseEvent* event) 
{
	shared_mem_.Lock();
	SharedData* data = shared_mem_.GetData();
	if (data) 
		data->app_b_running = false;
	shared_mem_.Unlock();
	QMainWindow::closeEvent(event);
}