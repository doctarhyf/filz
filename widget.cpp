#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    dirPath = ".";
    loadDirPath();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{

    dirPath = QFileDialog::getExistingDirectory(this, "Path");
    loadDirPath();
}

void Widget::loadDirPath()
{

    ui->listWidget->clear();
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



    }


}
