#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    av_register_all(); //初始化FFMPEG  调用了这个才能正常使用编码器和解码器
    avformat_network_init(); //支持打开网络文件

    if (SDL_Init(SDL_INIT_AUDIO)) {
        fprintf(stderr,"Could not initialize SDL - %s. \n", SDL_GetError());
        exit(1);
    }

    mPlayer = new VideoPlayer;
    connect(mPlayer,SIGNAL(sig_GetOneFrame(QImage)),this,SLOT(slotGetOneFrame(QImage)));
    connect(mPlayer,SIGNAL(sig_TotalTimeChanged(qint64)),this,SLOT(slotTotalTimeChanged(qint64)));
    connect(mPlayer,SIGNAL(sig_StateChanged(VideoPlayer::PlayerState)),this,SLOT(slotStateChanged(VideoPlayer::PlayerState)));


    mTimer = new QTimer; //定时器-获取当前视频时间
    connect(mTimer,SIGNAL(timeout()),this,SLOT(slotTimeTimeout()));
    mTimer->setInterval(500);

    connect(ui->pushButton_open,SIGNAL(clicked()),this,SLOT(slotBtnClick()));
    connect(ui->pushButton_play,SIGNAL(clicked()),this,SLOT(slotBtnClick()));
    connect(ui->pushButton_pause,SIGNAL(clicked()),this,SLOT(slotBtnClick()));
    connect(ui->pushButton_stop,SIGNAL(clicked()),this,SLOT(slotBtnClick()));

    connect(ui->horizontalSlider,SIGNAL(sliderMoved(int)),this,SLOT(slotSliderMoved(int)));
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setBrush(Qt::black);
    painter.drawRect(0, 0, this->width(), this->height()); //先画成黑色

    if (mImage.size().width() <= 0) return;

    ///将图像按比例缩放成和窗口一样大小
    QImage img = mImage.scaled(this->size(),Qt::KeepAspectRatio);

    int x = this->width() - img.width();
    int y = this->height() - img.height();

    x /= 2;
    y /= 2;

    painter.drawImage(QPoint(x,y),img); //画出图像
}


void MainWindow::slotGetOneFrame(QImage img)
{
    mImage = img;
    this->update();
}


void MainWindow::slotTotalTimeChanged(qint64 uSec)
{
    qint64 sec = uSec/1000000;
    ui->horizontalSlider->setRange(0,sec);
    QString mStr = QString("00%1").arg(sec/60);
    QString sStr = QString("00%1").arg(sec%60);

    QString str = QString("%1:%2").arg(mStr.right(2)).arg(sStr.right(2));
    ui->label_totaltime->setText(str);
}


void MainWindow::slotSliderMoved(int value)
{
    if(QObject::sender() == ui->horizontalSlider){
        mPlayer->seek((qint64)value*1000000);
    }
}


void MainWindow::slotTimeTimeout()
{
    if(QObject::sender() == mTimer){
        qint64 sec = mPlayer->getCurrentTime();

        ui->horizontalSlider->setValue(sec);
        QString mStr = QString("00%1").arg(sec/60);
        QString sStr = QString("00%1").arg(sec%60);

        QString str = QString("%1:%2").arg(mStr.right(2)).arg(sStr.right(2));
        ui->label_currenttime->setText(str);
    }
}


void MainWindow::slotBtnClick()
{
    if(QObject::sender() == ui->pushButton_play){
        mPlayer->play();
    }else if(QObject::sender() == ui->pushButton_pause) {
        mPlayer->pause();
    }else if(QObject::sender() == ui->pushButton_stop) {
        mPlayer->stop();
    }else if(QObject::sender() == ui->pushButton_open) {
        QString s = QFileDialog::getOpenFileName(this,"choose file","/home/rx","视频文件 (*.flv *.rmvb *.avi *.MP4);; 所有文件 (*.*);;");

        if(!s.isEmpty()){
            s.replace("/","\\");
            mPlayer->stop(true);
            mPlayer->setFileName(s);
            mTimer->start();
        }
    }
}



















