#pragma once

#include <mutex>

struct AVFormatContext;
struct AVPacket;
struct AVCodecParameters;
class ADemux
{
public:
	ADemux();
	virtual ~ADemux();
public:
	//��ý���ļ� ��ý��  rtmp http rstp
	virtual bool Open(const char* url);

	//�ռ�������ͷ� �ͷ�AVPacket����ռ� ���ݿռ�av_packet_free
	virtual AVPacket* Read();

	//��ȡ��Ƶ����  ���صĿռ���Ҫ����  avcodec_parameters_free
	AVCodecParameters* CopyVPara();

	//��ȡ��Ƶ����  ���صĿռ���Ҫ���� avcodec_parameters_free
	AVCodecParameters* CopyAPara();

	virtual bool IsAudio(AVPacket* pkt);

	//seek λ�� pos 0.0 ~1.0
	virtual bool Seek(double pos);

	//��ն�ȡ����
	virtual void Clear();
	virtual void Close();
	//����Ƶ��������ȡʱ��������Ƶ
	int videoStream = 0;
	int audioStream = 1;
protected:
	std::mutex mux;
	//���װ������
	AVFormatContext* ic = NULL;


public:
	int totalMs = 0;
	int width = 0;
	int height = 0;
	int sampleRate = 0;
	int channels = 0;
};


  