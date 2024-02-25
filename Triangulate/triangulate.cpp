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

    Eigen::Vector2d uv;    // 这帧图像观测到的特征坐标
};
int main()
{

    int poseNums = 10;
    double radius = 8;
    double fx = 1.;
    double fy = 1.;
    std::vector<Pose> camera_pose;
    for(int n = 0; n < poseNums; ++n ) {
        double theta = n * 2 * M_PI / ( poseNums * 4); // 1/4 圆弧
        // 绕 z轴 旋转
        Eigen::Matrix3d R;
        R = Eigen::AngleAxisd(theta, Eigen::Vector3d::UnitZ());
        Eigen::Vector3d t = Eigen::Vector3d(radius * cos(theta) - radius, radius * sin(theta), 1 * sin(2 * theta));
        camera_pose.push_back(Pose(R,t));
    }

    // 随机数生成 1 个 三维特征点
    std::default_random_engine generator;
    std::uniform_real_distribution<double> xy_rand(-4, 4.0);
    std::uniform_real_distribution<double> z_rand(8., 10.);
    double tx = xy_rand(generator);
    double ty = xy_rand(generator);
    double tz = z_rand(generator);

    Eigen::Vector3d Pw(tx, ty, tz);
    // 这个特征从第三帧相机开始被观测，i=3
    int start_frame_id = 3;
    int end_frame_id = poseNums;        
    for (int i = start_frame_id; i < end_frame_id; ++i) {   // 3-10
        Eigen::Matrix3d Rcw = camera_pose[i].Rwc.transpose();
        Eigen::Vector3d Pc = Rcw * (Pw - camera_pose[i].twc);

        double x = Pc.x();
        double y = Pc.y();
        double z = Pc.z();

        camera_pose[i].uv = Eigen::Vector2d(x/z,y/z);
    }
    
    /// TODO::homework; 请完成三角化估计深度的代码
    // 遍历所有的观测数据，并三角化
    Eigen::Vector3d P_est;           // 结果保存到这个变量
    P_est.setZero();
    /* your code begin */
    int D_dim_row = 2 * (end_frame_id - start_frame_id);
    int D_dim_col = 4;
    Eigen::MatrixXd D = Eigen::MatrixXd::Zero(D_dim_row, D_dim_col);
    
    // 每一个特征点可以提供两行约束
    for(int i = start_frame_id; i < end_frame_id; i++){
        Eigen::MatrixXd P = Eigen::MatrixXd::Zero(3, 4);

        // 构建投影矩阵
        //  P.block<3,3>(0,0) = camera_pose[i].Rwc.transpose();
        P.block(0, 0, 3, 3) = camera_pose[i].Rwc.transpose();   // Rcw
        P.block(0, 3, 3, 1) = -camera_pose[i].Rwc.transpose() * camera_pose[i].twc;     // tcw

        // 归一化坐标点(u,v,1)----当前帧-----在Eigen库中，可以使用( )操作符或者[ ]操作符---或uv.x() uv.y
        double x = camera_pose[i].uv[0];
        double y = camera_pose[i].uv[1];

        // 代入公式----每一个特征点可以提供两行约束
        D.block(2 * (i - start_frame_id), 0, 1 , 4) = x * P.row(2) - P.row(0);  
        D.block(2 * (i - start_frame_id) + 1, 0, 1 , 4) = y * P.row(2) - P.row(1);
    }

    Eigen::JacobiSVD<Eigen::MatrixXd> svd(D, Eigen::ComputeThinU | Eigen::ComputeThinV);
    // Eigen::JacobiSVD<Eigen::MatrixXd> svd(D.transpose()*D, Eigen::ComputeThinU | Eigen::ComputeThinV);
    // 调用svd对象的singularValues()成员函数，矩阵D的奇异值
    Eigen::Vector4d delta = svd.singularValues();
    std::cout << delta.transpose() << std::endl;

    if(delta(3) * 1e-3 > delta(2)){   // 一般来讲奇异值都是从小到大，只要视差合理，这种极端情况不会出现
        std::cout << "The parallax is not enough" << std::endl;
        return -1;
    }
    // 取最小奇异值对应的右奇异向量-------注意上面是对A^T*A进行了SVD分解，相当于对一个对称矩阵进行特征分解，两边UV都是一样的，所以这里取U也可以。但如果是对A进行SVD分解，只能是取V！
    // Eigen::VectorXd u4 = svd.matrixU().col(3);
    Eigen::VectorXd u4 = svd.matrixV().col(3);
    
    if(u4(3) != 0 && u4(2) / u4(3) > 0){
        P_est = u4.head<3>() / u4(3);
    }
    
    /* your code end */
    
    std::cout <<"ground truth: \n"<< Pw.transpose() <<std::endl;
    std::cout <<"your result: \n"<< P_est.transpose() <<std::endl;

    return 0;
}
