#include "ui/rheed_image_handle_thread.h"
#include <QImage>

RHEEDImageHandleThread::RHEEDImageHandleThread(InferenceSettings& settings){

    this->rheed_image_handle = std::make_shared<RHEEDImageHandle>();
    // 初始化算法参数
    this->rheed_image_handle->init_config(settings);
    this->data_path = settings.get_data_path();

    std::cout<<"create rheed image handle thread"<<std::endl;
}

RHEEDImageHandleThread::~RHEEDImageHandleThread(){
    std::cout<<"destroy rheed image handle thread"<<std::endl;
}

// 重写 QThread 的 run 方法
void RHEEDImageHandleThread::run(){
    // 转换为 QString
    QString data_path = QString::fromStdString(this->data_path);

    if(data_path.endsWith(".png") || data_path.endsWith(".jpg")){
        // .png or .jpg 结尾的 QString
        cv::Mat frame = cv::imread(this->data_path);
        std::vector<cv::Rect> roi_rects;
        this->rheed_image_handle->find_and_draw_contours(frame, roi_rects);   // 引用传递
        emit this->sendResult(frame, roi_rects);           // 向主线程发送推断的结果（信号机制）
    }
}
