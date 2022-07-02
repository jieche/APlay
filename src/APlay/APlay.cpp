#include "APlay.h"
#include<QFileDialog>
#include<QMessageBox>
#include <XDemuxThread.h>

XDemuxThread dt;
APlay::APlay(QWidget *parent)
    : QWidget(parent)
	, ui(new  Ui::APlayClass)
{
    ui->setupUi(this);
	dt.Start();
}

APlay::~APlay()
{
	dt.Close();
	delete ui;
}

void APlay::OpenFile()
{
	//选择文件
	QString name = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("选择视频文件"));
	if (name.isEmpty())return;
	this->setWindowTitle(name);
	if (!dt.Open(name.toLocal8Bit(), ui->video))
	{
		QMessageBox::information(0, "error", "open file failed!");
		return;
	}

}