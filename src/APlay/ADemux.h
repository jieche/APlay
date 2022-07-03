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
	//打开媒体文件 流媒体  rtmp http rstp
	virtual bool Open(const char* url);

	//空间调用者释放 释放AVPacket对象空间 数据空间av_packet_free
	virtual AVPacket* Read();

	//获取视频参数  返回的空间需要清理  avcodec_parameters_free
	AVCodecParameters* CopyVPara();

	//获取音频参数  返回的空间需要清理 avcodec_parameters_free
	AVCodecParameters* CopyAPara();

	virtual bool IsAudio(AVPacket* pkt);

	//seek 位置 pos 0.0 ~1.0
	virtual bool Seek(double pos);

	//清空读取缓存
	virtual void Clear();
	virtual void Close();
	//音视频索引，读取时区分音视频
	int videoStream = 0;
	int audioStream = 1;
protected:
	std::mutex mux;
	//解封装上下文
	AVFormatContext* ic = NULL;


public:
	int totalMs = 0;
	int width = 0;
	int height = 0;
	int sampleRate = 0;
	int channels = 0;
};


  