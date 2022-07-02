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

	//������Դ��ֹͣ�߳�
	virtual void Close();
protected:
	std::list <AVPacket*> packs;
	std::mutex mux;
	ADecode* decode = 0;
	//������
	int maxList = 100;
	bool isExit = false;
public:
	long long synpts = 0;

};

