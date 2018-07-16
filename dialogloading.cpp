#include "dialogloading.h"
#include "ui_dialogloading.h"

DialogLoading::DialogLoading(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogLoading)
{
    ui->setupUi(this);
}

DialogLoading::~DialogLoading()
{
    delete ui;
}
