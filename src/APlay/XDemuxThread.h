#pragma once
#include <QThread>
#include "IVideoCall.h"
#include <mutex>
class ADemux;
class XVideoThread;
class XAudioThread;
class XDemuxThread:public QThread
{
public:
	//�������󲢴�
	virtual bool Open(const char *url, IVideoCall *call);

	//���������߳�
	virtual void Start();
	//�ر��߳�������Դ
	virtual void Close();
	void run();
	XDemuxThread();
	virtual ~XDemuxThread();
	bool isExit = false;
	long long pts = 0;
	long long totalMs = 0;
protected:
	std::mutex mux;
	ADemux *demux = 0;
	XVideoThread *vt = 0;
	XAudioThread *at = 0;
};

