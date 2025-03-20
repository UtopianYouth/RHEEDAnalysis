#include "algorithm/inference_settings.h"
#include <opencv2/opencv.hpp>

InferenceSettings::InferenceSettings(DETECT_ALGORITHM_TYPE name){
    this->name = name;
}

// set
void InferenceSettings::setConfig_file(const std::string &newConfig_file){
    this->config_file = newConfig_file;
}

void InferenceSettings::setWeight_file(const std::string &newWeight_file){
    this->weight_file = newWeight_file;
}

void InferenceSettings::set_data_path(const std::string &data_path){
    this->data_path = data_path;
}

void InferenceSettings::setScore(float score){
    this->score = score;
}

void InferenceSettings::setShow_score(bool newShow_score){
    this->show_score = newShow_score;
}

void InferenceSettings::setShow_fps(bool newShow_fps){
    this->show_fps = newShow_fps;
}

void InferenceSettings::setConf(float conf){
    this->conf = conf;
}

void InferenceSettings::setInput_w(int input_w){
    this->input_w = input_w;
}

void InferenceSettings::setInput_h(int input_h){
    this->input_h = input_h;
}

void InferenceSettings::setName(DETECT_ALGORITHM_TYPE name){
    this->name = name;
}

void InferenceSettings::setShowCount(bool count){
    this->show_count = count;
}

// get
const std::string &InferenceSettings::getWeight_file() const{
    return weight_file;
}

const std::string &InferenceSettings::getConfig_file() const{
    return config_file;
}

const std::string& InferenceSettings::get_data_path() const{
    return this->data_path;
}

float InferenceSettings::getScore() const{
    return score;
}

bool InferenceSettings::getShow_fps() const{
    return show_fps;
}

bool InferenceSettings::getShow_score() const{
    return show_score;
}

float InferenceSettings::getConf() const{
    return this->conf;
}

int InferenceSettings::getInput_w() const{
    return this->input_w;
}

int InferenceSettings::getInput_h() const{
    return this->input_h;
}

DETECT_ALGORITHM_TYPE InferenceSettings::getName() const{
    return this->name;
}
bool InferenceSettings::getShowCount() const{
    return this->show_count;
}

// 加载参数
void InferenceSettings::loadSettings(){

    if(this->name == DETECT_ALGORITHM_TYPE::FACE_DETECT){
        cv::FileStorage fs("face_detector_settings.yaml", cv::FileStorage::READ);
        if(!fs.isOpened()){
            std::cout<<"open settings failure"<<std::endl;
            return;
        }
        fs["weight_file"] >> this->weight_file;
        fs["config_file"] >> this->config_file;
        fs["score"] >> this->score;
        fs["show_fps"] >> this->show_fps;
        fs["show_score"] >> this->show_score;
        fs.release();
    }

    if(this->name == DETECT_ALGORITHM_TYPE::YOLOv5_DNN){
        cv::FileStorage fs("yolov5_detector_settings.yaml", cv::FileStorage::READ);
        if(!fs.isOpened()){
            std::cout<<"open settings failure"<<std::endl;
            return;
        }
        fs["weight_file"] >> this->weight_file;
        fs["config_file"] >> this->config_file;
        fs["score"] >> this->score;
        fs["conf"] >> this->conf;
        fs["show_fps"] >> this->show_fps;
        fs["show_score"] >> this->show_score;
        fs.release();
    }

    if(this->name == DETECT_ALGORITHM_TYPE::YOLOv8_DNN || this->name == DETECT_ALGORITHM_TYPE::YOLOv8_OV){
        cv::FileStorage fs("yolov8_detector_settings.yaml", cv::FileStorage::READ);
        if(!fs.isOpened()){
            std::cout<<"open settings failure"<<std::endl;
            return;
        }
        fs["weight_file"] >> this->weight_file;
        fs["config_file"] >> this->config_file;
        fs["score"] >> this->score;
        fs["show_fps"] >> this->show_fps;
        fs["show_score"] >> this->show_score;
        fs.release();
    }
    if(this->name == DETECT_ALGORITHM_TYPE::RHEED_IMAGE_HANDLE){
        cv::FileStorage fs("rheed_image_handle_settings.yaml", cv::FileStorage::READ);
        if(!fs.isOpened()){
            std::cout<<"open settings failure"<<std::endl;
            return;
        }
        fs["weight_file"] >> this->weight_file;
        fs["config_file"] >> this->config_file;
        fs["show_fps"] >> this->show_fps;
        fs["show_count"] >> this->show_count;
        fs.release();
    }
}

// 写入参数
void InferenceSettings::dumpSettings(){

    if(this->name == DETECT_ALGORITHM_TYPE::FACE_DETECT){
        cv::FileStorage fs("face_detector_settings.yaml", cv::FileStorage::WRITE);

        fs << "weight_file" << this->weight_file;
        fs << "config_file" << this->config_file;
        fs << "score" << this->score;
        fs << "show_fps" << this->show_fps;
        fs << "show_score" << this->show_score;

        fs.release();
    }

    if(this->name == DETECT_ALGORITHM_TYPE::YOLOv5_DNN){
        cv::FileStorage fs("yolov5_detector_settings.yaml", cv::FileStorage::WRITE);

        fs << "weight_file" << this->weight_file;
        fs << "config_file" << this->config_file;
        fs << "score" << this->score;
        fs << "conf" << this->conf;
        fs << "show_fps" << this->show_fps;
        fs << "show_score" << this->show_score;

        fs.release();
    }

    if(this->name == DETECT_ALGORITHM_TYPE::YOLOv8_DNN || this->name == DETECT_ALGORITHM_TYPE::YOLOv8_OV){
        cv::FileStorage fs("yolov8_detector_settings.yaml", cv::FileStorage::WRITE);

        fs << "weight_file" << this->weight_file;
        fs << "config_file" << this->config_file;
        fs << "score" << this->score;
        fs << "show_fps" << this->show_fps;
        fs << "show_score" << this->show_score;
        fs.release();
    }

    if(this->name == DETECT_ALGORITHM_TYPE::RHEED_IMAGE_HANDLE){
        cv::FileStorage fs("rheed_image_handle_settings.yaml", cv::FileStorage::WRITE);

        fs << "weight_file" << this->weight_file;
        fs << "config_file" << this->config_file;
        fs << "show_fps" << this->show_fps;
        fs << "show_count" << this->show_count;
        fs.release();
    }
}

