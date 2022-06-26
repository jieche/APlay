#pragma once
#include <mutex>
struct AVCodecParameters;
struct AVCodecContext;

class ADecode
{
public:
	bool isAudio = false;

	//打开解码器,不管成功与否都释放para空间
	virtual bool Open(AVCodecParameters* para);

	virtual void Close();
	virtual void Clear();

	ADecode();
	virtual ~ADecode();
protected:
	AVCodecContext* codec = 0;
	std::mutex mux;
};

