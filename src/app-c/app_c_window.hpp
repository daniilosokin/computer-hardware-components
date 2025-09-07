#ifndef APP_C_WINDOW_HPP
#define APP_C_WINDOW_HPP

#include "app_c_window_ui.h"

#include <QMainWindow>
#include <QThread>
#include <QTimer>

class BeepThread : public QThread
{
    Q_OBJECT
	
public:
    explicit BeepThread(int period, bool *enabled, QObject *parent = nullptr);
    void run() override;

private:
    int period;
    bool *enabled;
};

class AppCWindow : public QMainWindow
{
    Q_OBJECT

public:
    AppCWindow(QWidget *parent = nullptr);
    ~AppCWindow();

private slots:
    void on_apply_period_button_clicked();

private:
    AppCWindowUi*ui;
    BeepThread *beep_thread;
    bool beep_enabled;
};

#endif