#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QtCore>
#include <QThread>
#include <QtDebug>
#include <QObject>
#include <QMessageBox>

class MyThread : public QThread
{

    Q_OBJECT

public:
    explicit MyThread(QObject *parent=0);
    explicit MyThread(QObject *parent,bool newRemoveFilesAfterSort, const QStringList& newExtsSplits, const QString& newDirPath, const QMap<QString, QStringList>& newFoldersHash);
    void run();
    bool stop;

    QStringList getExtsSplits() const;
    void setExtsSplits(const QStringList &value);

    QString getDirPath() const;
    void setDirPath(const QString &value);

    QMap<QString, QStringList> getFoldersHash() const;
    void setFoldersHash(const QMap<QString, QStringList> &value);

    bool getRemoveFilesAfterSort() const;
    void setRemoveFilesAfterSort(bool value);

private:
    QString getFileFolder(const QString& ext);
    QStringList extsSplits;
    QString dirPath;
    QMap<QString, QStringList> foldersHash;
    int numFilesTotal = 0, numFilesCopied = 0;
    bool removeFilesAfterSort;

signals:
    void onFileCopyFinished();
    void onProgress(int count, int total);
    void errorCopyingFile(const QString& newFilePath);
    void onNewCurrentFileName(const QString& newCurrentFileName);

protected:

};

#endif // MYTHREAD_H
