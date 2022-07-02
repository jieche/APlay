


#pragma once

///�������ʾ��Ƶ
struct AVPacket;
struct AVCodecParameters;
class ADecode;
#include <list>
#include <mutex>
#include <QThread>
#include "IVideoCall.h"
#include "ADecodeThread.h"
class XVideoThread:public ADecodeThread
{
public:
	//�򿪣����ܳɹ��������
	virtual bool Open(AVCodecParameters *para,IVideoCall *call,int width,int height);
	void run();

	XVideoThread();
	virtual ~XVideoThread();

	void SetPause(bool isPause);

	IVideoCall *call = 0;
public:
	std::mutex vmux;
	bool isPause = false;



};

