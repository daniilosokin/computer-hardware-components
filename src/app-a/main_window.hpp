#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QMainWindow>
#include <QProcess>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_applyPeriodButton_clicked();
    void on_startBButton_clicked();
    void on_terminateBButton_clicked();
    void on_startCButton_clicked();
    void on_terminateCButton_clicked();
    void on_beepButton_clicked();
    void handleProcessBFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void handleProcessCFinished(int exitCode, QProcess::ExitStatus exitStatus);

private:
    Ui::MainWindow *ui;
    QProcess *processB;
    QProcess *processC;
    bool beepEnabled;
    bool terminateRequestedB;
    bool terminateRequestedC;
};

#endif // MAIN_WINDOW_HPP