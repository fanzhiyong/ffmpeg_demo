#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include "ffmpegcore.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_chooseBtn_clicked()
{
    QString path = ui->filePathEdit->text();
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                      path,
                                                      tr("Video (*.*)"));
    if( fileName.isEmpty() ) return;

    ui->filePathEdit->setText(fileName);
}

void Widget::on_loadBtn_clicked()
{
    FFmpegCore * fc = FFmpegCore::getInstance();
    fc->load(getVideoPath());
}

QString Widget::getVideoPath()
{
    return ui->filePathEdit->text();
}
