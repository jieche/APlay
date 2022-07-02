

#include "XAudioThread.h"
#include "ADecode.h"
#include "XAudioPlay.h"
#include "XResample.h"
#include <iostream>
using namespace std;


//ֹͣ�̣߳�������Դ
void XAudioThread::Close()
{
	ADecodeThread::Close();
	if (res)
	{
		res->Close();
		amux.lock();
		delete res;
		res = NULL;
		amux.unlock();
	}
	if (ap)
	{
		ap->Close();
		amux.lock();
		ap = NULL;
		amux.unlock();
	}
}

bool XAudioThread::Open(AVCodecParameters* para, int sampleRate, int channels)
{
	if (!para)return false;

	Clear();

	amux.lock();
	pts = 0;
	if (!decode) decode = new ADecode();
	if (!res) res = new XResample();
	if (!ap) ap = XAudioPlay::Get();
	bool re = true;
	if (!res->Open(para, false))
	{
		cout << "XResample open failed!" << endl;
		re = false;
	}
	ap->sampleRate = sampleRate;
	ap->channels = channels;
	if (!ap->Open())
	{
		re = false;
		cout << "XAudioPlay open failed!" << endl;
	}
	amux.unlock();

	if (!decode->Open(para))
	{
		cout << "audio XDecode open failed!" << endl;
		re = false;
	}
	cout << "XAudioThread::Open :" << re << endl;
	return re;
}
void XAudioThread::run()
{
	unsigned char* pcm = new unsigned char[1024 * 1024 * 10];
	while (!isExit)
	{
		amux.lock();

		////û������
		//if (packs.empty() || !decode || !res || !ap)
		//{
		//	amux.unlock();
		//	msleep(1);
		//	continue;
		//}

		//AVPacket* pkt = packs.front();
		//packs.pop_front();


		AVPacket* pkt = Pop();
		bool re = decode->Send(pkt);
		if (!re)
		{
			amux.unlock();
			msleep(1);
			continue;
		}
		//һ��send ���recv
		while (!isExit)
		{
			AVFrame* frame = decode->Recv();
			if (!frame) break;

			pts = decode->pts - ap->getNoPlayMs();
			cout << "audio pts = " << pts << endl;

			//�ز��� 
			int size = res->Resample(frame, pcm);
			//������Ƶ
			while (!isExit)
			{
				if (size <= 0)break;
				//����δ���꣬�ռ䲻��
				if (ap->GetFree() < size)
				{
					msleep(1);
					continue;
				}
				ap->Write(pcm, size);
				break;
			}
		}
		amux.unlock();
	}
	delete pcm;
}

XAudioThread::XAudioThread()
{
}


XAudioThread::~XAudioThread()
{
	//�ȴ��߳��˳�
	isExit = true;
	wait();
}
