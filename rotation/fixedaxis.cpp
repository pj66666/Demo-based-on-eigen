#include <iostream>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <gflags/gflags.h>

using namespace std;

#define M_PI       3.14159265358979323846 

Eigen::Matrix3d RPY2Rotation(double roll, double pitch, double yaw);

/*绕固定轴X-Y-Z旋转，即rpy的旋转方式,先转的放后面*/

DEFINE_double(x1, 1, "the first frame of x coordinate");
DEFINE_double(y1, 1, "the first frame of y coordinate");
DEFINE_double(z1, 0, "the first frame of z coordinate");


int main(int argc, char** argv) {

    gflags::ParseCommandLineFlags(&argc, &argv, true);

    Eigen::Vector3d v(FLAGS_x1, FLAGS_y1, FLAGS_z1);      // 旋转前的点   (1,1,0)
    Eigen::Vector3d v_R;             // 旋转后的点	 (1,0,-1)
    // cout.precision(3);

    /********************Method 1: 利用角轴来计算*********************************************/

    // 绕固定轴旋转一定的角度，顺序X Y Z,   即rpy  先转的放后面
    Eigen::Matrix3d R12;
    R12 = Eigen::AngleAxisd(M_PI / 2, Eigen::Vector3d::UnitZ())
        * Eigen::AngleAxisd(0, Eigen::Vector3d::UnitY())
        * Eigen::AngleAxisd(-M_PI / 2, Eigen::Vector3d::UnitX());

    v_R = R12.transpose() * v;    // 因为是要把1坐标系下点投影到 2坐标系下，所以需要的是旋转矩阵R21（ = R12.transpose()；）
    cout << "Method 1: 利用角轴来计算 " << v_R.transpose() << endl;// 2系下的坐标
    // cout << R12.transpose() << endl;


    /********************Method 2: 利用公式来计算*********************************************/
    Eigen::Matrix3d R12_ = RPY2Rotation(-M_PI / 2, 0, M_PI / 2);    // 套公式算出来的结果的精度是要更高一点的！所以看起来会有点不一样
    Eigen::Vector3d v_R1 = R12_.transpose() * v;
    cout << "Method 2: 利用公式来计算 " << v_R1.transpose() << endl;
}

// 固定轴   rpy   先转的放后面
Eigen::Matrix3d RPY2Rotation(double roll, double pitch, double yaw)
{

    Eigen::Matrix3d R, Rx, Ry, Rz;

    Rx << 1.0, 0.0, 0.0,
        0.0, cos(roll), -sin(roll),
        0.0, sin(roll), cos(roll);

    Ry << cos(pitch), 0.0, sin(pitch),
        0.0, 1.0, 0.0,
        -sin(pitch), 0.0, cos(pitch);

    Rz << cos(yaw), -sin(yaw), 0.0,
        sin(yaw), cos(yaw), 0.0,
        0.0, 0.0, 1.0;

    R = Rz * Ry * Rx;   //  定轴，绕xyz，先转的放后面

    return R;
}