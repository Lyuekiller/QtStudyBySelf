#include "widget.h"
#include "ui_widget.h"
#include "getallfiles.h"
#include "segyfile.h"
#include <QDateTime>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->label_2->adjustSize();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    QString openFileName = QFileDialog::getExistingDirectory(this,"Open File",QDir::homePath());
    ui->openLineEdit->setText(openFileName);
}

void Widget::on_targetFileButton_clicked()
{
    QString targetFileName = QFileDialog::getExistingDirectory(this,"Save File",QDir::homePath());
    ui->targetLineEdit->setText(targetFileName);
}

void Widget::on_convertButton_clicked()
{
    QString openFileName = ui->openLineEdit->text();
    QString targetFileName = ui->targetLineEdit->text();
    if(openFileName.isEmpty()||targetFileName.isEmpty()){
        QMessageBox::information(this,"Error Message",QString::fromLocal8Bit("û��ѡ���ʼ�ļ�·������Ŀ���ļ�·��,��ѡ��!"));
        return;
    }
    QFileInfoList fileInfoList= GetFileListInSegy(GetFileList(openFileName));//����ļ��������к�׺��Ϊsgy�ļ����ļ�·��������GetFileList(openFileName)�ǻ�������ļ����ļ�����
    QList<CSegyHead> segyList;
    for(int i=0;i<fileInfoList.size();i++){//����fileInfoList
        QFileInfo fileInfo= fileInfoList.at(i);
        CSegyHead segyHead(fileInfo.filePath());
        segyList<<segyHead;
        qDebug()<<fileInfo.filePath();
    }
    int currentLocation[segyList.size()];
    for(int i=0;i<segyList.size();i++)
        currentLocation[i]=0;
    CSegyHead segyHead_1(segyList.at(16));//��õ�һ���ļ�,�Ե�һ���ļ���Ϊ��׼
    QDateTime startDateTime = segyHead_1.getDateTime(0);//��ÿ�ʼʱ��
    qDebug()<<"the 16 time is"<<startDateTime.toString();
    for(int i=1;i<segyList.size();i++){//�Ե�һ���ļ�Ϊ��׼,�������ļ���������ȷ��ʱ��λ��
        if(startDateTime>segyList[i].getDateTime(0)){
            qDebug()<<"the "<<i<<" time is"<<segyList[i].getDateTime(0).toString();
            qint64 court = segyList[i].getDateTime(0).secsTo(startDateTime)/15;
            currentLocation[i]=court;
            qDebug()<<"the corrent time is"<<segyList[i].getDateTime(court).toString();
        }
    }
    for(unsigned short i=0;i<segyList[0].getRecordLength();i++){
        if(startDateTime.isValid()){
            for(int i=1;i<segyList.size();i++){//i=1�����ӵڶ����ļ���ʼ�Ƚ�

            }
        }else{
            QMessageBox::information(this,"Error Message",QString::fromLocal8Bit("��һ���ļ���ȡ��һ����ͷ��������,��Ϊ���ڶ�ȡ��ʽ����ȷ"));
        }

    }
}
