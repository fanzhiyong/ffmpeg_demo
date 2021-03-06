﻿#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    m_player = new FFmpegPlayer(this);
    ui->verticalLayout->insertWidget(0, m_player);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_playBtn_clicked()
{
    m_player->play("d:/k2.mp4");
}

void Widget::on_stopBtn_clicked()
{
    m_player->stop();
}

void Widget::on_pauseBtn_clicked()
{
    m_player->pause();
}

void Widget::on_horizontalSlider_sliderMoved(int position)
{
    qInfo()<<"Slider: move: "<<position;
}

void Widget::on_infoBtn_clicked()
{
    qInfo()<<"duration ms: "<<m_player->getLength();
}
