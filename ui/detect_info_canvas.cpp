#include "ui/detect_info_canvas.h"
#include <QPainter>
#include <iostream>
#include <QHBoxLayout>

DetectInfoCanvas::DetectInfoCanvas() {
    std::cout<<"create detect info canvas"<<std::endl;
    this->setFixedSize(800, 600);
    this->image_label = new QLabel();
    this->image_label->setAlignment(Qt::AlignCenter);

    QHBoxLayout* hbox1= new QHBoxLayout();
    hbox1->addWidget(this->image_label);
    this->setLayout(hbox1);
}

DetectInfoCanvas::~DetectInfoCanvas(){
    std::cout<<"destroy detect info canvas"<<std::endl;
}

void DetectInfoCanvas::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QColor(100, 200, 100));

    if(!this->pixmap.isNull()) {
        this->pixmap = this->pixmap.scaled(800,600,Qt::KeepAspectRatio);
        this->image_label->setPixmap(pixmap);
    }

    QFont font;
    font.setBold(true);
    font.setPixelSize(48);
    painter.setFont(font);
}

void DetectInfoCanvas::setTextInfo(QString txt) {
    this->text_info = txt;
    this->repaint();
}

void DetectInfoCanvas::setImage(QPixmap &image) {
    this->pixmap = image;
    this->repaint();
}
