#ifndef SEGYFILE
#define SEGYFILE

#endif // SEGYFILE

using namespace std;

 class CSegyHead{
 private:
     QString path;//segy�ļ�·��
     short ntrpr;//��ͷ3213-3214,ÿ����¼�ĵ���
     short nart;//��ͷ3215-3216,ÿ����¼�ĸ�������
     unsigned short hdt;//��ͷ3215-3216,�þ�������
     unsigned short hns;//��ͷ3221-3222,�þ�ÿ���Ĳ������
     int tracl;//��ͷ1-4,�����е�˳���
     unsigned short dt;//��ͷ113-114,�õ���������
     unsigned short ns;//��ͷ115-116,�õ��Ĳ������
     short year;//��ͷ157-158,��
     short day;//��ͷ159-160,����
     short hour;//��ͷ161-162,Сʱ
     short minute;//��ͷ163-164,��
     short sec;//��ͷ165-166,��
 public:
     char *getReel();//��þ�ͷ
     char *getSu();//��õ�ͷ
     void reviseReel(int start , int length , QString targetPath);//�޸ľ�ͷ��ָ��λ��
     void reviseSu(int start , int length , QString targetPath);//�޸ĵ�ͷ��ָ��λ��
     QString getDataTime();
 };
