#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui/rheed_image_handle_ui.h"
#include "ui/rheed_video_handle_ui.h"
#include "ui/card_layout_panel.h"
#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QPixmap>
#include <QTabWidget>
#include <QMenuBar>     // 菜单栏
#include <QToolBar>     // 工具栏
#include <QTabWidget>   // 标签栏
#include <QMessageBox>
#include <opencv2/opencv.hpp>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);      // 注意：这段代码必须写第一行

    // 创建菜单栏，只能在 QMainwindow 中创建
    QMenuBar* menu_bar = new QMenuBar();
    this->setMenuBar(menu_bar);
    // 创建菜单选项
    QMenu* help_menu = new QMenu(tr("帮助"),this);
    // 为菜单选项添加响应
    QAction* about_action = new QAction(tr("关于"), this);
    help_menu->addAction(about_action);

    // 创建工具栏
    QToolBar* toolbar = new QToolBar("custom toolbar");
    this->addToolBar(toolbar);
    QAction* icon_about_action = new QAction(QIcon(":/images/help_icon.png"),tr("显示作者信息"),this);
    toolbar->addAction(icon_about_action);

    // 主界面卡片布局
    CardLayoutPanel* card_layout_panel = new CardLayoutPanel();
    QAction* return_action = new QAction(tr("返回主界面"),this);

    QHBoxLayout* hbox = new QHBoxLayout();
    hbox->addWidget(card_layout_panel);
    this->ui->centralwidget->setLayout(hbox);

    this->setWindowTitle("RHEED 图像分析");

    this->addAction(return_action);
    this->setContextMenuPolicy(Qt::ActionsContextMenu);     // 右击选项
    this->setFixedSize(1700,1200);

    connect(about_action,SIGNAL(triggered()),this,SLOT(about_info_show()));
    connect(icon_about_action,SIGNAL(triggered()),this,SLOT(about_info_show()));
    connect(card_layout_panel->rheed_image_button,SIGNAL(clicked()),this,SLOT(go_rheed_image_handle_view()));
    connect(card_layout_panel->rheed_video_button,SIGNAL(clicked()),this,SLOT(go_rheed_video_handle_view()));
    connect(return_action,SIGNAL(triggered()),this,SLOT(return_mainwindow()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::about_info_show(){
    QMessageBox::information(this,tr("关于"),"版权所有人 @ UtopianYouth");
}

void MainWindow::go_rheed_image_handle_view(){
    RHEEDImageHandleView* rheed_image_handle_view = new RHEEDImageHandleView();
    this->setCentralWidget(rheed_image_handle_view);
    this->setWindowTitle("RHEED 图像分析");
}

void MainWindow::go_rheed_video_handle_view(){
    RHEEDVideoHandleView* rheed_video_handle_view = new RHEEDVideoHandleView();
    this->setCentralWidget(rheed_video_handle_view);
    this->setWindowTitle("RHEED 视频序列分析");
}

void MainWindow::return_mainwindow(){
    CardLayoutPanel* card_layout_panel = new CardLayoutPanel();

    connect(card_layout_panel->rheed_image_button,SIGNAL(clicked()),this,SLOT(go_rheed_image_handle_view()));
    connect(card_layout_panel->rheed_video_button,SIGNAL(clicked()),this,SLOT(go_rheed_video_handle_view()));
    this->setCentralWidget(card_layout_panel);
    this->setWindowTitle("RHEED 图像数据处理软件");
}

