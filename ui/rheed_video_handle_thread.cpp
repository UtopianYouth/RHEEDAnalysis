#include "ui/rheed_video_handle_thread.h"
#include <QImage>

RHEEDVideoHandleThread::RHEEDVideoHandleThread(InferenceSettings& settings){

    this->rheed_image_handle = std::make_shared<RHEEDImageHandle>();
    // 初始化算法参数
    this->rheed_image_handle->init_config(settings);
    this->data_path = settings.get_data_path();

    std::cout<<"create rheed image handle thread"<<std::endl;
}

RHEEDVideoHandleThread::~RHEEDVideoHandleThread(){
    std::cout<<"destroy rheed image handle thread"<<std::endl;
}

// 重写 QThread 的 run 方法
void RHEEDVideoHandleThread::run(){
    // 转换为 QString
    QString data_path = QString::fromStdString(this->data_path);
    if(data_path.endsWith(".mp4")){
        // .mp4 结尾的 QString
        cv::VideoCapture capture(this->data_path);
        cv::Mat frame;
        cv::Mat dst;
        std::vector<cv::Rect> roi_rects;
        while(1){
            this->mutex.lock();
            if(this->is_pause){
                this->condition.wait(&this->mutex);
            }
            capture.read(frame);
            frame.copyTo(dst);
            roi_rects.clear();
            if(frame.empty()){
                break;
            }
            this->rheed_image_handle->find_and_draw_contours(dst, roi_rects);
            emit this->sendResult1(dst);
            emit this->sendResult2(frame);
            emit this->sendResult3(roi_rects);
            QThread::msleep(30);
            this->mutex.unlock();
        }
        // 视频流读取完毕后，发送空 Mat
        emit this->sendResult1(dst);
        emit this->sendResult2(frame);
        emit this->sendResult3(roi_rects);

        capture.release();
    }
}

void RHEEDVideoHandleThread::pause(){
    this->is_pause = true;
}

void RHEEDVideoHandleThread::resume(){
    this->condition.wakeAll();
    this->is_pause = false;
}
