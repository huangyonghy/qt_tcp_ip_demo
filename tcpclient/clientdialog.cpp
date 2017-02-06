/*
 * Copyright (c) 2006-2007, Johan Thelin
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 * 
 *     * Redistributions of source code must retain the above copyright notice, 
 *       this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright notice,  
 *       this list of conditions and the following disclaimer in the documentation 
 *       and/or other materials provided with the distribution.
 *     * Neither the name of APress nor the names of its contributors 
 *       may be used to endorse or promote products derived from this software 
 *       without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <QBuffer>
#include <QString>
#include <QFileDialog>
#include <QDebug>
#include <QDir>

#include "clientdialog.h"

ClientDialog::ClientDialog() : QDialog()
{
  ui.setupUi( this );
  
  connect( ui.choosePushButton, SIGNAL(clicked()), this, SLOT(chooseClicked()) );
  connect( ui.filePushButton, SIGNAL(clicked()), this, SLOT(commitClicked()) );

  inFileContentBytes = 0;

}

void ClientDialog::commitClicked()
{
  ui.filePushButton->setEnabled( false );
  
  //socket->abort();
  socket = new QTcpSocket;
  connect( socket, SIGNAL(readyRead()), this, SLOT(receiveFile()));
  //socket.connectToHost( "192.168.1.128", 9876 );
  socket->connectToHost( ui.ipLineEdit->text(), ui.pnLineEdit->text().toInt() );

  QString name = ui.fileLineEdit->text(); fileName = name.right(name.size() - name.lastIndexOf('/') - 1);
  command = ui.comboBox->currentText();
  if(name != NULL) {
      QFile file(name);
      if (!file.open(QFile::ReadOnly )) { //读取发送文件
          return;
      }

      QByteArray filedata; filedata = file.readAll();
      QByteArray trData;
      fileContentBytes = filedata.size();

      QDataStream stream( &trData, QIODevice::WriteOnly ); qDebug()<<trData.size()<<sizeof(qint32)<<sizeof(QString)<<sizeof(quint32);
      stream.setVersion( QDataStream::Qt_4_0 );
      //fileNameBytes = (qint32)sizeof(fileName); commandBytes= (qint32)sizeof(command); totalBytes = (qint32)filedata.size() + fileNameBytes + commandBytes;
      stream<<qint32(0)<<QString("Hello1"); qDebug()<<trData;
      stream<<fileName; int temp1 = trData.size(); qDebug()<<trData<<temp1<<sizeof(fileName);
      stream.device()->seek(0);
      stream<<qint32(temp1-sizeof(qint32))<<fileName<<qint32(0)<<command<<qint32(fileContentBytes);

      int temp2 = trData.size(); qDebug()<<temp2;
      stream.device()->seek(0);
      stream<<qint32(temp1-sizeof(qint32))<<fileName<<qint32(temp2-temp1-sizeof(qint32)*2)<<command<<qint32(fileContentBytes);


      trData.append( filedata );
      socket->write(trData);
      /*localfile = new QFile(tr("EGRET_POOL/feedback"));
      if (!localfile->open(QIODevice::WriteOnly)) {
          return;
      }*/
  }
  else {
      return;
  }
}

void ClientDialog::chooseClicked()
{
    QString name = QFileDialog::getOpenFileName(this, "choose EGRET output file", "../");
    if (name != NULL) {
        ui.fileLineEdit->setText(name);
    }
    if (name == NULL) {
        return;
    }
}

void ClientDialog::on_fileLineEdit_textChanged(const QString &arg1)
{
    ui.filePushButton->setEnabled( true );
}

void ClientDialog::receiveFile(){
    //QByteArray line=socket->readAll();
    //localfile->write(line);
    //file.close();*/
    //qDebug()<<line;
    if( inFileContentBytes == 0 ) {
        QDataStream stream( socket );
        stream.setVersion( QDataStream::Qt_4_0 );

        if( socket->bytesAvailable() < sizeof(qint32) )
             return;
        stream >> inFileNameBytes;
        qDebug()<<inFileNameBytes;

        if( socket->bytesAvailable() < inFileNameBytes )
             return;
        stream >> inFileName;
        qDebug()<<inFileName;

        if( socket->bytesAvailable() < sizeof(qint32) )
             return;
        stream >> inFileContentBytes;
        qDebug()<<inFileContentBytes;
    }

    if( inFileContentBytes > socket->bytesAvailable() )
        return;

    QByteArray array = socket->read( inFileContentBytes );
    QString dir = QDir::currentPath();
    QFile file(dir + tr("/EGRET_POOL/%1").arg(inFileName));
    if (!file.open(QIODevice::WriteOnly)) {
        return;
    }
    file.write(array);
    file.close();
    inFileContentBytes = 0;
}
