#include "tcpthread.h"
#include <QtGui>
#include <QtNetwork>
#include <QDebug>
#include <QDir>
#include <QProcess>
#include <QFile>

TcpThread::TcpThread(int socketDescriptor, QObject *parent) :
    QThread(parent),socketDescriptor(socketDescriptor)
{
    loadSize = 4*1024;
    QString location = QDir::currentPath() + "/EGRET_POOL"; qDebug()<<location;
    QDir().setCurrent(location);
}

void TcpThread::run()
{
     socket = new QTcpSocket;
     if (!socket->setSocketDescriptor(socketDescriptor)) {
         emit error(socket->error());
         return;
     }

     fileContentBytes = 0;
     bytesWritten = 0;
     connect(socket, SIGNAL(readyRead()), this, SLOT(receiveFile()), Qt::DirectConnection);
     connect(socket,SIGNAL(bytesWritten(qint64)),this,SLOT(updateTransfer(qint64)), Qt::DirectConnection);

     exec();
}

void TcpThread::receiveFile()
{
     if( fileContentBytes == 0 ) {
         QDataStream stream( socket );
         stream.setVersion( QDataStream::Qt_4_0 );

         if( socket->bytesAvailable() < sizeof(qint32) )
              return;
         stream >> fileNameBytes;
         //qDebug()<<fileNameBytes;

         if( socket->bytesAvailable() < fileNameBytes )
              return;
         stream >> fileName;
         //qDebug()<<fileName;

         if( socket->bytesAvailable() < sizeof(qint32) )
              return;
         stream >> commandBytes;
         //qDebug()<<commandBytes;

         if( socket->bytesAvailable() < commandBytes )
              return;
         stream >> command;
         //qDebug()<<command;

         if( socket->bytesAvailable() < sizeof(qint32) )
              return;
         stream >> fileContentBytes;
         //qDebug()<<fileContentBytes;
     }

     if( fileContentBytes > socket->bytesAvailable() )
         return;

     if (command == "Upload File") {
         saveFile();
         qDebug()<<tr("Save File %1").arg(fileName);
         //socket->write("this is the feedback!");
     }
     else if (command == "Calculation and Feedback Result") {
         saveFile();
         //QString command = "EGRET.exe -i " + location + "/" + fileName;
         QString command = "EGRET.exe -i " + fileName;
         QProcess *egretCalculating = new QProcess();
         egretCalculating->start(command);
         if (egretCalculating->waitForFinished(600000)) {
             qDebug()<<"Finished Calculation!";
        }

         //socket->write( getSendFileContent(fileName) );
         startTransfer();
     }
     else {
         qDebug()<<"Unknown Command";
     }

}

void TcpThread::saveFile() {
    QByteArray array = socket->read( fileContentBytes );
    //QFile file(tr("EGRET_POOL/%1").arg(fileName));
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        return;
    }
    file.write(array);
    file.close();
}

void TcpThread::startTransfer()  //实现文件大小等信息的发送
{
     QString name = fileName + ".out";
     localFile = new QFile(name);
     qDebug()<<QDir().currentPath()<<name;
     if(!localFile->open(QFile::ReadOnly)) {
         qDebug() << "open file error!";
         return;
     }
     //QByteArray filedata; filedata = localFile->readAll();
     //文件总大小
     totalBytes = localFile->size();
     QDataStream sendOut(&outBlock,QIODevice::WriteOnly);
     sendOut.setVersion(QDataStream::Qt_4_0);
     QString currentFileName = name;//.right(fileName.size() - fileName.lastIndexOf('/')-1);

     //依次写入件名大小信息空间，文件名, 文件总大小信息空间
     sendOut << qint32(0) << currentFileName << qint32(totalBytes);
     //这里的总大小是文件名大小等信息和实际文件大小的总和
     sendOut.device()->seek(0);
     //返回outBolock的开始，用实际的大小信息代替两个qint64(0)空间
     sendOut<<qint32((outBlock.size() - sizeof(qint32)*2));
     totalBytes += outBlock.size();
     //outBlock.append(filedata);
     //socket->write(outBlock);
     //发送完头数据后剩余数据的大小
     socket->write(outBlock);
     qDebug()<< qint32((outBlock.size() - sizeof(qint32)*2)) << currentFileName << qint32(totalBytes);
     bytesToWrite = totalBytes - outBlock.size();
     outBlock.resize(0);
     /*for (int i=0; i<1000; i++) {
         updateTransfer(1024*3);
     }*/
}

void TcpThread::updateTransfer(qint64 numBytes)
{
    QString name = fileName + ".out";
    //已经发送数据的大小
    bytesWritten += (int)numBytes;
    if(bytesToWrite > 0) //如果已经发送了数据
    {
         //每次发送loadSize大小的数据，这里设置为4KB，如果剩余的数据不足4KB，
         //就发送剩余数据的大小
         outBlock = localFile->read(qMin(bytesToWrite,loadSize));
         //发送完一次数据后还剩余数据的大小
         socket->write(outBlock);
         bytesToWrite -= (outBlock.size());
         //清空发送缓冲区
         outBlock.resize(0);
     }
     else {
         localFile->close(); //如果没有发送任何数据，则关闭文件
     }

    if(bytesWritten == totalBytes) //发送完毕
    {
         qDebug()<<(tr("Transfer %1 successfully!").arg(name));
         localFile->close();
    }
}
