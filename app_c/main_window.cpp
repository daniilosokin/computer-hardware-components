#include "main_window.hpp"
#include "ui_main_window.h"
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
            Beep(1000, 1000); // Beep at 1000Hz for 1s
            QThread::sleep(period);
        } else {
            QThread::msleep(100);
        }
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , beepThread(nullptr)
    , beepEnabled(false)
{
    ui->setupUi(this);
    setWindowTitle("Application C");
}

MainWindow::~MainWindow()
{
    if (beepThread) {
        beepThread->terminate();
        beepThread->wait();
        delete beepThread;
    }
    delete ui;
}

void MainWindow::on_applyPeriodButton_clicked()
{
    bool ok;
    int period = ui->periodLineEdit->text().toInt(&ok);
    if (ok && period > 0) {
        // Здесь должна быть логика обновления периода в других приложениях
        // и обновление периода в beepThread, если он существует
    } else {
        QMessageBox::warning(this, "Error", "Invalid period value");
    }
}