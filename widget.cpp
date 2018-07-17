#include "widget.h"
#include "ui_widget.h"
#include "mythread.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    mythread = new MyThread();

    dialogLoading = new DialogLoading(this);
    dialogLoading->setModal(true);
    dialogLoading->hide();

    dirPath = "C:\\Downloads\\test";


    fileSysModel = new QFileSystemModel;
    fileSysModel->setRootPath(dirPath);
    ui->listView->setModel(fileSysModel);
    loadDirPath();

    ui->lineEdit->setText(dirPath);

    connect(mythread, SIGNAL(onFileCopyFinished()), this, SLOT(onFileCopyFinished()));
    connect(mythread, SIGNAL(onProgress(int,int)), this, SLOT(onProgress(int,int)));
    connect(mythread, SIGNAL(errorCopyingFile(QString)), this, SLOT(onErrorCopyingFile(QString)));





}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{

    dirPath = QFileDialog::getExistingDirectory(this, "Choose directory ...", ui->lineEdit->text());
    if(dirPath == "") dirPath = ui->lineEdit->text();
    loadDirPath();
}

void Widget::loadDirPath()
{

    dialogLoading->setProgress(0,0);
    dialogLoading->show();
    ui->listView->setRootIndex(fileSysModel->index(dirPath));
    loadExts();

    /*ui->listWidget->clear();
    ui->lineEdit->setText(dirPath);

    QDir dir(dirPath);

    QFileInfoList list = dir.entryInfoList();



    foreach (QFileInfo fileInfo, list) {

        QIcon icon(":/img/ic_folder.png");
        QString baseName = fileInfo.fileName();
        QStringList splits = baseName.split(".");
        QString ext = splits[splits.size() -1 ];

        QString fname = baseName.left(baseName.indexOf(ext));

        qDebug() << fname;

        if(fileInfo.isDir()){
            fname = baseName;
        }else{
            fname = fname + ext;
            QString iconStr = ":/img/";
            QString iconFileName = "ic_raw.png";

           icon = QIcon(iconStr + iconFileName);

        }



        QString isDir = fileInfo.isDir() ? "true" : "false";



        QListWidgetItem* item = new QListWidgetItem(icon, fname);
        ui->listWidget->addItem(item);



    }*/


}


void Widget::on_lineEdit_textChanged(const QString &arg1)
{
    dirPath = arg1;
    //loadDirPath();
}

void Widget::on_lineEdit_returnPressed()
{
    loadDirPath();
}

void Widget::loadExts()
{
    //QFile file("exts.txt");
    /*if(file.open(QIODevice::ReadWrite )){
        QFileInfo info(file);
        //qDebug() << "EXT file : " << info.absoluteFilePath();

        QTextStream ts(&file);*/
        QString extsData = ui->plainTextEdit->toPlainText();

        //qDebug() << "Data : " << extsData;

        //return;



        extsSplits = extsData.split("\n");
        extsSplits.removeLast();

        //ui->labelExts->setText(extsData);




     /*}else{

        QMessageBox::critical(this,"Error creating exts file", "The exts file could not be created!");
     }*/

    dialogLoading->hide();
}

void Widget::on_pushButtonSort_clicked()
{
    sort();
}

void Widget::sort()
{

    int number;
    int randomValue = qrand() % number;

    QString rand = QString::number(randomValue);

    QString tokken = QInputDialog::getText(this, "Confirm sorting", "Type in : "
                                                   "<strong>" + rand + "</strong>");

    if(tokken == rand ){

    dialogLoading->show();
    foldersHash.clear();

    mythread->setDirPath(dirPath);
    mythread->setExtsSplits(extsSplits);
    mythread->setFoldersHash(foldersHash);
    mythread->setRemoveFilesAfterSort(ui->checkBoxRemFiles->isChecked());
    mythread->start();

    }else{
        QMessageBox::warning(this, "Tokken error", "The tokken was wrong, please try again.");
    }



}




QString Widget::getFileFolder(const QString &ext)
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

void Widget::onFileCopyFinished()
{
    qDebug() << "copy finished!";

    QMessageBox::information(this, "Sort Complete", "The sorting has been completed!");
    dialogLoading->hide();
}

void Widget::onProgress(int count, int total)
{
    qDebug() << "Count : " << count << ", total : " << total;
    dialogLoading->setProgress(count, total);

}

void Widget::onErrorCopyingFile(QString newFilePath)
{
    qDebug() << "Error copying to : " << newFilePath;
    QMessageBox::critical(this, "Error copying file", "Error while copying : <strong>" + newFilePath + "</strong>");
}
