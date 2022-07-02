#pragma once
#include <QThread>

struct AVPacket;
struct ADecode;
class ADecodeThread :
	public QThread
{
public:
	ADecodeThread();
	virtual ~ADecodeThread();
	virtual void Push(AVPacket* pkt);
	AVPacket* Pop();
	virtual void Clear();

	//清理资源，停止线程
	virtual void Close();
protected:
	std::list <AVPacket*> packs;
	std::mutex mux;
	ADecode* decode = 0;
	//最大队列
	int maxList = 100;
	bool isExit = false;
public:
	long long synpts = 0;

};

