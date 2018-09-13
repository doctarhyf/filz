#include "dialogloading.h"
#include "ui_dialogloading.h"


DialogLoading::DialogLoading(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogLoading)
{
    setWindowFlags(Qt::SplashScreen);
    setWindowTitle("Processing ...");
    ui->setupUi(this);
    currentFileName = "...";


}

DialogLoading::~DialogLoading()
{
    delete ui;
}

void DialogLoading::setProgress(int count, int total)
{
    ui->progressBar->setMaximum(total);
    ui->progressBar->setValue(count);

    int prog = 0;
    if(count > 0){
        prog = count * 100/total;
    }

    ui->labelProg->setText("<b>" + QVariant::fromValue(prog).toString() + "%</b>");

    int strLimit = 47;
    QString cfn = currentFileName.right(strLimit);
    QString ldots = "";

    if(strLimit < currentFileName.length()) ldots = "...";

    ui->labelCurrentFile->setText("Copying : <b>" + ldots + cfn + "</b>");

}

void DialogLoading::onCurrentFileNameChanged(QString newCurrentFileName)
{
    //qDebug() << "DA NEW CUR FILE : " << newCurrentFileName;
    currentFileName = newCurrentFileName;

}
