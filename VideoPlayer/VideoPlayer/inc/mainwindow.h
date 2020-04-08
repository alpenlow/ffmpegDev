#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "videoplayer.h"
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::MainWindow *ui;
    QImage mImage;
    VideoPlayer *mPlayer;
    QTimer *mTimer;
    bool isPause;

private slots:
    void slotGetOneFrame(QImage img);
    void slotTotalTimeChanged(qint64 uSec);
    void slotSliderMoved(int value);
    void slotTimeTimeout();
    void slotBtnClick();
};

#endif // MAINWINDOW_H
