#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void about_info_show();
    void return_mainwindow();
    void go_rheed_image_handle_view();
    void go_rheed_video_handle_view();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
