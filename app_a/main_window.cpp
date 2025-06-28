#include "main_window.hpp"
#include "ui_main_window.h"
#include <QMessageBox>
#include <QSettings>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , processB(new QProcess(this))
    , processC(new QProcess(this))
    , beepEnabled(false)
    , terminateRequestedB(false)
    , terminateRequestedC(false)
{
    ui->setupUi(this);

    connect(processB, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this, &MainWindow::handleProcessBFinished);
    connect(processC, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this, &MainWindow::handleProcessCFinished);
}

MainWindow::~MainWindow()
{
    terminateRequestedB = true;
    terminateRequestedC = true;
    processB->terminate();
    processC->terminate();
    delete ui;
}

void MainWindow::on_applyPeriodButton_clicked()
{
    QString period = ui->periodLineEdit->text();
    // Здесь должна быть логика обновления периода в других приложениях
    // Например, через IPC (QSharedMemory, QLocalSocket и т.д.)
}

void MainWindow::on_startBButton_clicked()
{
    if (processB->state() == QProcess::NotRunning) {
        processB->start("app_b.exe");
        terminateRequestedB = false;
    }
}

void MainWindow::on_terminateBButton_clicked()
{
    if (processB->state() != QProcess::NotRunning) {
        terminateRequestedB = true;
        processB->terminate();
    }
}

void MainWindow::on_startCButton_clicked()
{
    if (processC->state() == QProcess::NotRunning) {
        processC->start("app_c.exe");
        terminateRequestedC = false;
    }
}

void MainWindow::on_terminateCButton_clicked()
{
    if (processC->state() != QProcess::NotRunning) {
        terminateRequestedC = true;
        processC->terminate();
    }
}

void MainWindow::on_beepButton_clicked()
{
    beepEnabled = !beepEnabled;
    ui->beepButton->setText(beepEnabled ? "Beep (ON)" : "Beep (OFF)");
    // Здесь должна быть логика уведомления приложения C о состоянии beep
}

void MainWindow::handleProcessBFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    Q_UNUSED(exitCode);
    Q_UNUSED(exitStatus);
    
    if (!terminateRequestedB && processB->state() == QProcess::NotRunning) {
        QTimer::singleShot(1000, this, [this]() {
            processB->start("app_b.exe");
        });
    }
}

void MainWindow::handleProcessCFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    Q_UNUSED(exitCode);
    Q_UNUSED(exitStatus);
    
    if (!terminateRequestedC && processC->state() == QProcess::NotRunning) {
        QTimer::singleShot(1000, this, [this]() {
            processC->start("app_c.exe");
        });
    }
}