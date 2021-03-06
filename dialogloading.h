#ifndef DIALOGLOADING_H
#define DIALOGLOADING_H

#include <QDialog>
#include <QtDebug>

namespace Ui {
class DialogLoading;
}

class DialogLoading : public QDialog
{
    Q_OBJECT

public:
    explicit DialogLoading(QWidget *parent = 0);
    ~DialogLoading();
    void setProgress(int count, int total);

private:
    Ui::DialogLoading *ui;
    QString currentFileName;

public slots:
    void onCurrentFileNameChanged(QString newCurrentFileName);
};

#endif // DIALOGLOADING_H
