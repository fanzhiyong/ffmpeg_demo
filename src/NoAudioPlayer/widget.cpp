#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    m_show = new SDLShow(this);
    //ui->verticalLayout->addWidget();
}

Widget::~Widget()
{
    delete ui;
}
