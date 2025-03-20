#ifndef RHEED_IMAGE_HANDLE_UI_H
#define RHEED_IMAGE_HANDLE_UI_H

#include<QWidget>
#include<QLabel>
#include<QComboBox>
#include<QCheckBox>
#include<QRadioButton>
#include<QLineEdit>
#include<QPushButton>
#include<QFont>
#include<QTableView>
#include<QStandardItemModel>
#include"ui/rheed_image_handle_thread.h"
#include"ui/detect_info_canvas.h"

// 自定义 Panel
class RHEEDImageHandleView:public QWidget{
    // 使用 Q_OBJECT 保证 QT 的组件可以正常显示在界面中
    Q_OBJECT

public:
    RHEEDImageHandleView();
    ~RHEEDImageHandleView();
    void initUI();
public slots:
    void select_weight_file();
    void select_config_file();
    void select_image_dir();
    void start_detect();
    void post_image_process(cv::Mat frame,std::vector<cv::Rect> roi_rects);
    void go_front_image();
    void go_next_image();
private:
    // 模型选择部分
    QLineEdit* weight_file_path{nullptr};
    QLineEdit* label_file_path{nullptr};
    QPushButton* weight_file_button{nullptr};
    QPushButton* label_file_button{nullptr};

    // 图像文字部分
    QCheckBox* fps{nullptr};
    QCheckBox* count{nullptr};

    // 数据加载部分
    QLineEdit* image_path{nullptr};
    QPushButton* image_select_button{nullptr};
    QLabel* image_num_label{nullptr};

    // 显示部分，使用自定义的画布
    DetectInfoCanvas* image_canvas{nullptr};

    // 运行按钮
    QPushButton* start_detect_button{nullptr};

    // 表格部分
    QTableView* table_view{nullptr};
    QStandardItemModel* table_model{nullptr};

    // 图像浏览部分
    QPushButton* go_front_button{nullptr};
    QPushButton* go_next_button{nullptr};
    QLabel* image_label{nullptr};
    int image_index = 0;

    // RHEED 算法执行线程
    RHEEDImageHandleThread* work_thread{nullptr};

    // 图像文件路径
    std::vector<std::string>image_paths;
};

#endif // RHEED_IMAGE_HANDLE_UI_H
