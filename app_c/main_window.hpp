#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QMainWindow>
#include <QThread>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui 
{
	class MainWindow;
}
QT_END_NAMESPACE

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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_applyPeriodButton_clicked();

private:
    Ui::MainWindow *ui;
    BeepThread *beepThread;
    bool beepEnabled;
};

#endif // MAIN_WINDOW_HPP