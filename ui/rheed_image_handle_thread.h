#ifndef RHEED_IMAGE_HANDLE_THREAD_H
#define RHEED_IMAGE_HANDLE_THREAD_H

#include <QThread>
#include "algorithm/rheed_image_handle.h"

class RHEEDImageHandleThread:public QThread{
    Q_OBJECT
public:
    RHEEDImageHandleThread(InferenceSettings& settings);
    ~RHEEDImageHandleThread();
protected:
    void run()override;
signals:
    void sendResult(cv::Mat, std::vector<cv::Rect>);
private:
    std::shared_ptr<RHEEDImageHandle> rheed_image_handle{nullptr};
    std::string data_path = "";
};

#endif // RHEED_IMAGE_HANDLE_THREAD_H
