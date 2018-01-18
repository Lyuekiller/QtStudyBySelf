#include "widget.h"
#include "ui_widget.h"
#include "getallfiles.h"

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

    for(int i=0;i<fileInfoList.size();i++){//遍历fileInfoList
        QFileInfo fileInfo= fileInfoList.at(i);
        qDebug()<<fileInfo.filePath();
    }
}
