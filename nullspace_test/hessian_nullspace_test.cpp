#include <iostream>
#include <vector>
#include <random>  
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <Eigen/Eigenvalues>

struct Pose
{
    Pose(Eigen::Matrix3d R, Eigen::Vector3d t):Rwc(R),qwc(R),twc(t) {};
    Eigen::Matrix3d Rwc;
    Eigen::Quaterniond qwc;
    Eigen::Vector3d twc;
};

int main()
{
    int featureNums = 20;       // 路标点数
    int poseNums = 10;          // 姿态数量

    // 对位姿的雅可比分为旋转和平移两部分，单目SLAM中是一个2*6的矩阵；对于路标点的雅可比是一个2*3的矩阵
    int diem = poseNums * 6 + featureNums * 3;      // 10*6+20*3=120
    double fx = 1.;     // 焦距f分别在x,y轴方向等价的像素个数
    double fy = 1.;
    Eigen::MatrixXd H(diem,diem);   // H = J^T*J
    H.setZero();

    std::vector<Pose> camera_pose;
    double radius = 8;
    // 这里就是模拟了10个姿态，旋转范围绕z轴旋转90°，平均到10个姿态里面，旋转矩阵Rwc,典型的绕动轴旋转。
    // 平移量xy肯定是负的，画个图就能看出来。以最开始为世界系，后面旋转为相机系
    for(int n = 0; n < poseNums; ++n ) {
        double theta = n * 2 * M_PI / ( poseNums * 4); // 1/4 圆弧
        // 绕 z轴 旋转
        Eigen::Matrix3d R;
        R = Eigen::AngleAxisd(theta, Eigen::Vector3d::UnitZ());
        // 每次还要进行一定量xyz上面的平移,
        Eigen::Vector3d t = Eigen::Vector3d(radius * cos(theta) - radius, radius * sin(theta), 1 * sin(2 * theta));
        camera_pose.push_back(Pose(R,t));
    }

    // 随机数生成20个三维特征点
    std::default_random_engine generator;
    std::vector<Eigen::Vector3d> points;
    for(int j = 0; j < featureNums; ++j)
    {
        std::uniform_real_distribution<double> xy_rand(-4, 4.0);
        std::uniform_real_distribution<double> z_rand(8., 10.);
        double tx = xy_rand(generator);
        double ty = xy_rand(generator);
        double tz = z_rand(generator);

        Eigen::Vector3d Pw(tx, ty, tz);
        points.push_back(Pw);

        for (int i = 0; i < poseNums; ++i) {
            Eigen::Matrix3d Rcw = camera_pose[i].Rwc.transpose();
            Eigen::Vector3d Pc = Rcw * (Pw - camera_pose[i].twc);

            double x = Pc.x();
            double y = Pc.y();
            double z = Pc.z();
            double z_2 = z * z;
            Eigen::Matrix<double,2,3> jacobian_uv_Pc;
            jacobian_uv_Pc<< fx/z, 0 , -x * fx/z_2,
                    0, fy/z, -y * fy/z_2;
            Eigen::Matrix<double,2,3> jacobian_Pj = jacobian_uv_Pc * Rcw;
            Eigen::Matrix<double,2,6> jacobian_Ti;
            jacobian_Ti << -x* y * fx/z_2, (1+ x*x/z_2)*fx, -y/z*fx, fx/z, 0 , -x * fx/z_2,
                            -(1+y*y/z_2)*fy, x*y/z_2 * fy, x/z * fy, 0,fy/z, -y * fy/z_2;

            H.block(i*6,i*6,6,6) += jacobian_Ti.transpose() * jacobian_Ti;
            /// 请补充完整作业信息矩阵块的计算
            H.block(j*3 + 6*poseNums,j*3 + 6*poseNums,3,3) +=jacobian_Pj.transpose() * jacobian_Pj;
            H.block(i*6,j*3 + 6*poseNums, 6,3) += jacobian_Ti.transpose() * jacobian_Pj;
            H.block(j*3 + 6*poseNums,i*6 , 3,6) += jacobian_Pj.transpose() * jacobian_Ti;
        }
    }

//    std::cout << H << std::endl;
//    Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> saes(H);
//    std::cout << saes.eigenvalues() <<std::endl;

    // 奇异值分解
    Eigen::JacobiSVD<Eigen::MatrixXd> svd(H, Eigen::ComputeThinU | Eigen::ComputeThinV);
    // 调用svd对象的singularValues()成员函数，矩阵H的奇异值
    std::cout << svd.singularValues() <<std::endl;
    
    // 于一个矩阵而言，它的奇异值越大，表示它的特征、结构和变换等信息越重要。
    // 而奇异值越小，则说明这部分信息对矩阵的影响越小


    return 0;
}
