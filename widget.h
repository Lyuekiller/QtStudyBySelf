#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFileDialog>
#include <QUrl>
#include <QDir>
#include <QMessageBox>
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

    void on_targetFileButton_clicked();

    void on_convertButton_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
