#include "app_a_window.hpp"

#include <QApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>

AppAWindow::AppAWindow(QWidget* parent)
	: QMainWindow(parent)
	, process_b_(nullptr)
	, process_c_(nullptr)
	, manual_termination_b_(false)
	, period_t_(1000) 
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
}

AppAWindow::~AppAWindow() 
{
	shared_mem_.Lock();
	SharedData* data = shared_mem_.GetData();
	if (data) 
		data->terminate_all = true;
	shared_mem_.Unlock();

	TerminateAppB();
	TerminateAppC();
}

void AppAWindow::ApplyPeriodT() 
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

void AppAWindow::StartAppB() 
{
	if (!process_b_) 
	{
		process_b_ = new QProcess(this);
		process_b_->start("app_b");
		manual_termination_b_ = false;

		shared_mem_.Lock();
		SharedData* data = shared_mem_.GetData();
		if (data) 
			data->app_b_running = true;
		shared_mem_.Unlock();
	}
}

void AppAWindow::TerminateAppB() 
{
	if (process_b_ && process_b_->state() == QProcess::Running) 
	{
		process_b_->terminate();
		if (!process_b_->waitForFinished(3000)) 
			process_b_->kill();
		manual_termination_b_ = true;

		shared_mem_.Lock();
		SharedData* data = shared_mem_.GetData();
		if (data)
			data->app_b_running = false;
		shared_mem_.Unlock();

		process_b_->deleteLater();
		process_b_ = nullptr;
	}
}

void AppAWindow::StartAppC() 
{
	if (!process_c_)
	{
		process_c_ = new QProcess(this);
		process_c_->start("app_c");

		shared_mem_.Lock();
		SharedData* data = shared_mem_.GetData();
		if (data) 
			data->app_c_running = true;
		shared_mem_.Unlock();
	}
}

void AppAWindow::TerminateAppC() 
{
	if (process_c_ && process_c_->state() == QProcess::Running) 
	{
		process_c_->terminate();
		if (!process_c_->waitForFinished(3000))
			process_c_->kill();

		shared_mem_.Lock();
		SharedData* data = shared_mem_.GetData();
		if (data) 
			data->app_c_running = false;
		shared_mem_.Unlock();

		process_c_->deleteLater();
		process_c_ = nullptr;
	}
}

void AppAWindow::ToggleBeep() 
{
	shared_mem_.Lock();
	SharedData* data = shared_mem_.GetData();
	if (data) 
		data->beep_enabled = !(data->beep_enabled);
	shared_mem_.Unlock();
}

void AppAWindow::MonitorProcesses()
{
	if (process_b_ 
		&& process_b_->state() != QProcess::Running 
		&& !manual_termination_b_) 
	{
		process_b_->deleteLater();
		process_b_ = new QProcess(this);
		process_b_->start("app_b");

		shared_mem_.Lock();
		SharedData* data = shared_mem_.GetData();
		if (data) 
			data->app_b_running = true;
		shared_mem_.Unlock();
	}

	if (process_c_ 
		&& process_c_->state() != QProcess::Running) 
	{
		process_c_ = nullptr;
	}

	shared_mem_.Lock();
	SharedData* data = shared_mem_.GetData();
	if (data && data->terminate_all)
	{
		shared_mem_.Unlock();
		close();
		return;
	}
	shared_mem_.Unlock();
}

void AppAWindow::UpdateUiFromSharedData() 
{
	shared_mem_.Lock();
	SharedData* data = shared_mem_.GetData();
	if (!data) 
	{
		shared_mem_.Unlock();
		return;
	}

	int     current_t = data->period_t;
	bool current_beep = data->beep_enabled;
	shared_mem_.Unlock();

	if (period_t_ != current_t)
	{
		period_t_ = current_t;
		t_edit_->setText(QString::number(current_t));
	}

	beep_button_->setText(current_beep ? "Beep (ON)" : "Beep (OFF)");
}

void AppAWindow::SetupUi() 
{
	QWidget*     central_widget = new QWidget(this);
	QVBoxLayout*    main_layout = new QVBoxLayout(central_widget);
	QHBoxLayout*       t_layout = new QHBoxLayout();

	            t_edit_ = new QLineEdit();
	       beep_button_ = new QPushButton("Beep (OFF)");
	      apply_button_ = new QPushButton("Применить период Т");
	    start_b_button_ = new QPushButton("Запуск приложения B");
	    start_c_button_ = new QPushButton("Запуск приложения C");
	terminate_b_button_ = new QPushButton("Терминация приложения B");
	terminate_c_button_ = new QPushButton("Терминация приложения C");

	t_edit_->setText(QString::number(period_t_));

	t_layout->addWidget(new QLabel("Период T:"));
	t_layout->addWidget(t_edit_);

	main_layout->addLayout(t_layout);
	main_layout->addWidget(apply_button_);
	main_layout->addWidget(start_b_button_);
	main_layout->addWidget(terminate_b_button_);
	main_layout->addWidget(start_c_button_);
	main_layout->addWidget(terminate_c_button_);
	main_layout->addWidget(beep_button_);

	setCentralWidget(central_widget);
	setWindowTitle("Приложение A");
	resize(400, 300);
}

void AppAWindow::SetupConnections() 
{
	connect(apply_button_, &QPushButton::clicked, this, &AppAWindow::ApplyPeriodT);
	connect(start_b_button_, &QPushButton::clicked, this, &AppAWindow::StartAppB);
	connect(terminate_b_button_, &QPushButton::clicked, this, &AppAWindow::TerminateAppB);
	connect(start_c_button_, &QPushButton::clicked, this, &AppAWindow::StartAppC);
	connect(terminate_c_button_, &QPushButton::clicked, this, &AppAWindow::TerminateAppC);
	connect(beep_button_, &QPushButton::clicked, this, &AppAWindow::ToggleBeep);
}

void AppAWindow::SetupTimers() 
{
	QTimer* monitor_timer = new QTimer(this);
	connect(monitor_timer, &QTimer::timeout, this, &AppAWindow::MonitorProcesses);
	monitor_timer->start(100);

	QTimer* update_timer = new QTimer(this);
	connect(update_timer, &QTimer::timeout, this, &AppAWindow::UpdateUiFromSharedData);
	update_timer->start(100);
}

void AppAWindow::closeEvent(QCloseEvent* event)
{
	shared_mem_.Lock();
	SharedData* data = shared_mem_.GetData();
	if (data)
		data->terminate_all = true;
	shared_mem_.Unlock();

	TerminateAppB();
	TerminateAppC();
	QMainWindow::closeEvent(event);
}