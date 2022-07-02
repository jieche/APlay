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
protected:
    //��ʱ�� ��������ʾ
    void timerEvent(QTimerEvent* e) override;

    //���ڳߴ�仯
    void resizeEvent(QResizeEvent* e) override;


    //˫��ȫ��
    void mouseDoubleClickEvent(QMouseEvent* e) override;

private:
    Ui::APlayClass *ui;
};
