#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>
#include <Eigen/Dense>
#include <random>

using namespace std;
/*
 * Frame : 保存每帧的姿态和观测
 */
struct Frame {
    Frame(Eigen::Matrix3d R, Eigen::Vector3d t) : Rwc(R), qwc(R), twc(t) {};
    Eigen::Matrix3d Rwc;
    Eigen::Quaterniond qwc;
    Eigen::Vector3d twc;

    unordered_map<int, Eigen::Vector3d> featurePerId; // 该帧观测到的特征以及特征id
};

/*
 * 产生世界坐标系下的虚拟数据: 相机姿态, 特征点, 以及每帧观测
 */
void GetSimDataInWordFrame(vector<Frame> &cameraPoses, vector<Eigen::Vector3d> &points) {
    int featureNums = 20;  // 特征数目，假设每帧都能观测到所有的特征
    int poseNums = 2;     // 相机数目

    double radius = 8;
    for (int n = 0; n < poseNums; ++n) {
        double theta = n * 2 * M_PI / (poseNums * 4); // 1/4 圆弧
        // 绕 z轴 旋转
        Eigen::Matrix3d R;
        R = Eigen::AngleAxisd(theta, Eigen::Vector3d::UnitZ());
        Eigen::Vector3d t = Eigen::Vector3d(radius * cos(theta) - radius, radius * sin(theta), 1 * sin(2 * theta));
        cameraPoses.push_back(Frame(R, t));
    }

    // 随机数生成三维特征点
    std::default_random_engine generator;
    std::normal_distribution<double> noise_pdf(0., 1. / 1000.);  // 2pixel / focal
    for (int j = 0; j < featureNums; ++j) {
        std::uniform_real_distribution<double> xy_rand(0, 4.0);
        std::uniform_real_distribution<double> z_rand(4., 8.);

        Eigen::Vector3d Pw(xy_rand(generator), xy_rand(generator), z_rand(generator));
        points.push_back(Pw);

        // 在每一帧上的观测量
        for (int i = 0; i < poseNums; ++i) {
            // Pc = Rcw*(Pw - twc) = Rcw*Pw - Rcw*twc = Rcw*Pw + tcw = Pc
            Eigen::Vector3d Pc = cameraPoses[i].Rwc.transpose() * (Pw - cameraPoses[i].twc);
            Pc = Pc / Pc.z();  // 归一化图像平面
            Pc[0] += noise_pdf(generator);
            Pc[1] += noise_pdf(generator);
            cameraPoses[i].featurePerId.insert(make_pair(j, Pc));
        }
    }
}

void DrawSimData(const std::vector<Frame>& cameraPoses, const std::vector<Eigen::Vector3d>& points) {
    cv::Mat image(800, 800, CV_8UC3, cv::Scalar(255, 255, 255));

    // 绘制相机姿态
    for (const auto& pose : cameraPoses) {
        cv::Point center(static_cast<int>(400 + pose.twc[0]*50), static_cast<int>(400 + pose.twc[1]*50));
        cv::circle(image, center, 10, cv::Scalar(0, 255, 0), -1);
    }

    // 绘制特征点
    for (const auto& point : points) {
        cv::Point pt(static_cast<int>(400 + point[0]*50), static_cast<int>(400 + point[1]*50));
        cv::circle(image, pt, 5, cv::Scalar(255, 0, 0), -1);
    }

    cv::imshow("Simulated Data", image);
    cv::waitKey(0);
}

int main() {
    std::vector<Frame> cameraPoses;
    std::vector<Eigen::Vector3d> points;

    GetSimDataInWordFrame(cameraPoses, points);

    DrawSimData(cameraPoses, points);


    return 0;
}
