#include "app_c_window.hpp"

#include <windows.h>

#include <QMessageBox>

BeepThread::BeepThread(int period, bool *enabled, QObject *parent)
    : QThread(parent), period(period), enabled(enabled)
{
}

void BeepThread::run()
{
    while (true) {
        if (*enabled) {
            Beep(1000, 1000);
            QThread::sleep(period);
        } else {
            QThread::msleep(100);
        }
    }
}

AppCWindow::AppCWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new AppCWindowUi)
    , beep_thread(nullptr)
    , beep_enabled(false)
{
    ui->setupUi(this);
}

AppCWindow::~AppCWindow()
{
    if (beep_thread) {
        beep_thread->terminate();
        beep_thread->wait();
        delete beep_thread;
    }
    delete ui;
}

void AppCWindow::on_apply_period_button_clicked()
{
    bool ok;
    int period = ui->period_line_edit->text().toInt(&ok);
    if (ok && period > 0) {
        // Здесь должна быть логика обновления периода в других приложениях
        // и обновление периода в beepThread, если он существует
    } else {
        QMessageBox::warning(this, "Error", "Invalid period value");
    }
}