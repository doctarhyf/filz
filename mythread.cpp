#include "mythread.h"

MyThread::MyThread(QObject *parent) :
    QThread(parent)
{
    stop = false;
}

MyThread::MyThread(QObject *parent,bool newRemoveFilesAfterSort, const QStringList &newExtsSplits, const QString &newDirPath, const QMap<QString, QStringList> &newFoldersHash)
{
    stop = false;
    this->setParent(parent);
    this->extsSplits = newExtsSplits;
    this->dirPath = newDirPath;
    this->foldersHash = newFoldersHash;
    this->removeFilesAfterSort = newRemoveFilesAfterSort;
}

void MyThread::run()
{


    QDate date = QDate::currentDate();
    QString bcpFileName = date.toString().replace(" ","_") + ".txt";

    QFile bcpFile(bcpFileName);

    bool bcpOpened = bcpFile.open(QIODevice::ReadWrite);

    for(int i = 0; i < extsSplits.length(); i++){
            QStringList folderExts = extsSplits.at(i).split(",");
            QString dirName = folderExts.at(0);
            QString extsStr = folderExts.at(1);
            QStringList extsList = extsStr.split(" ");

            //QString dirName = dirName;

            QString dp = dirPath + "\\" + dirName;
            QDir dir(dirName);

            if(!dir.exists()){
                dir.mkpath(dp);
            }



            foldersHash.insert(dirName, extsList);
        }

        qDebug() << foldersHash;

        QDir dir(dirPath);

        QFileInfoList list = dir.entryInfoList();

        foreach (QFileInfo info, dir.entryInfoList()) {

            if(!info.isDir()){
                numFilesTotal++;

                qDebug() << "DA FILE : " << info.filePath();

                if(bcpOpened){
                    QTextStream ts(&bcpFile);

                    ts << "Path : " << info.absoluteFilePath() << "," << 0x0 ;
                }


            }


        }

        bcpFile.close();

        qDebug() << "Total File(s) : " << numFilesTotal;


        foreach (QFileInfo fileInfo, list) {

           // qDebug() << "File : " << fileInfo.absoluteFilePath();
            if(!fileInfo.isDir()){
                QFile file(fileInfo.absoluteFilePath());

                QStringList splits = file.fileName().split(".");
                QString realExt = splits[splits.length() - 1];
                QString folder = getFileFolder(realExt);

                QStringList pathSplits = file.fileName().split("/");
                QString fname = pathSplits.at(pathSplits.size() - 1);

                pathSplits.removeLast();
                QString newPath = pathSplits.join("/") + "/" + folder + "/";






                if(file.open(QIODevice::ReadWrite)){

                    newPath += fname;
                    QFile nfile(newPath);

                    if(nfile.open(QIODevice::ReadWrite)){

                        emit onNewCurrentFileName(newPath);

                        nfile.write(file.readAll());

                    }else{
                        emit errorCopyingFile(newPath);
                        qDebug() << "Error copying new file : " << newPath;
                    }
                    nfile.flush();
                    nfile.close();


                    if(removeFilesAfterSort){
                        file.remove();
                    }

                    numFilesCopied ++;






                    emit onProgress(numFilesCopied, numFilesTotal);

                    if(numFilesCopied == numFilesTotal){
                        emit onFileCopyFinished();
                        numFilesCopied = numFilesTotal = 0;

                    }

                    //qDebug() << "Progress : " << numFilesCopied << "/" << numFilesTotal;

                    //qDebug() << "new path : " << newPath <<  ", file name : " << fname <<  ", real ext : " << realExt << ", folder : " << folder;
                }

                file.close();


            }


        }

        //emit onFileCopyFinished;
}


QString MyThread::getFileFolder(const QString &ext)
{
    QString folder = "OTHER";
    int i = 0;
    QList<QString> keys = foldersHash.keys();

    foreach (QStringList exts, foldersHash) {

        if(exts.indexOf(ext) != -1){
            folder = keys.at(i);
        }

        i++;
    }

    return folder;
}

bool MyThread::getRemoveFilesAfterSort() const
{
    return removeFilesAfterSort;
}

void MyThread::setRemoveFilesAfterSort(bool value)
{
    removeFilesAfterSort = value;
}

QMap<QString, QStringList> MyThread::getFoldersHash() const
{
    return foldersHash;
}

void MyThread::setFoldersHash(const QMap<QString, QStringList> &value)
{
    foldersHash = value;
}

QString MyThread::getDirPath() const
{
    return dirPath;
}

void MyThread::setDirPath(const QString &value)
{
    dirPath = value;
}

QStringList MyThread::getExtsSplits() const
{
    return extsSplits;
}

void MyThread::setExtsSplits(const QStringList &value)
{
    extsSplits = value;
}
