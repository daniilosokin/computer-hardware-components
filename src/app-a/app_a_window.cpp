#include "app_a_window.hpp"

#include <QMessageBox>
#include <QSettings>
#include <QDebug>

AppAWindow::AppAWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new AppAWindowUi)
    , process_app_b(new QProcess(this))
    , process_app_c(new QProcess(this))
    , beep_enabled(false)
    , terminate_requested_app_b(false)
    , terminate_requested_app_c(false)
{
    ui->setupUi(this);

    connect(process_app_b, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this, &AppAWindow::handle_process_app_b_finished);
    connect(process_app_c, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this, &AppAWindow::handle_process_app_c_finished);
}

AppAWindow::~AppAWindow()
{
    terminate_requested_app_b = true;
    terminate_requested_app_c = true;
    process_app_b->terminate();
    process_app_c->terminate();
    delete ui;
}

void AppAWindow::on_apply_period_button_clicked()
{
    QString period = ui->period_line_edit->text();
    // Здесь должна быть логика обновления периода в других приложениях
    // Например, через IPC (QSharedMemory, QLocalSocket и т.д.)
}

void AppAWindow::on_start_app_b_button_clicked()
{
    if (process_app_b->state() == QProcess::NotRunning) {
        process_app_b->start("app-b.exe");
        terminate_requested_app_b = false;
    }
}

void AppAWindow::on_terminate_app_b_button_clicked()
{
    if (process_app_b->state() != QProcess::NotRunning) {
        terminate_requested_app_b = true;
        process_app_b->terminate();
    }
}

void AppAWindow::on_start_app_c_button_clicked()
{
    if (process_app_c->state() == QProcess::NotRunning) {
        process_app_c->start("app-c.exe");
        terminate_requested_app_c = false;
    }
}

void AppAWindow::on_terminate_app_c_button_clicked()
{
    if (process_app_c->state() != QProcess::NotRunning) {
        terminate_requested_app_c = true;
        process_app_c->terminate();
    }
}

void AppAWindow::on_beep_button_clicked()
{
    beep_enabled = !beep_enabled;
    ui->beep_button->setText(beep_enabled ? "Beep (ON)" : "Beep (OFF)");
    // Здесь должна быть логика уведомления приложения C о состоянии beep
}

void AppAWindow::handle_process_app_b_finished(int exit_code, QProcess::ExitStatus exit_status)
{
    Q_UNUSED(exit_code);
    Q_UNUSED(exit_status);
    
    if (!terminate_requested_app_b && process_app_b->state() == QProcess::NotRunning) {
        QTimer::singleShot(100, this, [this]() {
            process_app_b->start("app-b.exe");
        });
    }
}

void AppAWindow::handle_process_app_c_finished(int exit_code, QProcess::ExitStatus exit_status)
{
    Q_UNUSED(exit_code);
    Q_UNUSED(exit_status);
    
    if (!terminate_requested_app_c && process_app_c->state() == QProcess::NotRunning) 
    {
        QTimer::singleShot(100, this, [this]() {
            process_app_c->start("app-c.exe");
        });
    }
}