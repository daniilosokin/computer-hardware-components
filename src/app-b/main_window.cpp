#include "main_window.hpp"
#include "ui_main_window.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_apply_period_button_clicked()
{
    QString period = ui->period_line_edit->text();
    // Здесь должна быть логика обновления периода в других приложениях
}