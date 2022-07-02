

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

	//�򿪣����ܳɹ��������
	virtual bool Open(AVCodecParameters *para,int sampleRate,int channels);

	//ֹͣ�̣߳�������Դ
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

