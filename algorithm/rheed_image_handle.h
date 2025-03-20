#ifndef RHEED_IMAGE_HANDLE_H
#define RHEED_IMAGE_HANDLE_H
#include<opencv2/opencv.hpp>
#include"inference_settings.h"

class RHEEDImageHandle{
public:
    RHEEDImageHandle();
    ~RHEEDImageHandle();
    void init_config(InferenceSettings& settings);
    cv::Mat gray_and_binary(cv::Mat& frame);
    cv::Mat image_fusion(cv::Mat& src1, float weight1, cv::Mat& src2, float weight2);
    cv::Mat USM_demo(cv::Mat& src);
    void find_and_draw_contours(cv::Mat& frame,std::vector<cv::Rect>& roi_rects);
    static void read_image_file_dir(std::string dir_path, std::vector<std::string>& image_path);
private:
    std::string weight_file = "";
    std::string config_file = "";
    bool show_fps = true;
    bool show_count = true;
};

#endif // RHEED_IMAGE_HANDLE_H
