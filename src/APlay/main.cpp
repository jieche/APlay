#include "APlay.h"
#include <QtWidgets/QApplication>
#include "ADemux.h"
#include <iostream>
#include "ADecode.h"

#include<QThread>
#include <XResample.h>
#include <XAudioPlay.h>
#include <XAudioThread.h>

using namespace std;


class TestThread :public QThread
{
public:
	XAudioThread at;
	void Init()
	{
		//œ„∏€Œ¿ ”
		const char* url = "rtmp://live.hkstv.hk.lxdns.com/live/hks";
		cout << "demux.Open = " << demux.Open(url);
		demux.Read();
		demux.Clear();
		demux.Close();
		url = "960_544.mp4";
		cout << "demux.Open = " << demux.Open(url);
		//cout << "CopyVPara = " << demux.CopyVPara() << endl;
		//cout << "CopyAPara = " << demux.CopyAPara() << endl;
		////cout << "seek=" << demux.Seek(0.95) << endl;

		///////////////////////////////

		cout << "vdecode.Open() = " << vdecode.Open(demux.CopyVPara()) << endl;
		////vdecode.Clear();
		////vdecode.Close();
		//cout << "adecode.Open() = " << adecode.Open(demux.CopyAPara()) << endl;
		//cout << "resample.Open = " << resample.Open(demux.CopyAPara()) << endl;
		////XAudioPlay::Get()->channels = demux.channels;
		////XAudioPlay::Get()->sampleRate = demux.sampleRate;
		//cout << "XAudioPlay::Get()->Open() = " << XAudioPlay::Get()->Open() << endl;

		demux.sampleRate = 44100;
		demux.channels = 2;

		cout << "at.Open = " << at.Open(demux.CopyAPara(), demux.sampleRate, demux.channels);
		at.start();
	}
	unsigned char* pcm = new unsigned char[1024 * 1024];
	void run()
	{
		for (;;)
		{
			AVPacket* pkt = demux.Read();
			if (demux.IsAudio(pkt))
			{
				at.Push(pkt);

			/*	adecode.Send(pkt);
				AVFrame *frame = adecode.Recv();
				int len = resample.Resample(frame, pcm);
				cout << "Resample:" << len << " ";
				while (len > 0)
				{
					if (XAudioPlay::Get()->GetFree() >= len)
					{
						XAudioPlay::Get()->Write(pcm, len);
						break;
					}
					msleep(1);
				}*/
				//cout << "Audio:" << frame << endl;
			}
			else
			{
				vdecode.Send(pkt);
				AVFrame* frame = vdecode.Recv();
				video->Repaint(frame);
				msleep(40);
				cout << "Video:" << frame << endl;
			}
			if (!pkt)break;
		}

	}
	///≤‚ ‘XDemux
	ADemux demux;
	///Ω‚¬Î≤‚ ‘
	ADecode vdecode;
	ADecode adecode;
	XVideoWidget* video;
	XResample resample;

};


int main(int argc, char *argv[])
{
    /////≤‚ ‘XDemux
    //ADemux demux;
    ////œ„∏€Œ¿ ”
    //////const char* url = R"(http://devimages.apple.com.edgekey.net/streaming/examples/bipbop_4x3/gear2/prog_index.m3u8)";
    ////const char* url =R"(rtmp://live.hkstv.hk.lxdns.com/live/hks)";
    //const char*  url = "960_544.mp4";
    //cout << "demux.Open = " << demux.Open(url);
    ////demux.Clear();
    ////demux.Close();
    //cout << "CopyVPara = " << demux.CopyVPara() << endl;
    //cout << "CopyAPara = " << demux.CopyAPara() << endl;
    //cout << "seek=" << demux.Seek(0.995) << endl;

    //ADecode vdecode;
    //cout << "vdecode.Open() = " << vdecode.Open(demux.CopyVPara()) << endl;
    //vdecode.Clear();
    //vdecode.Close();
    //ADecode adecode;
    //cout << "adecode.Open() = " << adecode.Open(demux.CopyAPara()) << endl;
     
    //while (true)
    //{
    //    AVPacket* pkt = demux.Read();
    //    if (demux.IsAudio(pkt))
    //    {
    //        adecode.Send(pkt);
    //        AVFrame* frame = adecode.Recv();
    //        //cout << "Audio:" << frame << endl;
    //    }
    //    else
    //    {
    //        vdecode.Send(pkt);
    //        AVFrame* frame = vdecode.Recv();
    //        //cout << "Video:" << frame << endl;
    //    }
    //    if (!pkt)
    //    {
    //        break;
    //    }
    //}

	TestThread tt;
	tt.Init();


    QApplication a(argc, argv);
    APlay w;
    w.show();


    //≥ı ºªØgl¥∞ø⁄
    w.ui.video->Init(tt.demux.width, tt.demux.height);
	tt.video = w.ui.video;
	tt.start();
    return a.exec();
}
