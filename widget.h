#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDir>
#include <QtDebug>
#include <QFileDialog>
#include <QtGui>
#include <QFileSystemModel>
#include <QMessageBox>
#include <QTableWidgetItem>
#include "dialogloading.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButton_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_lineEdit_returnPressed();

    void on_pushButtonSort_clicked();

private:
    void sort();
    void loadExts();
    void loadDirPath();
    QMap<QString, QStringList> foldersHash;
    QString getFileFolder(const QString& ext);
    Ui::Widget *ui;
    QString dirPath;
    QFileSystemModel *fileSysModel;
    QStringList extsSplits;
    DialogLoading* dialogLoading;

};

#endif // WIDGET_H
