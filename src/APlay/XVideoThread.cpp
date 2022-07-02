

#include "XVideoThread.h"
#include "ADecode.h"
#include <iostream>
using namespace std;
//�򿪣����ܳɹ��������
bool XVideoThread::Open(AVCodecParameters *para, IVideoCall *call,int width,int height)
{
	if (!para)return false;

	Clear();

	vmux.lock();

	//��ʼ����ʾ����
	this->call = call;
	if (call)
	{
		call->Init(width, height);
	}
	vmux.unlock();

	
	int re = true;
	if (!decode->Open(para))
	{
		cout << "audio XDecode open failed!" << endl;
		re = false;
	}
	cout << "XAudioThread::Open :" << re << endl;
	return re;
}



void XVideoThread::run()
{
	while (!isExit)
	{
		vmux.lock();

		//����Ƶͬ��
		if (synpts>0&&synpts < decode->pts)
		{
			vmux.unlock();
			msleep(1);
			continue;
		}

		////û������
		//if (packs.empty() || !decode)
		//{
		//	vmux.unlock();
		//	msleep(1);
		//	continue;
		//}

	/*	AVPacket *pkt = packs.front();
		packs.pop_front();*/

		AVPacket* pkt = Pop();
		bool re = decode->Send(pkt);
		if (!re)
		{
			vmux.unlock();
			msleep(1);
			continue;
		}
		//һ��send ���recv
		while (!isExit)
		{
			AVFrame * frame = decode->Recv();
			if (!frame) break;
			//��ʾ��Ƶ
			if (call)
			{
				call->Repaint(frame);
			}

		}
		vmux.unlock();
	}
}

XVideoThread::XVideoThread()
{
}


XVideoThread::~XVideoThread()
{

}
