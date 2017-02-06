#ifndef TCPTHREAD_H
#define TCPTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QtNetwork>

class TcpThread : public QThread
{
    Q_OBJECT
public:
    TcpThread(int socketDescriptor, QObject *parent);
    void run();

    QString fileName, command;
    QString outFileName, outCommand;
    qint32 fileNameBytes, commandBytes, fileContentBytes;
    qint32 outFileNameBytes, outCommandBytes, outFileContentBytes;
    int bytesWritten, bytesToWrite, totalBytes;
    QFile *localFile;

signals:
    void error(QTcpSocket::SocketError socketError);
    void bytesArrived(qint64,qint32,int);

public slots:
    void receiveFile();
    void updateTransfer(qint64 numBytes);

private:
    int socketDescriptor;
    QTcpSocket *socket;
    void saveFile();
    QByteArray getSendFileContent(QString name);
    void startTransfer();
    QByteArray outBlock;
    int loadSize;
};

#endif // TCPTHREAD_H
