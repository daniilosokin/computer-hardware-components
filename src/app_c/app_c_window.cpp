#include "app_c_window.hpp"

#include <QApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QTimer>
#include <Windows.h>

BeepThread::BeepThread(SharedMemoryManager* shared_mem, QObject* parent)
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
			Beep(1000, 1000);

			if (period_t > 1000) 
				msleep(period_t - 1000);
		} 
		else 
			msleep(100);
	}
}

AppCWindow::AppCWindow(QWidget* parent)
	: QMainWindow(parent)
	, beep_thread_(nullptr)
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

	beep_thread_ = new BeepThread(&shared_mem_, this);
	beep_thread_->start();

	shared_mem_.Lock();
	SharedData* data = shared_mem_.GetData();
	if (data) 
		data->app_c_running = true;
	shared_mem_.Unlock();
}

AppCWindow::~AppCWindow()
{
	if (beep_thread_ && beep_thread_->isRunning())
	{
		beep_thread_->Stop();
		beep_thread_->wait(3000);
	}

	shared_mem_.Lock();
	SharedData* data = shared_mem_.GetData();
	if (data) 
		data->app_c_running = false;
	shared_mem_.Unlock();
}

void AppCWindow::ApplyPeriodT() 
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
		QMessageBox::warning(this,
							"Ошибка", 
							"Введите корректное значение T");
}

void AppCWindow::CheckTermination()
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

void AppCWindow::SetupUi() 
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
	setWindowTitle("Приложение C");
	setFixedSize(260, 75);
}

void AppCWindow::SetupConnections() 
{
	connect(apply_button_, &QPushButton::clicked, this, &AppCWindow::ApplyPeriodT);
}

void AppCWindow::SetupTimers() 
{
	QTimer* check_timer = new QTimer(this);
	connect(check_timer, &QTimer::timeout, this, &AppCWindow::CheckTermination);
	check_timer->start(100);
}

void AppCWindow::closeEvent(QCloseEvent* event)
{
	if (beep_thread_ && beep_thread_->isRunning()) 
	{
		beep_thread_->Stop();
		beep_thread_->wait(1000);
	}

	shared_mem_.Lock();
	SharedData* data = shared_mem_.GetData();
	if (data) 
		data->app_c_running = false;
	shared_mem_.Unlock();
	QMainWindow::closeEvent(event);
}