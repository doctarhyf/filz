#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDir>
#include <QtDebug>
#include <QFileDialog>
#include <QtGui>

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

private:
    void loadDirPath();
    Ui::Widget *ui;
    QString dirPath;
};

#endif // WIDGET_H
