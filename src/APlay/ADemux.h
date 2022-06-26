#pragma once

#include <mutex>

struct AVFormatContext;
class ADemux
{
public:
	ADemux();
	virtual ~ADemux();
public:
	//��ý���ļ� ��ý��  rtmp http rstp
	virtual bool Open(const char* url);

protected:
	std::mutex mux;
	//���װ������
	AVFormatContext* ic = NULL;
	//����Ƶ��������ȡʱ��������Ƶ
	int videoStream = 0;
	int audioStream = 1;
};


  