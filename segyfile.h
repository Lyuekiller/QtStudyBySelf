#ifndef SEGYFILE
#define SEGYFILE

#endif // SEGYFILE

using namespace std;

 class CSegyHead{
 private:
     QString path;//segy文件路径
     short ntrpr;//卷头3213-3214,每个记录的道数
     short nart;//卷头3215-3216,每个记录的辅助道数
     unsigned short hdt;//卷头3215-3216,该卷采样间隔
     unsigned short hns;//卷头3221-3222,该卷每道的采样间隔
     int tracl;//道头1-4,测线中道顺序号
     unsigned short dt;//道头113-114,该道采样点数
     unsigned short ns;//道头115-116,该道的采样间隔
     short year;//道头157-158,年
     short day;//道头159-160,日期
     short hour;//道头161-162,小时
     short minute;//道头163-164,分
     short sec;//道头165-166,秒
 public:
     char *getReel();//获得卷头
     char *getSu();//获得道头
     void reviseReel(int start , int length , QString targetPath);//修改卷头的指定位置
     void reviseSu(int start , int length , QString targetPath);//修改道头的指定位置
     QString getDataTime();
 };
