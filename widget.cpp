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
        QMessageBox::information(this,"Error Message",QString::fromLocal8Bit("没有选择初始文件路径或者目标文件路径,请选择!"));
        return;
    }
    QFileInfoList fileInfoList= GetFileListInSegy(GetFileList(openFileName));//获得文件夹中所有后缀名为sgy文件的文件路径，其中GetFileList(openFileName)是获得所有文件的文件名。
    QList<CSegyHead> segyList;
    for(int i=0;i<fileInfoList.size();i++){//遍历fileInfoList
        QFileInfo fileInfo= fileInfoList.at(i);
        CSegyHead segyHead(fileInfo.filePath());
        segyList<<segyHead;
        qDebug()<<fileInfo.filePath();
    }
    int currentLocation[segyList.size()];
    for(int i=0;i<segyList.size();i++)
        currentLocation[i]=0;
    CSegyHead segyHead_1(segyList.at(16));//获得第一个文件,以第一个文件作为标准
    QDateTime startDateTime = segyHead_1.getDateTime(0);//获得开始时间
    qDebug()<<"the 16 time is"<<startDateTime.toString();
    for(int i=1;i<segyList.size();i++){//以第一个文件为标准,把其他文件调整到正确的时间位置
        if(startDateTime>segyList[i].getDateTime(0)){
            qDebug()<<"the "<<i<<" time is"<<segyList[i].getDateTime(0).toString();
            qint64 court = segyList[i].getDateTime(0).secsTo(startDateTime)/15;
            currentLocation[i]=court;
            qDebug()<<"the corrent time is"<<segyList[i].getDateTime(court).toString();
        }
    }
    for(unsigned short i=0;i<segyList[0].getRecordLength();i++){
        if(startDateTime.isValid()){
            for(int i=1;i<segyList.size();i++){//i=1表明从第二个文件开始比较

            }
        }else{
            QMessageBox::information(this,"Error Message",QString::fromLocal8Bit("第一个文件获取第一个道头发生错误,因为日期读取格式不正确"));
        }

    }
}
