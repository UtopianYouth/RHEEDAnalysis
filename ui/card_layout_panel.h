#ifndef CARD_LAYOUT_PANEL_H
#define CARD_LAYOUT_PANEL_H

#include<QWidget>
#include<QLabel>
#include<QPushButton>
#include<QPixmap>


// 自定义 Panel
class CardLayoutPanel:public QWidget{
    Q_OBJECT

public:
    CardLayoutPanel();
    ~CardLayoutPanel();
    void initUI();

    // 卡片1
    QPushButton* rheed_image_button{nullptr};
    QPixmap rheed_image_pixmap;
    QLabel* rheed_image_label{nullptr};

    // 卡片2
    QPushButton* rheed_video_button{nullptr};
    QPixmap rheed_video_pixmap;
    QLabel* rheed_video_label{nullptr};
};

#endif // CARD_LAYOUT_PANEL_H
