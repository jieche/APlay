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
private:
    Ui::APlayClass *ui;
};
