#ifndef INFERENCE_SETTINGS_H
#define INFERENCE_SETTINGS_H

#include"iostream"



enum DETECT_ALGORITHM_TYPE{
    YOLOv5_DNN,
    YOLOv8_DNN,
    YOLOv8_OV,
    FACE_DETECT,
    RHEED_IMAGE_HANDLE
};

class InferenceSettings{
public:
    InferenceSettings(DETECT_ALGORITHM_TYPE name);

    // set
    void setWeight_file(const std::string &newWeight_file);
    void setConfig_file(const std::string &newConfig_file);
    void set_data_path(const std::string& data_path);
    void setShow_score(bool newShow_score);
    void setShow_fps(bool newShow_fps);
    void setScore(float score);
    void setConf(float conf);
    void setInput_w(int input_w);
    void setInput_h(int input_h);
    void setName(DETECT_ALGORITHM_TYPE name);
    void setShowCount(bool count);

    // get
    const std::string &getWeight_file() const;
    const std::string &getConfig_file() const;
    const std::string &get_data_path() const;
    bool getShow_score() const;
    bool getShow_fps() const;
    float getScore() const;
    float getConf() const;
    int getInput_w() const;
    int getInput_h() const;
    DETECT_ALGORITHM_TYPE getName() const;
    bool getShowCount() const;

    void loadSettings();
    void dumpSettings();

private:
    DETECT_ALGORITHM_TYPE name = DETECT_ALGORITHM_TYPE::FACE_DETECT;      // 推理类型
    std::string weight_file = "";
    std::string config_file = "";
    std::string data_path = "";
    float score = 0.50;
    bool show_fps = true;
    bool show_score = true;
    bool show_count = false;
    float conf = 0.50;
    int input_w = 640;
    int input_h = 640;
};

#endif // INFERENCE_SETTINGS_H
