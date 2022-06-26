#pragma once

#include <mutex>

struct AVFormatContext;
class ADemux
{
public:
	ADemux();
	virtual ~ADemux();
public:
	//打开媒体文件 流媒体  rtmp http rstp
	virtual bool Open(const char* url);

protected:
	std::mutex mux;
	//解封装上下文
	AVFormatContext* ic = NULL;
	//音视频索引，读取时区分音视频
	int videoStream = 0;
	int audioStream = 1;
};


  