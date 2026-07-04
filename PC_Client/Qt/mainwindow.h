#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QtMqtt/qmqttclient.h"
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
    QMqttClient *pMqttClient;//mqtt服务器对象
    QTimer *timer1;

private slots:
    void connected_isr();//连接回调函数
    void disconnected_isr();
    void recv_message(QByteArray message);//接收消息回调
    void timer1Handler();

    void on_pbtn_start_alarm_clicked();

    void on_pbtn_close_alarm_clicked();

    void on_pbtn_clear_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
