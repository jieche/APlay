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
	startTimer(40);
}

APlay::~APlay()
{
	dt.Close();
	delete ui;
}

void APlay::SliderPress()
{
	isSliderPress = true;
}
void APlay::SliderRelease()
{
	isSliderPress = false;
	double pos = 0.0;
	pos = (double)ui->horizontalSlider->value() / (double)ui->horizontalSlider->maximum();
	dt.Seek(pos);
}

void APlay::play()
{
	bool isPause = !dt.isPause;
	dt.SetPause(isPause);
	if (!isPause)
	{
		ui->pushButton_play->setText(QString::fromLocal8Bit("播放"));
	}
	else
	{
		ui->pushButton_play->setText(QString::fromLocal8Bit("暂停"));

	}
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

//定时器 滑动条显示
void APlay::timerEvent(QTimerEvent* e)
{
	if (isSliderPress)return;
	long long total = dt.totalMs;
	if (total > 0)
	{
		double pos = (double)dt.pts / (double)total;
		int v = ui->horizontalSlider->maximum() * pos;
		ui->horizontalSlider->setValue(v);
	}
}


//双击全屏
void APlay::mouseDoubleClickEvent(QMouseEvent* e)
{
	if (isFullScreen())
		this->showNormal(); 
	else
		this->showFullScreen();
}
//窗口尺寸变化
void APlay::resizeEvent(QResizeEvent* e)
{
	ui->horizontalSlider->move(50, this->height() - 100);
	ui->horizontalSlider->resize(this->width() - 100, ui->horizontalSlider->height());
	ui->pushButton->move(100, this->height() - 150);
	ui->video->resize(this->size());
}
