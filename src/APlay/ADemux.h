#pragma once

#include <mutex>

struct AVFormatContext;
struct AVPacket;
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

protected:
	std::mutex mux;
	//���װ������
	AVFormatContext* ic = NULL;
	//����Ƶ��������ȡʱ��������Ƶ
	int videoStream = 0;
	int audioStream = 1;
};


  