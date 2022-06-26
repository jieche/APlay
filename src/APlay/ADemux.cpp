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
		//��ʼ����װ��
		av_register_all();

		//��ʼ������� �����Դ�rtsp rtmp http Э�����ý����Ƶ��
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
	//��������
	AVDictionary* opts = NULL;
	//����rtsp����tcpЭ���
	av_dict_set(&opts, "rtsp_transport", "tcp", 0);

	//������ʱʱ��
	av_dict_set(&opts, "max_delay", "500", 0);

	mux.lock();
	int re = avformat_open_input(
		&ic,
		url,
		0,  // 0��ʾ�Զ�ѡ������
		&opts //�������ã�����rtsp����ʱʱ��
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

	//��ȡ����Ϣ 
	re = avformat_find_stream_info(ic, 0);

	//��ʱ�� ����
	int totalMs = ic->duration / (AV_TIME_BASE / 1000);
	cout << "totalMs = " << totalMs << endl;

	//��ӡ��Ƶ����ϸ��Ϣ
	av_dump_format(ic, 0, url, 0);


	//��ȡ��Ƶ��
	videoStream = av_find_best_stream(ic, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);
	AVStream* as = ic->streams[videoStream];

	cout << "=======================================================" << endl;
	cout << videoStream << "��Ƶ��Ϣ" << endl;
	cout << "codec_id = " << as->codecpar->codec_id << endl;
	cout << "format = " << as->codecpar->format << endl;
	cout << "width=" << as->codecpar->width << endl;
	cout << "height=" << as->codecpar->height << endl;
	//֡�� fps ����ת��
	cout << "video fps = " << r2d(as->avg_frame_rate) << endl;

	cout << "=======================================================" << endl;
	cout << audioStream << "��Ƶ��Ϣ" << endl;
	//��ȡ��Ƶ��
	audioStream = av_find_best_stream(ic, AVMEDIA_TYPE_AUDIO, -1, -1, NULL, 0);
	as = ic->streams[audioStream];
	cout << "codec_id = " << as->codecpar->codec_id << endl;
	cout << "format = " << as->codecpar->format << endl;
	cout << "sample_rate = " << as->codecpar->sample_rate << endl;
	//AVSampleFormat;
	cout << "channels = " << as->codecpar->channels << endl;
	//һ֡���ݣ��� ��ͨ�������� 
	cout << "frame_size = " << as->codecpar->frame_size << endl;
	//1024 * 2 * 2 = 4096  fps = sample_rate/frame_size
	mux.unlock();



	return true;
}
 