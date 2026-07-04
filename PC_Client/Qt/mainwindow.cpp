#include "mainwindow.h"
#include "ui_mainwindow.h"

bool mqtt_connect_state;
bool device_online_state;
uint8_t device_online_cnt;

/* 连接云平台用到的参数 */
QString Hostname = "anszgfn.iot.gz.baidubce.com";
QString Username = "thingidp@anszgfn|smart_pet_collar_device_15|0|MD5";
QString Password = "d95bda79e19b27bdc64438088abff846";
QString Topic = "$iot/smart_pet_collar_device_15/user/msg";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    pMqttClient=new QMqttClient(this);    //实例化QMqttClient对象

    pMqttClient->setHostname(Hostname);    //连接mqtt服务器
    pMqttClient->setPort(1883);
    pMqttClient->setClientId(QString().append("%1%2").arg("app").arg(QTime::currentTime().msec()));
    pMqttClient->setUsername(Username);
    pMqttClient->setPassword(Password);
    pMqttClient->setKeepAlive(60);

    connect(pMqttClient, &QMqttClient::messageReceived, this,
            [=](const QByteArray &message, const QMqttTopicName &topic){
        qDebug() << "收到消息:" << message << "Topic:" << topic.name();
    });

    pMqttClient->connectToHost();

    auto sub = pMqttClient->subscribe(QMqttTopicFilter(Topic));
    if (!sub)
        qDebug() << "订阅失败!";
    else
        qDebug() << "订阅成功";

    connect(pMqttClient,&QMqttClient::connected,    //连接异步槽
                    this,&MainWindow::connected_isr);
    connect(pMqttClient,&QMqttClient::disconnected,    //连接异步槽
                    this,&MainWindow::disconnected_isr);
    connect(pMqttClient,&QMqttClient::messageReceived,
                    this,&MainWindow::recv_message);

    ui->label_state->setText("设备离线");
    ui->label_temp->setText("");
    ui->label_step_num->setText("");
    ui->label_heart->setText("");
    ui->label_spo2->setText("");
    ui->label_lat->setText("");
    ui->label_lon->setText("");

    timer1 = new QTimer;
    connect(timer1, SIGNAL(timeout()), this, SLOT(timer1Handler()));
    timer1->start(200);

    qSetRealNumberPrecision(6);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/* 定时器1溢出事件 */
void MainWindow::timer1Handler()
{
    static uint8_t cnt = 0;

    if(device_online_cnt == 0)
    {
        cnt++;
        if(cnt > 30)
        {
            cnt = 0;
            device_online_state = 0;
            ui->label_state->setText("设备离线");
            ui->label_temp->setText("");
            ui->label_step_num->setText("");
            ui->label_heart->setText("");
            ui->label_spo2->setText("");
            ui->label_lat->setText("");
            ui->label_lon->setText("");
        }
    }
    else
    {
        cnt = 0;
    }

    device_online_cnt = 0;
}

//成功连接回调
void MainWindow::connected_isr()
{
    qDebug()<<"MQTT Connected Successfully!";
    mqtt_connect_state = 1;
    pMqttClient->subscribe(QMqttTopicFilter(Topic));//订阅频道
}

//断开连接回调
void MainWindow::disconnected_isr()
{
    qDebug()<<" MQTT Disonnected!";
    mqtt_connect_state = 0;
    pMqttClient->connectToHost();
}

//收到消息回调
void MainWindow::recv_message(QByteArray message)
{
    uint8_t buff[200];
    uint16_t len = message.size();

    memset(buff,0,sizeof(buff));
    for(uint8_t i = 0;i < len;i++)
    {
        buff[i] = message[i];
    }

    int device_type;
    float temp,temp_thre;
    int step_num;
    float longitude;//经度
    float latitude;	//纬度
    int xinlv,xinlv_thre;
    int xueyang,xueyang_thre;//心率 血氧

    qDebug() << message;

    /* 判断是否满足10个参数 */
    if(sscanf((char *)buff,"{%d,%f,%f,%d,%d,%d,%d,%d,%f,%f}",&device_type,&temp,&temp_thre,&step_num,&xinlv,&xinlv_thre,&xueyang,&xueyang_thre,&longitude,&latitude) == 10)
    {
        qDebug() << device_type << temp << step_num << xinlv << xinlv_thre << xueyang << xueyang_thre << QString::number(longitude, 'f', 6) << QString::number(latitude, 'f', 6);
        if(device_type == 1)
        {
            ui->label_state->setText("");
            ui->label_temp->setText(QString("体温:%1° 阈值:%2°").arg(QString::number(temp, 'f', 1)).arg(QString::number(temp_thre, 'f', 0)));
            ui->label_step_num->setText(QString("宠物步数:%1").arg(step_num));
            ui->label_heart->setText(QString("心率:%1 阈值:%2").arg(xinlv).arg(xinlv_thre));
            ui->label_spo2->setText(QString("血氧:%1 阈值:%2").arg(xueyang).arg(xueyang_thre));
            ui->label_lon->setText(QString("经度:%1").arg(QString::number(longitude, 'f', 6)));
            ui->label_lat->setText(QString("纬度:%1").arg(QString::number(latitude, 'f', 6)));
            device_online_state = 1;
            device_online_cnt++;
        }
        qDebug() << "收到原始消息:" << message;
    }
}

void MainWindow::on_pbtn_start_alarm_clicked()
{
    if(mqtt_connect_state)
    {
        QByteArray buff;

        buff.append(QString("{2,1,%1}").arg(1));
        pMqttClient->publish(QMqttTopicName(Topic),buff,0,true);
    }
}

void MainWindow::on_pbtn_close_alarm_clicked()
{
    if(mqtt_connect_state)
    {
        QByteArray buff;

        buff.append(QString("{2,1,%1}").arg(0));
        pMqttClient->publish(QMqttTopicName(Topic),buff,0,true);
    }
}

void MainWindow::on_pbtn_clear_clicked()
{
    if(mqtt_connect_state)
    {
        QByteArray buff;

        buff.append(QString("{2,2,%1}").arg(1));
        pMqttClient->publish(QMqttTopicName(Topic),buff,0,true);
    }
}

void MainWindow::on_pushButton_clicked()
{
    if(mqtt_connect_state)
    {
        QByteArray buff;

        buff.append(QString("{2,3,%1}").arg(ui->spinBox_temp_thre->value()));
        pMqttClient->publish(QMqttTopicName(Topic),buff,0,true);
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    if(mqtt_connect_state)
    {
        QByteArray buff;

        buff.append(QString("{2,4,%1}").arg(ui->spinBox_xinlv_thre->value()));
        pMqttClient->publish(QMqttTopicName(Topic),buff,0,true);
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    if(mqtt_connect_state)
    {
        QByteArray buff;

        buff.append(QString("{2,5,%1}").arg(ui->spinBox_spo2_thre->value()));
        pMqttClient->publish(QMqttTopicName(Topic),buff,0,true);
    }
}
