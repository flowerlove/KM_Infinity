#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "GlobalMouseEvent.h"
#include "GlobalKeyEvent.h"
#include <QDebug>
#include <QMetaEnum>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(GlobalMouseEvent::getInstance(), &GlobalMouseEvent::mouseEvent, this, &MainWindow::onMouseEvent);
    connect(GlobalMouseEvent::getInstance(), &GlobalMouseEvent::wheelEvent, this, &MainWindow::onWheelEvent);
    connect(GlobalKeyEvent::getInstance(), &GlobalKeyEvent::keyEvent, this, &MainWindow::onKeyboardEvent);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Startup_clicked()
{
    bool ret = GlobalMouseEvent::installMouseEvent();
    ui->LogTextEdit->append(QString("<<<<<<<<<<  GlobalKMEventListener Install %1 >>>>>>>>>>")
                                .arg(ret ? "Success" : "Failed"));
}


void MainWindow::on_Shutdown_clicked()
{
    bool ret = GlobalMouseEvent::removeMouseEvent();
    ui->LogTextEdit->append(QString("<<<<<<<<<< GlobalKMEventListener Uninstall %1 >>>>>>>>>>")
                                .arg(ret ? "Success" : "Failed"));
}

void MainWindow::onMouseEvent(QMouseEvent *event)
{
    switch (event->type())
    {
    case QEvent::MouseButtonPress:
    {
        QString but;
        switch (event->button())
        {
        case Qt::LeftButton:
        {
            but = "LeftMouse";
            break;
        }
        case Qt::RightButton:
        {
            but = "RightMouse";
            break;
        }
        case Qt::MiddleButton:
        {
            but = "MiddleMouse";
            break;
        }
        default:
        {
            but = "unkownMouse";
            break;
        }
        }
        QString str = QString("MouseButton:%1 Down：(x:%2, y:%3)").arg(but).arg(event->x()).arg(event->y());
        ui->LogTextEdit->append(str);
        break;
    }
    case QEvent::MouseMove:
    {
        QString str = QString("MouseMove：(x:%1, y:%2)").arg(event->x()).arg(event->y());
        ui->LogTextEdit->append(str);
        break;
    }
    case QEvent::MouseButtonRelease:
    {
        QString but;
        switch (event->button())
        {
            case Qt::LeftButton:
            {
                but = "LeftMouse";
                break;
            }
            case Qt::RightButton:
            {
                but = "RightMouse";
                break;
            }
            case Qt::MiddleButton:
            {
                but = "MiddleMouse";
                break;
            }
            default:
            {
                but = "unkownMouse";
                break;
            }
        }
        QString str = QString("MouseButton:%1 Rlease：(x:%2, y:%3)").arg(but).arg(event->x()).arg(event->y());
        ui->LogTextEdit->append(str);
        break;
    }
    default:
        break;
    }
    delete event;
}

void MainWindow::onWheelEvent(QWheelEvent *event)
{
    QString str = QString("MouseWheel：%1，(x:%2, y:%3)")
                      .arg(event->delta() > 0 ? "Up" : "Down")
                      .arg(event->x()).arg(event->y());
    ui->LogTextEdit->append(str);
    delete event;
}

void MainWindow::onKeyboardEvent(QKeyEvent *event)
{
    QMetaEnum type     = QMetaEnum::fromType<QEvent::Type>();
    QMetaEnum key      = QMetaEnum::fromType<Qt::Key>();
    QMetaEnum keyboard = QMetaEnum::fromType<Qt::KeyboardModifiers>();
    QString str        = QString("State：[%1]\t Key：[%2]\t modifiers：[%3]]")
                      .arg(type.valueToKey(event->type()))
                      .arg(key.valueToKey(event->key()))
                      .arg(QString(keyboard.valueToKeys(int(event->modifiers()))));

    if(!event->text().isEmpty())
    {
        str += QString("\t Keyboard_TextValue：[%1]").arg(event->text());
    }
    ui->LogTextEdit->append(str);
    delete event;
}


void MainWindow::on_ClearLog_clicked()
{
    ui->LogTextEdit->clear();
}

