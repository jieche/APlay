#include "APlay.h"
#include <QtWidgets/QApplication>
#include "ADemux.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    ///≤‚ ‘XDemux
    ADemux demux;
    //œ„∏€Œ¿ ”
    ////const char* url = R"(http://devimages.apple.com.edgekey.net/streaming/examples/bipbop_4x3/gear2/prog_index.m3u8)";
    //const char* url =R"(rtmp://live.hkstv.hk.lxdns.com/live/hks)";
    const char*  url = "960_544.mp4";
    cout << "demux.Open = " << demux.Open(url);

    cout << "CopyVPara = " << demux.CopyVPara() << endl;
    cout << "CopyAPara = " << demux.CopyAPara() << endl;

    while (true)
    {
        AVPacket* pkt = demux.Read();
        if (!pkt)
        {
            break;
        }
    }




    QApplication a(argc, argv);
    APlay w;
    w.show();
    return a.exec();
}
