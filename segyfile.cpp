#include "segyfile.h"
#include <QFileInfo>
#include <QFile>
#include <QDataStream>
#include <QDebug>
CSegyHead::CSegyHead(QString path){
    this->path=path;
}

QString CSegyHead::getDataTime(){
    char *buffersu;
    buffersu =getSu();//获得道头
    QString dataTime;
    char year[2] = {buffersu[156] , buffersu[157]};
    unsigned short *year_u_short = (unsigned short *)year;
    dataTime = QString::number(*year_u_short);
    char data[2] = {buffersu[158] , buffersu[159]};
    unsigned short *data_u_short = (unsigned short *)data;
    dataTime.append(QString::number(*data_u_short));
    char hour[2] = {buffersu[160] , buffersu[161]};
    unsigned short *hour_u_short = (unsigned short *)hour;
    dataTime.append(QString::number(*hour_u_short));
    char min[2] = {buffersu[162] , buffersu[163]};
    unsigned short *min_u_short = (unsigned short *)min;
    dataTime.append(QString::number(*min_u_short));
    char sec[2] = {buffersu[164] , buffersu[165]};
    unsigned short *sec_u_short = (unsigned short *)sec;
    dataTime.append(QString::number(*sec_u_short));
    qDebug()<<QString::fromLocal8Bit("判别位置")<<dataTime;
    qDebug()<<*year_u_short<<" "<<*data_u_short<<" "<<*hour_u_short<<" "<<*min_u_short<<" "<<*sec_u_short;
    delete buffersu;
    return dataTime;
}

char* CSegyHead::getSu(){
    QFile file(this->path);
    if(file.open(QFile::ReadOnly)){
        qDebug()<<"open success!";
        QDataStream in(&file);
        char *buffersu = new char[240];//存入道头的缓存
        for(int i=0;i<240;i++)
            buffersu[i]=0;
        file.seek(3600);
        in.setVersion(QDataStream::Qt_5_5);
        in.readRawData(buffersu,240);
        return buffersu;
    }
}
