#include"rheed_image_handle.h"

RHEEDImageHandle::RHEEDImageHandle(){
    std::cout<<"create RHEED image handle algorithm"<<std::endl;
}

RHEEDImageHandle::~RHEEDImageHandle(){
    std::cout<<"delete RHEED image handle algorithm"<<std::endl;
}

// 初始化 RHEED 参数
void RHEEDImageHandle::init_config(InferenceSettings &settings){
    this->weight_file = settings.getWeight_file();
    this->config_file = settings.getWeight_file();
    this->show_fps = settings.getShow_fps();
    this->show_count = settings.getShowCount();
}

// 二值化
cv::Mat RHEEDImageHandle::gray_and_binary(cv::Mat& frame){
    cv::Mat gray,binary;
    cv::GaussianBlur(frame, frame, cv::Size(3, 3), 0);
    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

    // 最后一个参数为每一个局部阈值减去常数
    cv::adaptiveThreshold(gray, binary, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, 3, -0.7);

    // 形态学操作
    cv::Mat kernel = getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    morphologyEx(binary, binary, cv::MORPH_OPEN, kernel, cv::Point(-1, -1), 1);
    return binary;
}

// 融合
cv::Mat RHEEDImageHandle::image_fusion(cv::Mat& src1, float weight1, cv::Mat& src2, float weight2){
    cv::Mat dst;
    cv::addWeighted(src1, weight1, src2, weight2, 0, dst);
    return dst;
}

/*
    USM 图像锐化
    - 锐化因子(amount): 控制锐化效果的强度，值越大，锐化效果越明显
    - 阈值(threshold): 控制哪些像素会被锐化，值越大，只有灰度差异较大的像素才会被锐化，减少了噪声的影响
*/
cv::Mat RHEEDImageHandle::USM_demo(cv::Mat& src){
    if (src.empty()) {
        printf("could not load image...\n");
        return src;
    }

    cv::Mat blur1 = cv::Mat::zeros(src.size(), src.type());

    cv::Mat dst1 = cv::Mat::zeros(src.size(), src.type());

    // 二维高斯卷积核，对核内的每一个像素值进行高斯概率密度计算
    cv::GaussianBlur(src, blur1, cv::Size(99, 99), 0);

    double amount = 0.90;

    // 整图操作，转换为浮点数类型，防止做差操作溢出
    cv::Mat src_float, blur_float;
    src.convertTo(src_float, CV_32F);
    blur1.convertTo(blur_float, CV_32F);

    // 计算残差图 mask
    cv::Mat subtract_mask = src_float - blur_float;

    // 将残差图按比例加回到原始图像中
    cv::Mat sharpened = src_float + amount * subtract_mask;

    // 1.0 缩放系数，0 偏置值
    sharpened.convertTo(dst1, CV_8UC3, 1.0, 0);

    // 返回锐化的结果
    return dst1;
}

void RHEEDImageHandle::find_and_draw_contours(cv::Mat &frame, std::vector<cv::Rect>& roi_rects) {
    int64 start = cv::getTickCount();
    // 融合
    cv::Mat fusion_frame = this->image_fusion(frame,0.55,frame,0.55);
    // 锐化
    cv::Mat usm_frame = this->USM_demo(fusion_frame);

    cv::Mat binary = this->gray_and_binary(usm_frame);

    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    findContours(binary, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // 筛选轮廓
    for (int i = 0; i < contours.size(); ++i) {
        cv::Rect rect = boundingRect(contours[i]);
        double w = static_cast<double>(rect.width);
        double h = static_cast<double>(rect.height);
        if (w / h >= 0.5 || w*h <= 30) {
            continue;
        }
        printf("width = %.2lf, height = %.2lf, w/h = %.2lf\n", w, h, w / h);
        roi_rects.push_back(rect);
        rectangle(frame, rect, cv::Scalar(50, 50, 100), 1, 8);
    }

    if(this->show_fps){
        float t = (cv::getTickCount() - start) / cv::getTickFrequency();
        cv::putText(frame,cv::format("FPS: %.2f",1.0/t),cv::Point(10,15),
                    cv::QT_FONT_NORMAL,0.4,cv::Scalar(0,0,255),1,cv::LINE_AA);
    }
    if(this->show_count){
        cv::putText(frame,cv::format("Streak Count: %lld", roi_rects.size()),cv::Point(10,30),
                    cv::QT_FONT_NORMAL,0.4,cv::Scalar(0,0,255),1,cv::LINE_AA);
    }
}

void RHEEDImageHandle::read_image_file_dir(std::string dir_path, std::vector<std::string>& image_path){
    dir_path += "/*.png";
    cv::glob(dir_path, image_path);
}
