#include "ADemux.h"

extern "C" {
#include "libavformat/avformat.h"
}

#include <mutex>
#include <iostream>
using namespace std;

#pragma comment(lib,"avformat.lib")
#pragma comment(lib,"avutil.lib")

ADemux::ADemux()
{
	static bool isFirst = true;
	static std::mutex dmux;
	dmux.lock();
	if (isFirst)
	{
		//初始化封装库
		av_register_all();

		//初始化网络库 （可以打开rtsp rtmp http 协议的流媒体视频）
		avformat_network_init();
		isFirst = false;
	}
	dmux.unlock();
}

ADemux::~ADemux()
{
}

static double r2d(AVRational r)
{
	return r.den == 0 ? 0 : (double)r.num / (double)r.den;
}

bool ADemux::Open(const char* url)
{
	//参数设置
	AVDictionary* opts = NULL;
	//设置rtsp流已tcp协议打开
	av_dict_set(&opts, "rtsp_transport", "tcp", 0);

	//网络延时时间
	av_dict_set(&opts, "max_delay", "500", 0);

	mux.lock();
	int re = avformat_open_input(
		&ic,
		url,
		0,  // 0表示自动选择解封器
		&opts //参数设置，比如rtsp的延时时间
	);
	if (re != 0)
	{
		mux.unlock();
		char buf[1024] = { 0 };
		av_strerror(re, buf, sizeof(buf) - 1);
		cout << "open " << url << " failed! :" << buf << endl;
		return false;
	}
	cout << "open " << url << " success! " << endl;

	//获取流信息 
	re = avformat_find_stream_info(ic, 0);

	//总时长 毫秒
	int totalMs = ic->duration / (AV_TIME_BASE / 1000);
	cout << "totalMs = " << totalMs << endl;

	//打印视频流详细信息
	av_dump_format(ic, 0, url, 0);


	//获取视频流
	videoStream = av_find_best_stream(ic, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);
	AVStream* as = ic->streams[videoStream];

	cout << "=======================================================" << endl;
	cout << videoStream << "视频信息" << endl;
	cout << "codec_id = " << as->codecpar->codec_id << endl;
	cout << "format = " << as->codecpar->format << endl;
	cout << "width=" << as->codecpar->width << endl;
	cout << "height=" << as->codecpar->height << endl;
	//帧率 fps 分数转换
	cout << "video fps = " << r2d(as->avg_frame_rate) << endl;

	cout << "=======================================================" << endl;
	cout << audioStream << "音频信息" << endl;
	//获取音频流
	audioStream = av_find_best_stream(ic, AVMEDIA_TYPE_AUDIO, -1, -1, NULL, 0);
	as = ic->streams[audioStream];
	cout << "codec_id = " << as->codecpar->codec_id << endl;
	cout << "format = " << as->codecpar->format << endl;
	cout << "sample_rate = " << as->codecpar->sample_rate << endl;
	//AVSampleFormat;
	cout << "channels = " << as->codecpar->channels << endl;
	//一帧数据？？ 单通道样本数 
	cout << "frame_size = " << as->codecpar->frame_size << endl;
	//1024 * 2 * 2 = 4096  fps = sample_rate/frame_size
	mux.unlock();



	return true;
}
 