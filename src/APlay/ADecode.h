#pragma once
#include <mutex>
struct AVCodecParameters;
struct AVCodecContext;
struct AVFrame;
struct AVPacket;
extern void XFreePacket(AVPacket** pkt);
class ADecode
{
public:
	bool isAudio = false;

	//��ǰ�����pts
	long long pts = 0;
	//�򿪽�����,���ܳɹ�����ͷ�para�ռ�
	virtual bool Open(AVCodecParameters* para);

	//���͵������̣߳����ܳɹ�����ͷ�pkt�ռ䣨�����ý�����ݣ�
	virtual bool Send(AVPacket* pkt);

	//��ȡ�������ݣ�һ��send������Ҫ���Recv����ȡ�����е�����Send NULL��Recv���
	//ÿ�θ���һ�ݣ��ɵ������ͷ� av_frame_free
	virtual AVFrame* Recv();

	virtual void Close();
	virtual void Clear();

	ADecode();
	virtual ~ADecode();
protected:
	AVCodecContext* codec = 0;
	std::mutex mux;
};

