#pragma once
#include <mutex>
struct AVCodecParameters;
struct AVCodecContext;

class ADecode
{
public:
	bool isAudio = false;

	//�򿪽�����,���ܳɹ�����ͷ�para�ռ�
	virtual bool Open(AVCodecParameters* para);

	virtual void Close();
	virtual void Clear();

	ADecode();
	virtual ~ADecode();
protected:
	AVCodecContext* codec = 0;
	std::mutex mux;
};

