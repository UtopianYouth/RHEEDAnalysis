#ifndef DETECT_INFO_CANVAS_H
#define DETECT_INFO_CANVAS_H
#include <QWidget>
#include <QBitmap>
#include <QLabel>

class DetectInfoCanvas: public QWidget {
    Q_OBJECT
public:
    explicit DetectInfoCanvas();
    ~DetectInfoCanvas();
    void paintEvent(QPaintEvent *event) override;
    void setTextInfo(QString txt);
    void setImage(QPixmap &image);

private:
    QString text_info = QString::fromLocal8Bit("OpenCV");
    QPixmap pixmap;
    QLabel* image_label{nullptr};
};


#endif // DETECT_INFO_CANVAS_H
