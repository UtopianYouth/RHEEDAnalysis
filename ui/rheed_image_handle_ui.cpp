#include <QFont>
#include <QImage>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QFileDialog>
#include <QMessageBox>
#include <iostream>
#include <QApplication>
#include<QHeaderView>
#include "ui/rheed_image_handle_ui.h"

RHEEDImageHandleView::RHEEDImageHandleView(){
    // 初始化成员属性
    // 模型选择部分
    this->weight_file_path = new QLineEdit();
    this->label_file_path = new QLineEdit();
    this->weight_file_button = new QPushButton("输入");
    this->label_file_button = new QPushButton("输入");

    // 图像文字部分
    this->fps = new QCheckBox("显示FPS");
    this->count = new QCheckBox("显示条纹数量");

    // 数据加载部分
    this->image_path = new QLineEdit();
    this->image_select_button = new QPushButton("文件夹选择");
    this->image_num_label = new QLabel();

    // 显示部分
    this->image_canvas = new DetectInfoCanvas();

    // 图像浏览部分
    auto icon1 = QApplication::style()->standardIcon(QStyle::SP_ArrowLeft);
    auto icon2 = QApplication::style()->standardIcon(QStyle::SP_ArrowRight);
    this->go_front_button = new QPushButton(icon1,"");
    this->go_next_button = new QPushButton(icon2,"");
    this->image_label = new QLabel();

    // 表格部分
    this->table_view = new QTableView();
    this->table_model = new QStandardItemModel();
    this->table_view->setModel(this->table_model);

    // 运行按钮
    this->start_detect_button = new QPushButton();

    this->initUI();

    std::cout<<"create rheed image handle view"<<std::endl;
}

RHEEDImageHandleView::~RHEEDImageHandleView(){
    std::cout<<"destroy rheed image handle view"<<std::endl;
}

void RHEEDImageHandleView::initUI(){

    this->weight_file_path->setReadOnly(true);
    this->label_file_path->setReadOnly(true);
    this->image_path->setReadOnly(true);

    this->weight_file_path->setFixedWidth(400);
    this->label_file_path->setFixedWidth(400);
    this->image_path->setFixedWidth(350);

    this->start_detect_button->setFixedSize(158,48);
    this->go_front_button->setFixedSize(158,48);
    this->go_next_button->setFixedSize(158,48);
    this->start_detect_button->setIcon(QIcon(":/images/image_icon.png"));

    std::string image_num = std::to_string(this->image_paths.size());
    this->image_num_label->setText(QString::fromStdString(image_num));
    this->image_label->setFixedSize(800,600);
    this->image_label->setAlignment(Qt::AlignCenter);

    // 交替行颜色
    this->table_view->setAlternatingRowColors(true);
    // 填充整个表格
    this->table_view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->table_view->horizontalHeader()->setStyleSheet("font-weight: bold");
    this->table_model->setHorizontalHeaderLabels({"x", "y", "width", "height", "area"});

    QGridLayout* grid1 = new QGridLayout();
    QGroupBox* panel1 = new QGroupBox("模型");
    grid1->addWidget(new QLabel("权重文件路径："),0,0);
    grid1->addWidget(this->weight_file_path,0,1);
    grid1->addWidget(this->weight_file_button,0,2);
    grid1->addWidget(new QLabel("标签文件路径："),1,0);
    grid1->addWidget(this->label_file_path,1,1);
    grid1->addWidget(this->label_file_button,1,2);
    panel1->setLayout(grid1);

    QGridLayout* grid2 = new QGridLayout();
    QGroupBox* panel2 = new QGroupBox("显示内容");
    grid2->addWidget(this->fps,0,0);
    grid2->addWidget(this->count,0,1);
    panel2->setLayout(grid2);


    QWidget* panel3 = new QGroupBox("图像文件夹信息");
    QHBoxLayout* hbox3 = new QHBoxLayout();
    hbox3->addWidget(new QLabel("图像文件路径："));
    hbox3->addWidget(this->image_path);
    hbox3->addWidget(this->image_select_button);
    hbox3->addStretch(1);
    hbox3->addWidget(new QLabel("图像总数："));
    hbox3->addWidget(this->image_num_label);
    hbox3->addStretch(1);
    panel3->setLayout(hbox3);

    QGroupBox* panel7 = new QGroupBox("原图");
    QHBoxLayout* hbox4 = new QHBoxLayout();
    hbox4->addStretch(1);
    hbox4->addWidget(this->image_label);
    hbox4->addStretch(1);
    panel7->setLayout(hbox4);

    QGridLayout* grid3= new QGridLayout();
    QWidget* panel5 = new QWidget();
    grid3->addWidget(this->go_front_button,0,0);
    grid3->addWidget(this->start_detect_button,0,1);
    grid3->addWidget(this->go_next_button,0,2);
    panel5->setLayout(grid3);

    QWidget* panel6 = new QWidget();
    QVBoxLayout* vbox1 = new QVBoxLayout();
    vbox1->setAlignment(Qt::AlignHCenter);
    vbox1->addWidget(panel1);
    vbox1->addWidget(panel2);
    vbox1->addWidget(panel3);
    vbox1->addWidget(panel7);
    vbox1->addWidget(panel5);
    vbox1->addStretch(1);
    panel6->setLayout(vbox1);


    QGroupBox* panel8 = new QGroupBox("RHEED 条纹位置信息");
    QVBoxLayout* vbox2 = new QVBoxLayout();
    vbox2->addWidget(this->table_view);
    panel8->setLayout(vbox2);

    QGroupBox* panel9 = new QGroupBox("RHEED 图像条纹标记");
    QVBoxLayout* vbox3 = new QVBoxLayout();
    vbox3->addWidget(this->image_canvas);
    panel9->setLayout(vbox3);

    QWidget* panel10 = new QWidget();
    QVBoxLayout* vbox4 = new QVBoxLayout();
    vbox4->addWidget(panel9);
    vbox4->addWidget(panel8);
    panel10->setLayout(vbox4);

    QHBoxLayout* hbox5 = new QHBoxLayout();
    hbox5->addWidget(panel6);
    hbox5->addWidget(panel10);
    this->setLayout(hbox5);

    // add listener
    connect(weight_file_button, SIGNAL(clicked()), this, SLOT(select_weight_file()));
    connect(label_file_button, SIGNAL(clicked()), this, SLOT(select_config_file()));
    connect(image_select_button, SIGNAL(clicked()), this, SLOT(select_image_dir()));
    connect(start_detect_button, SIGNAL(clicked()), this, SLOT(start_detect()));
    connect(go_front_button, SIGNAL(clicked()), this, SLOT(go_front_image()));
    connect(go_next_button, SIGNAL(clicked()), this, SLOT(go_next_image()));

    // 初始化界面的时候，将设置参数初始化到窗口中
    InferenceSettings settings(DETECT_ALGORITHM_TYPE::RHEED_IMAGE_HANDLE);
    settings.loadSettings();
    this->weight_file_path->setText(QString::fromStdString(settings.getWeight_file()));
    this->label_file_path->setText(QString::fromStdString(settings.getConfig_file()));
    this->fps->setChecked(settings.getShow_fps());
    this->count->setChecked(settings.getShowCount());
};


// 槽函数
void RHEEDImageHandleView::select_weight_file(){
    QString file_name = QFileDialog::getOpenFileName(this,"select weight file","D:/Postgraduate3/",tr("Weight(*.onnx);"));
    if(file_name.isEmpty() && this->weight_file_path->text().isEmpty()){
        QMessageBox::warning(this,"warning","weight file path is empty.");
        return;
    }
    if(!file_name.isEmpty()){
        this->weight_file_path->setText(file_name);
    }
}

void RHEEDImageHandleView::select_config_file(){
    QString file_name = QFileDialog::getOpenFileName(this,"select label file","D:/Postgraduate3/",tr("Labels(*.txt);"));
    if(file_name.isEmpty() && this->label_file_path->text().isEmpty()){
        QMessageBox::warning(this,"warning","config file path is empty.");
        return;
    }
    if(!file_name.isEmpty()){
        this->label_file_path->setText(file_name);
    }
}

void RHEEDImageHandleView::start_detect(){
    int ret = QMessageBox::question(this,"RHEED pattern","run detect RHEED pattern?",QMessageBox::StandardButtons(
                              QMessageBox::StandardButton::Yes | QMessageBox::StandardButton::No));
    if(ret == QMessageBox::No)  return;

    auto weight_file = this->weight_file_path->text().toStdString();
    auto config_file = this->label_file_path->text().toStdString();
    auto image_path = this->image_path->text().toStdString();
    bool show_fps = this->fps->isChecked();
    bool show_count = this->count->isChecked();

    if(image_path.empty() || this->image_paths.size() == 0){
        QMessageBox::warning(this,"warning","Please select image directory first.");
        return;
    }

    if(weight_file.empty() || weight_file == ""){
        QMessageBox::warning(this,"warning","Please select weight file first.");
        return;
    }

    if(config_file.empty() || config_file == ""){
        QMessageBox::warning(this,"warning","Please select config file first.");
        return;
    }

    InferenceSettings settings(DETECT_ALGORITHM_TYPE::RHEED_IMAGE_HANDLE);
    settings.setWeight_file(weight_file);
    settings.setConfig_file(config_file);
    settings.set_data_path(image_path);
    settings.setShow_fps(show_fps);
    settings.setShowCount(show_count);

    // 每一次运行的参数都写入到文件中
    settings.dumpSettings();

    // 初始化工作线程
    this->work_thread = new RHEEDImageHandleThread(settings);
    qRegisterMetaType<cv::Mat>("cv::Mat");
    qRegisterMetaType<std::vector<cv::Rect>>("std::vector<cv::Rect>");

    // 针对子线程，注册信号与槽
    connect(this->work_thread, SIGNAL(sendResult(cv::Mat,std::vector<cv::Rect>)), this, SLOT(post_image_process(cv::Mat,std::vector<cv::Rect>)));
    connect(this->work_thread, &RHEEDImageHandleThread::finished, this->work_thread, &QObject::deleteLater);

    this->work_thread->start(); // OS 通过 start() callback run()

    this->start_detect_button->setEnabled(false);       // 设置按钮不可选取
}

// 接收子线程信号的槽函数（接收子线程处理后的图像，显示到 QT panel 中）
void RHEEDImageHandleView::post_image_process(cv::Mat frame, std::vector<cv::Rect> roi_rects){

    this->start_detect_button->setEnabled(true);
    this->table_model->clear();
    if(frame.empty()){
        return;
    }

    cv::Mat dst;
    cv::cvtColor(frame,dst,cv::COLOR_BGR2RGB);

    QImage image = QImage(dst.data,dst.cols,dst.rows,dst.step,QImage::Format_RGB888);
    image = image.scaled(600,600,Qt::KeepAspectRatio);

    QPixmap  pixmap = QPixmap::fromImage(image);
    this->image_canvas->setImage(pixmap);

    // 表格填充 RHEED 条纹位置信息
    this->table_model->setHorizontalHeaderLabels({"x", "y", "width", "height", "area"});
    for(auto roi_rect:roi_rects){
        QList<QStandardItem*> row_data;
        row_data<<new QStandardItem(QString::number(roi_rect.x))<<
                  new QStandardItem(QString::number(roi_rect.y))<<
                  new QStandardItem(QString::number(roi_rect.width))<<
                  new QStandardItem(QString::number(roi_rect.height))<<
                  new QStandardItem(QString::number(roi_rect.area()));
        this->table_model->appendRow(row_data);
    }
}

void RHEEDImageHandleView::select_image_dir(){

    // 创建文件夹选择对话框，选择指定文件夹，返回文件夹目录
    auto file_dir = QFileDialog::getExistingDirectory(this,"选择图像目录","D:/Photo/");
    if(file_dir.isEmpty()){
        return;
    }

    RHEEDImageHandle::read_image_file_dir(file_dir.toStdString(),this->image_paths);

    std::string tmp = std::to_string(this->image_paths.size());
    this->image_num_label->setText(QString::fromStdString(tmp));

    if(this->image_paths.size() == 0){
        return;
    }

    // 显示目录里面的第一张图像
    this->image_index = 0;
    this->image_path->setText(QString::fromStdString(this->image_paths[this->image_index]));
    QPixmap pixmap = QPixmap(QString::fromStdString(this->image_paths[this->image_index]));
    pixmap = pixmap.scaled(800,600,Qt::KeepAspectRatio);
    this->image_label->setPixmap(pixmap);
}

void RHEEDImageHandleView::go_front_image(){
    if(this->image_index <= 0 || this->image_paths.size() == 0){
        std::cout<<"first image"<<std::endl;
        return;
    }
    this->image_index--;

    this->image_path->setText(QString::fromStdString(this->image_paths[this->image_index]));
    QPixmap pixmap = QPixmap(QString::fromStdString(this->image_paths[this->image_index]));
    pixmap = pixmap.scaled(800,600,Qt::KeepAspectRatio);
    this->image_label->setPixmap(pixmap);
}

void RHEEDImageHandleView::go_next_image(){
    if(this->image_index >= this->image_paths.size() - 1 || this->image_paths.size() == 0){
        std::cout<<"last image"<<std::endl;
        return;
    }
    this->image_index++;

    this->image_path->setText(QString::fromStdString(this->image_paths[this->image_index]));
    QPixmap pixmap = QPixmap(QString::fromStdString(this->image_paths[this->image_index]));
    pixmap = pixmap.scaled(800,600,Qt::KeepAspectRatio);
    this->image_label->setPixmap(pixmap);
}
