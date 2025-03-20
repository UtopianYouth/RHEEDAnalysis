#include <QFont>
#include <QImage>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QFileDialog>
#include <QMessageBox>
#include <QHeaderView>
#include "ui/rheed_video_handle_ui.h"
#include "algorithm/rheed_image_handle.h"

RHEEDVideoHandleView::RHEEDVideoHandleView(){
    // 模型选择部分
    this->weight_file_path = new QLineEdit();
    this->label_file_path = new QLineEdit();
    this->weight_file_button = new QPushButton("输入");
    this->label_file_button = new QPushButton("输入");

    // 图像文字部分
    this->fps = new QCheckBox("显示FPS");
    this->count = new QCheckBox("显示条纹数量");

    // 数据加载部分
    this->video_path = new QLineEdit();
    this->video_select_button = new QPushButton("视频选择");

    // 显示部分，使用自定义的画布
    this->image_canvas = new QLabel();
    this->image_label = new QLabel();

    // 运行按钮
    this->start_stop_button = new QPushButton();

    // 保存配置按钮
    this->save_config_button = new QPushButton();

    // 表格部分
    this->table_view = new QTableView();
    this->table_model = new QStandardItemModel();
    this->table_view->setModel(this->table_model);

    this->initUI();

    std::cout<<"create rheed video handle view"<<std::endl;
}

RHEEDVideoHandleView::~RHEEDVideoHandleView(){
    std::cout<<"destroy rheed video handle view"<<std::endl;
}

void RHEEDVideoHandleView::initUI(){
    this->weight_file_path->setReadOnly(true);
    this->label_file_path->setReadOnly(true);
    this->video_path->setReadOnly(true);

    this->weight_file_path->setFixedWidth(400);
    this->label_file_path->setFixedWidth(400);
    this->video_path->setFixedWidth(400);

    this->start_stop_button->setFixedSize(128,48);
    this->start_stop_button->setIcon(QIcon(":/images/stop_icon.png"));

    this->save_config_button->setFixedSize(128,48);
    this->save_config_button->setIcon(QIcon(":/images/save_icon.png"));

    this->image_label->setFixedSize(800,600);
    this->image_canvas->setFixedSize(800,600);

    // 交替行颜色
    this->table_view->setAlternatingRowColors(true);
    // 填充整个表格
    this->table_view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // 表头加粗显示
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

    QWidget* panel3 = new QGroupBox("视频文件信息");
    QGridLayout* grid3 = new QGridLayout();
    grid3->addWidget(new QLabel("视频文件路径："),0,0);
    grid3->addWidget(this->video_path,0,1);
    grid3->addWidget(this->video_select_button,0,2);
    panel3->setLayout(grid3);

    QGroupBox* panel4 = new QGroupBox("源视频");
    QHBoxLayout* hbox4 = new QHBoxLayout();
    hbox4->addStretch(1);
    hbox4->addWidget(this->image_label);
    hbox4->addStretch(1);
    panel4->setLayout(hbox4);

    QWidget* panel5 = new QWidget();
    QHBoxLayout* hbox5 = new QHBoxLayout();
    hbox5->addWidget(this->save_config_button);
    hbox5->addStretch(2);
    hbox5->addWidget(this->start_stop_button);
    panel5->setLayout(hbox5);

    QWidget* panel6 = new QWidget();
    QVBoxLayout* vbox1 = new QVBoxLayout();
    vbox1->setAlignment(Qt::AlignHCenter);
    vbox1->addWidget(panel1);
    vbox1->addWidget(panel2);
    vbox1->addWidget(panel3);
    vbox1->addWidget(panel4);
    vbox1->addWidget(panel5);
    vbox1->addStretch(1);
    panel6->setLayout(vbox1);

    QGroupBox* panel7 = new QGroupBox("RHEED 条纹位置信息");
    QVBoxLayout* vbox2 = new QVBoxLayout();
    vbox2->addWidget(this->table_view);
    panel7->setLayout(vbox2);

    QGroupBox* panel8 = new QGroupBox("RHEED 图像条纹标记");
    QVBoxLayout* vbox3 = new QVBoxLayout();
    vbox3->addWidget(this->image_canvas);
    panel8->setLayout(vbox3);

    QWidget* panel9 = new QWidget();
    QVBoxLayout* vbox4 = new QVBoxLayout();
    vbox4->addWidget(panel8);
    vbox4->addWidget(panel7);
    panel9->setLayout(vbox4);

    QHBoxLayout* hbox6 = new QHBoxLayout();
    hbox6->addWidget(panel6);
    hbox6->addWidget(panel9);
    this->setLayout(hbox6);

    // add listener
    connect(weight_file_button, SIGNAL(clicked()), this, SLOT(select_weight_file()));
    connect(label_file_button, SIGNAL(clicked()), this, SLOT(select_config_file()));
    connect(video_select_button, SIGNAL(clicked()), this, SLOT(select_video_file()));
    connect(start_stop_button, SIGNAL(clicked()), this, SLOT(start_stop_detect()));
    connect(save_config_button, SIGNAL(clicked()), this, SLOT(save_config()));

    // 初始化界面的时候，将设置参数初始化到窗口中
    InferenceSettings settings(DETECT_ALGORITHM_TYPE::RHEED_IMAGE_HANDLE);
    settings.loadSettings();
    this->weight_file_path->setText(QString::fromStdString(settings.getWeight_file()));
    this->label_file_path->setText(QString::fromStdString(settings.getConfig_file()));
    this->fps->setChecked(settings.getShow_fps());
    this->count->setChecked(settings.getShowCount());
};

// 槽函数
void RHEEDVideoHandleView::select_weight_file(){
    QString file_name = QFileDialog::getOpenFileName(this,"select weight file","D:/Postgraduate3/",tr("Weight(*.onnx);"));
    if(file_name.isEmpty() && this->weight_file_path->text().isEmpty()){
        QMessageBox::warning(this,"warning","weight file path is empty.");
        return;
    }
    if(!file_name.isEmpty()){
        this->weight_file_path->setText(file_name);
    }
}

void RHEEDVideoHandleView::select_config_file(){
    QString file_name = QFileDialog::getOpenFileName(this,"select label file","D:/Postgraduate3/",tr("Labels(*.txt);"));
    if(file_name.isEmpty() && this->label_file_path->text().isEmpty()){
        QMessageBox::warning(this,"warning","config file path is empty.");
        return;
    }
    if(!file_name.isEmpty()){
        this->label_file_path->setText(file_name);
    }
}

void RHEEDVideoHandleView::select_video_file(){

    // 创建文件选择对话框，选择指定格式的文件，返回文件路径
    QString file_name = QFileDialog::getOpenFileName(this,"select image","D:/Photo/",tr("Videos(*.mp4);"));
    if(file_name.isEmpty()){
        return;
    }

    this->video_path->setText(file_name);
    cv::VideoCapture capture(this->video_path->text().toStdString());
    cv::Mat frame,dst;
    capture.read(frame);

    // 显示视频第一帧图像
    cv::cvtColor(frame,dst,cv::COLOR_BGR2RGB);
    QImage image = QImage(dst.data,dst.cols,dst.rows,dst.step,QImage::Format_RGB888);
    image = image.scaled(800,600,Qt::KeepAspectRatio);
    QPixmap pixmap = QPixmap::fromImage(image);
    this->image_label->setPixmap(pixmap);
}

void RHEEDVideoHandleView::start_stop_detect(){
    if(this->is_start){
        int ret = QMessageBox::question(this,"RHEED pattern","run detect RHEED pattern?",QMessageBox::StandardButtons(
                                  QMessageBox::StandardButton::Yes | QMessageBox::StandardButton::No));
        if(ret == QMessageBox::No)  return;

        auto weight_file = this->weight_file_path->text().toStdString();
        auto config_file = this->label_file_path->text().toStdString();
        auto video_path = this->video_path->text().toStdString();
        bool show_fps = this->fps->isChecked();
        bool show_count = this->count->isChecked();

        if(weight_file.empty() || weight_file == ""){
            QMessageBox::warning(this,"warning","Please select weight file first.");
            return;
        }

        if(config_file.empty() || config_file == ""){
            QMessageBox::warning(this,"warning","Please select config file first.");
            return;
        }

        if(video_path.empty() || video_path == ""){
            QMessageBox::warning(this,"warning","Please select image or video first.");
            return;
        }

        InferenceSettings settings(DETECT_ALGORITHM_TYPE::RHEED_IMAGE_HANDLE);
        settings.setWeight_file(weight_file);
        settings.setConfig_file(config_file);
        settings.set_data_path(video_path);
        settings.setShow_fps(show_fps);
        settings.setShowCount(show_count);

        // 初始化工作线程
        this->work_thread = new RHEEDVideoHandleThread(settings);

        qRegisterMetaType<cv::Mat>("cv::Mat");
        qRegisterMetaType<std::vector<cv::Rect>>("std::vector<cv::Rect>");

        // 针对子线程，注册信号与槽
        connect(this->work_thread, &RHEEDVideoHandleThread::sendResult1, this, &RHEEDVideoHandleView::post_image_process1);
        connect(this->work_thread, &RHEEDVideoHandleThread::sendResult2, this, &RHEEDVideoHandleView::post_image_process2);
        connect(this->work_thread, &RHEEDVideoHandleThread::sendResult3, this, &RHEEDVideoHandleView::post_roi_rects);
        connect(this->work_thread, &RHEEDVideoHandleThread::finished, this->work_thread, &QObject::deleteLater);

        this->work_thread->start(); // OS 通过 start() callback run()
        this->is_start = false;
        this->start_stop_button->setIcon(QIcon(":/images/run_icon.png"));
        this->fps->setEnabled(false);
        this->count->setEnabled(false);
        this->weight_file_button->setEnabled(false);
        this->label_file_button->setEnabled(false);
    }
    else{
        if(this->is_pause){     // 上一个状态
            this->start_stop_button->setIcon(QIcon(":/images/run_icon.png"));
            this->is_pause = false;
            this->work_thread->resume();
        }
        else{
            this->start_stop_button->setIcon(QIcon(":/images/stop_icon.png"));
            this->is_pause = true;
            this->work_thread->pause();
        }
    }
}

void RHEEDVideoHandleView::save_config(){
    int ret = QMessageBox::question(this,"save file","save this detect configuration?",QMessageBox::StandardButtons(
                              QMessageBox::StandardButton::Yes | QMessageBox::StandardButton::No));
    if(ret == QMessageBox::No)  return;

    auto weight_file = this->weight_file_path->text().toStdString();
    auto config_file = this->label_file_path->text().toStdString();
    auto video_path = this->video_path->text().toStdString();
    bool show_fps = this->fps->isChecked();
    bool show_count = this->count->isChecked();

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
    settings.setShow_fps(show_fps);
    settings.setShowCount(show_count);

    // 将运行参数都写入到文件中
    settings.dumpSettings();
}


// 接收子线程信号的槽函数（接收子线程处理后的图像，显示到 QT panel 中）
void RHEEDVideoHandleView::post_image_process1(cv::Mat frame){
    // 视频最后一帧
    if(frame.empty()){
        this->start_stop_button->setIcon(QIcon(":/images/stop_icon.png"));
        this->is_start = true;
        this->fps->setEnabled(true);
        this->count->setEnabled(true);
        this->weight_file_button->setEnabled(true);
        this->label_file_button->setEnabled(true);
        return;
    }

    cv::Mat dst;
    cv::cvtColor(frame,dst,cv::COLOR_BGR2RGB);
    QImage image1 = QImage(dst.data,dst.cols,dst.rows,dst.step,QImage::Format_RGB888);
    image1 = image1.scaled(800,600,Qt::KeepAspectRatio);
    QPixmap  pixmap1 = QPixmap::fromImage(image1);
    this->image_canvas->setPixmap(pixmap1);
}

void RHEEDVideoHandleView::post_image_process2(cv::Mat frame){
    // 视频最后一帧
    if(frame.empty()){
        return;
    }
    cv::Mat dst;
    cv::cvtColor(frame,dst,cv::COLOR_BGR2RGB);
    QImage image1 = QImage(dst.data,dst.cols,dst.rows,dst.step,QImage::Format_RGB888);
    image1 = image1.scaled(800,600,Qt::KeepAspectRatio);
    QPixmap  pixmap1 = QPixmap::fromImage(image1);
    this->image_label->setPixmap(pixmap1);
}

void RHEEDVideoHandleView::post_roi_rects(std::vector<cv::Rect> roi_rects){
    this->table_model->clear();

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


