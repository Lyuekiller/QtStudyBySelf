#include "segyfile.h"
#include <QFileInfo>
#include <QFile>
#include <QDataStream>
#include <QDebug>
#include <QFileInfo>
#include <QDate>
#include <QDateTime>
#include <QTime>
CSegyHead::CSegyHead(QString path){
    this->path=path;
    setHdt();
    setHns();
    setRecordLength();
    setNtrpr();
}

QDateTime CSegyHead::getDateTime(int i){
    char *buffersu;
    buffersu =getSu(i);//获得道头
    char year[2] = {buffersu[156] , buffersu[157]};
    unsigned short *year_u_short = (unsigned short *)year;
    char day[2] = {buffersu[158] , buffersu[159]};
    unsigned short *day_u_short = (unsigned short *)day;
    char hour[2] = {buffersu[160] , buffersu[161]};
    unsigned short *hour_u_short = (unsigned short *)hour;
    char min[2] = {buffersu[162] , buffersu[163]};
    unsigned short *min_u_short = (unsigned short *)min;
    char sec[2] = {buffersu[164] , buffersu[165]};
    unsigned short *sec_u_short = (unsigned short *)sec;
//    qDebug()<<*year_u_short<<" "<<*day_u_short<<" "<<*hour_u_short<<" "<<*min_u_short<<" "<<*sec_u_short;
    delete[] buffersu;
    QDate date(*year_u_short,1,1);
    date = date.addDays(*day_u_short-1);
    QDateTime dateTime(date,QTime(*hour_u_short,*min_u_short,*sec_u_short));
    return dateTime;
}

char* CSegyHead::getSu(int i){
    QFile file(this->path);
    if(file.open(QFile::ReadOnly)){
        qDebug()<<"open success!";
        QDataStream in(&file);
        char *buffersu = new char[240];//存入道头的缓存
        for(int i=0;i<240;i++)
            buffersu[i]=0;
        file.seek(3600+(240+hns*4)*i);
        in.setVersion(QDataStream::Qt_5_5);
        in.readRawData(buffersu,240);
        return buffersu;
    }
}

char* CSegyHead::getReel(){
    QFile file(this->path);
    if(file.open(QFile::ReadOnly)){
        qDebug()<<"open success!";
        QDataStream in(&file);
        char *bufferReel = new char[3600];//存入卷头的缓存
        for(int i=0;i<3600;i++)
            bufferReel[i]=0;
        file.seek(0);
        in.setVersion(QDataStream::Qt_5_5);
        in.readRawData(bufferReel,3600);
        return bufferReel;
    }
}

void CSegyHead::setHdt(){
    char *bufferReel;
    bufferReel =getReel();//获得卷头
    char hdtChar[2] = {bufferReel[3216] , bufferReel[3217]};
    unsigned short *hdt_u_short = (unsigned short *)hdtChar;
    this->hdt = *hdt_u_short;
}

void CSegyHead::setHns(){
    char *bufferReel;
    bufferReel =getReel();//获得卷头
    char hnsChar[2] = {bufferReel[3220] , bufferReel[3221]};
    unsigned short *hns_u_short = (unsigned short *)hnsChar;
    this->hns = *hns_u_short;
}

void CSegyHead::setRecordLength(){
    this->recordLength=this->hns*this->hdt;
}

void CSegyHead::setNtrpr(){
    QFileInfo fileInfo(this->path);
    qint64 fileSize = fileInfo.size();
    ntrpr = (fileSize-3600)/(240+hns*4);
    qDebug()<<"ntrpr"<<ntrpr;
}

unsigned short CSegyHead::getHdt(){
    return this->hdt;
}

unsigned short CSegyHead::getHns(){
    return this->hns;
}

unsigned short CSegyHead::getRecordLength(){
    return recordLength;
}
unsigned short CSegyHead::getNtrpr(){
    return this->ntrpr;
}
