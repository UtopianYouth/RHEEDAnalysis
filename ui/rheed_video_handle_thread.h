#ifndef RHEED_VIDEO_HANDLE_THREAD_H
#define RHEED_VIDEO_HANDLE_THREAD_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include "algorithm/rheed_image_handle.h"

class RHEEDVideoHandleThread:public QThread{
    Q_OBJECT
public:
    RHEEDVideoHandleThread(InferenceSettings& settings);
    ~RHEEDVideoHandleThread();
    void pause();
    void resume();

protected:
    void run()override;
signals:
    void sendResult1(cv::Mat);
    void sendResult2(cv::Mat);
    void sendResult3(std::vector<cv::Rect>);
private:
    std::shared_ptr<RHEEDImageHandle> rheed_image_handle{nullptr};
    std::string data_path = "";
    bool is_pause = false;
    QMutex mutex;
    QWaitCondition condition;
};

#endif // RHEED_VIDEO_HANDLE_THREAD_H
