#include "ADecodeThread.h"
#include "ADecode.h"

ADecodeThread::ADecodeThread()
{
	//�򿪽�����
	if (!decode) decode = new ADecode();
}

ADecodeThread::~ADecodeThread()
{
	//�ȴ��߳��˳�
	isExit = true;
	wait();
}

void ADecodeThread::Push(AVPacket* pkt)
{
	if (!pkt)return;
	//����
	while (!isExit)
	{
		mux.lock();
		synpts = 0;
		if (packs.size() < maxList)
		{
			packs.push_back(pkt);
			mux.unlock();
			break;
		}
		mux.unlock();
		msleep(1);
	}
}

AVPacket* ADecodeThread::Pop()
{
	mux.lock();
	if (packs.empty())
	{
		mux.unlock();
		return nullptr;
	}
	auto* pkt = packs.front();
	packs.pop_front();
	mux.unlock();
	return pkt;
}

void ADecodeThread::Clear()
{
	mux.lock();
	decode->Clear();
	while (!packs.empty())
	{
		AVPacket* pkt = packs.front();
		XFreePacket(&pkt);
		packs.pop_front();
	}
	mux.unlock();
}