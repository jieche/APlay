

#pragma once
#include <QThread>
#include <mutex>
#include <list>
#include"ADecodeThread.h"
struct AVCodecParameters;
class ADecode;
class XAudioPlay;
class XResample;
class AVPacket;
class XAudioThread:public ADecodeThread
{
public:
	long long pts = 0;

	//打开，不管成功与否都清理
	virtual bool Open(AVCodecParameters *para,int sampleRate,int channels);

	//停止线程，清理资源
	virtual void Close();
	void run();
	XAudioThread();
	virtual ~XAudioThread();

	void SetPause(bool isPause);
	
protected:
	bool isPause = false;
	std::mutex amux;
	XAudioPlay *ap = 0;
	XResample *res = 0;

};

