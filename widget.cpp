#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    dialogLoading = new DialogLoading(this);
    dialogLoading->setModal(true);

    dirPath = "C:\\Downloads\\test";


    fileSysModel = new QFileSystemModel;
    fileSysModel->setRootPath(dirPath);
    ui->listView->setModel(fileSysModel);
    loadDirPath();

    ui->lineEdit->setText(dirPath);





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
    QFile file("exts.txt");
    if(file.open(QIODevice::ReadWrite )){
        QFileInfo info(file);
        //qDebug() << "EXT file : " << info.absoluteFilePath();

        QTextStream ts(&file);
        QString extsData = ts.readAll();

        extsSplits = extsData.split("\r\n");
        extsSplits.removeLast();

        ui->labelExts->setText(extsData);




     }else{

        QMessageBox::critical(this,"Error creating exts file", "The exts file could not be created!");
     }

    dialogLoading->hide();
}

void Widget::on_pushButtonSort_clicked()
{
    sort();
}

void Widget::sort()
{

    dialogLoading->show();
    foldersHash.clear();

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
                    nfile.write(file.readAll());

                }else{
                    qDebug() << "Cant create file : " << newPath;
                }
                nfile.flush();
                nfile.close();


                file.remove();
                //qDebug() << "new path : " << newPath <<  ", file name : " << fname <<  ", real ext : " << realExt << ", folder : " << folder;
            }

            file.close();
        }
    }

    dialogLoading->hide();
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
