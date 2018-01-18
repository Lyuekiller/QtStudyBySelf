#ifndef GETALLFILES
#define GETALLFILES

#endif // GETALLFILES

#include <QStringList>
#include <QFileInfoList>
#include <QFileInfo>
#include <QDir>
#include <QDebug>

//��ȡ�ļ����°������ļ��������е��ļ���������QFileInfoList���ط����ȡ�ļ�����Ϣ��
QFileInfoList GetFileList(QString path)
{
    QDir dir(path);
    QFileInfoList file_list = dir.entryInfoList(QDir::Files | QDir::Hidden | QDir::NoSymLinks);//entryInfoList�ǻ��dirĿ¼�����е��ļ���QFileInfoList���󷵻�
    QFileInfoList folder_list = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);

    for(int i = 0; i != folder_list.size(); i++)
    {
         QString name = folder_list.at(i).absoluteFilePath();
         QFileInfoList child_file_list = GetFileList(name);
         file_list.append(child_file_list);
    }
    return file_list;
}


QFileInfoList GetFileListInSegy(QFileInfoList filelist){
    QFileInfo fileInfo;
    QFileInfoList sgyFileList;
    for(int i=0;i<filelist.size();i++){
        fileInfo = filelist.at(i);
        if(fileInfo.suffix()=="sgy"){
            sgyFileList<<fileInfo;
        }
    }
    return sgyFileList;
}
