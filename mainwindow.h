#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QKeyEvent>

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
    void on_Startup_clicked();

    void on_Shutdown_clicked();

    void onMouseEvent(QMouseEvent* event);
    void onWheelEvent(QWheelEvent* event);
    void onKeyboardEvent(QKeyEvent* event);

    void on_ClearLog_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
