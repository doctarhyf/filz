#include "dialogloading.h"
#include "ui_dialogloading.h"

DialogLoading::DialogLoading(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogLoading)
{
    setWindowFlags(Qt::SplashScreen);
    setWindowTitle("Processing ...");
    ui->setupUi(this);
}

DialogLoading::~DialogLoading()
{
    delete ui;
}

void DialogLoading::setProgress(int count, int total)
{
    ui->progressBar->setMaximum(total);
    ui->progressBar->setValue(count);
}
