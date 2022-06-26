#include "APlay.h"
#include <QtWidgets/QApplication>
#include "ADemux.h"
#include <iostream>
#include "ADecode.h"

using namespace std;

int main(int argc, char *argv[])
{
    ///测试XDemux
    ADemux demux;
    //香港卫视
    ////const char* url = R"(http://devimages.apple.com.edgekey.net/streaming/examples/bipbop_4x3/gear2/prog_index.m3u8)";
    //const char* url =R"(rtmp://live.hkstv.hk.lxdns.com/live/hks)";
    const char*  url = "960_544.mp4";
    cout << "demux.Open = " << demux.Open(url);
    //demux.Clear();
    //demux.Close();
    cout << "CopyVPara = " << demux.CopyVPara() << endl;
    cout << "CopyAPara = " << demux.CopyAPara() << endl;
    cout << "seek=" << demux.Seek(0.995) << endl;

    ADecode vdecode;
    cout << "vdecode.Open() = " << vdecode.Open(demux.CopyVPara()) << endl;
    vdecode.Clear();
    vdecode.Close();
    ADecode adecode;
    cout << "adecode.Open() = " << adecode.Open(demux.CopyAPara()) << endl;
     
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




    QApplication a(argc, argv);
    APlay w;
    w.show();


    //初始化gl窗口
    w.ui.video->Init(demux.width, demux.height);

    return a.exec();
}
