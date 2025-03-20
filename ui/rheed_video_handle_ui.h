#ifndef RHEED_VIDEO_HANDLE_UI_H
#define RHEED_VIDEO_HANDLE_UI_H

#include<QWidget>
#include<QLabel>
#include<QCheckBox>
#include<QLineEdit>
#include<QPushButton>
#include<QFont>
#include<QTableView>
#include<QStandardItemModel>
#include"ui/rheed_video_handle_thread.h"
#include"ui/detect_info_canvas.h"

// 自定义 Panel
class RHEEDVideoHandleView:public QWidget{
    Q_OBJECT

public:
    RHEEDVideoHandleView();
    ~RHEEDVideoHandleView();
    void initUI();
public slots:
    void select_weight_file();
    void select_config_file();
    void select_video_file();
    void save_config();
    void start_stop_detect();
    void post_image_process1(cv::Mat frame);
    void post_image_process2(cv::Mat frame);
    void post_roi_rects(std::vector<cv::Rect> roi_rects);
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
    QLineEdit* video_path{nullptr};
    QPushButton* video_select_button{nullptr};

    // 显示部分，使用自定义的画布
    QLabel* image_canvas{nullptr};

    // 运行停止按钮
    QPushButton* start_stop_button{nullptr};

    // 保存配置
    QPushButton* save_config_button{nullptr};

    // RHEED 算法执行线程
    RHEEDVideoHandleThread* work_thread{nullptr};

    // 表格部分
    QTableView* table_view{nullptr};
    QStandardItemModel* table_model{nullptr};

    // 原图显示
    QLabel* image_label{nullptr};

    // 控制视频暂停
    bool is_pause = false;
    bool is_start = true;
};


#endif // RHEED_VIDEO_HANDLE_UI_H
