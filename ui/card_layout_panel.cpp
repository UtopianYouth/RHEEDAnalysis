#include "ui/card_layout_panel.h"
#include <iostream>
#include <QGridLayout>


CardLayoutPanel::CardLayoutPanel(){
    std::cout<<"create card layout panel"<<std::endl;

    // 初始化成员变量
    this->rheed_image_button = new QPushButton("图像数据处理");
    this->rheed_image_pixmap = QPixmap(":/images/image_icon.png");
    this->rheed_image_label = new QLabel();

    this->rheed_video_button = new QPushButton("视频数据处理");
    this->rheed_video_pixmap = QPixmap(":/images/video_icon.png");
    this->rheed_video_label = new QLabel();

    // 初始化 UI
    this->initUI();
}

CardLayoutPanel::~CardLayoutPanel(){
    std::cout<<"destroy card layout panel"<<std::endl;
}

void CardLayoutPanel::initUI(){

    this->rheed_image_button->setFixedSize(128,68);
    this->rheed_image_button->setStyleSheet("background: rgb(47,192,212); color: black");
    this->rheed_video_button->setFixedSize(128,68);
    this->rheed_video_button->setStyleSheet("background: rgb(47,192,212); color: black");

    QGridLayout* grid1 = new QGridLayout();

    QWidget* card1 = new QWidget();
    QVBoxLayout* vbox1 = new QVBoxLayout();

    QPixmap pixmap1 = this->rheed_image_pixmap.scaled(QSize(128,128),Qt::KeepAspectRatio);
    this->rheed_image_label->setPixmap(pixmap1);
    vbox1->addWidget(this->rheed_image_label);
    vbox1->addWidget(rheed_image_button);
    vbox1->addStretch(1);
    card1->setLayout(vbox1);

    QWidget* card2 = new QWidget();
    QVBoxLayout* vbox2 = new QVBoxLayout();

    QPixmap pixmap2 = this->rheed_video_pixmap.scaled(QSize(128,128),Qt::KeepAspectRatio);
    this->rheed_video_label->setPixmap(pixmap2);
    vbox2->addWidget(this->rheed_video_label);
    vbox2->addWidget(rheed_video_button);
    vbox2->addStretch(1);
    card2->setLayout(vbox2);

    grid1->addWidget(card1,0,0,Qt::AlignCenter);
    grid1->addWidget(card2,0,1,Qt::AlignCenter);

    this->setLayout(grid1);
}

