#pragma once

#include <QtWidgets/QWidget>
#include "ui_APlay.h"

class APlay : public QWidget
{
    Q_OBJECT

public:
    APlay(QWidget *parent = nullptr);
    ~APlay();
public slots:
    void OpenFile();
    void play();
    void SliderPress();
    void SliderRelease();
protected:
    //定时器 滑动条显示
    void timerEvent(QTimerEvent* e) override;

    //窗口尺寸变化
    void resizeEvent(QResizeEvent* e) override;


    //双击全屏
    void mouseDoubleClickEvent(QMouseEvent* e) override;

private:
    Ui::APlayClass *ui;
    bool isSliderPress = false;
};
