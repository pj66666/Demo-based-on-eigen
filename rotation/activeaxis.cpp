#include <iostream>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <gflags/gflags.h>
using namespace std;

#define M_PI       3.14159265358979323846 

Eigen::Matrix3d YPR2Rotation(double yaw,double pitch, double roll);



/*绕动轴Z-Y-X旋转，即ypr的旋转方式.动轴就是欧拉角，非常好理解.先转的放前面!*/

/*
但要注意的是，虽然是动轴，但并不是按每次旋转后的那个轴去旋转。--- 类似于下面程序的形式
仔细思考下欧拉角那个绕轴旋转的公式，表示一个坐标系到另一个坐标系的旋转，这都是相对量，而不是绝对量！
我们可以把第一个坐标系永远看作单位矩阵，毕竟它们的关系是相对的！所以，我们任然是代公式可以，用角轴也可以！

而且，如果我们是按照每一次旋转之后的xyz轴去旋转，那么先转的放前面必定是错误的！比如下面这种格式
Eigen::AngleAxisd roll_x = Eigen::AngleAxisd(roll, yaw_z * Eigen::Vector3d::UnitX());
*/

DEFINE_double(x1, 1, "the first frame of x coordinate");
DEFINE_double(y1, 1, "the first frame of y coordinate");
DEFINE_double(z1, 0, "the first frame of z coordinate");

DEFINE_double(x2, 1, "the second frame of x coordinate");
DEFINE_double(y2, 0, "the second frame of y coordinate");
DEFINE_double(z2, -1, "the second frame of z coordinate");

int main(int argc, char** argv) {

    gflags::ParseCommandLineFlags(&argc, &argv, true);

    double yaw = M_PI / 2;
    double pitch = 0;
    double roll = -M_PI / 2;
    /********************确定两个坐标系中相同向量的坐标**************************************/ 

    Eigen::Vector3d v_1(FLAGS_x1, FLAGS_y1, FLAGS_z1);     // 旋转前的点  在第1个坐标系中点（1，1，1）
    Eigen::Vector3d v_R1;             // 旋转后的点 第1个坐标系中点（1，1，1）在第2个坐标系坐标(1,-1,-1)
    Eigen::Vector3d v_2(FLAGS_x2, FLAGS_y2, FLAGS_z2);     // 第2个坐标系中点（1，-1，-1）
    Eigen::Vector3d v_R2;             // 第2个坐标系中点（1，-1，-1）在第1个坐标系坐标(1,1,1)

    /********************Method 1: 利用角轴来计算*********************************************/

    // 绕动轴旋转一定的角度，顺序Z Y X,   即ypr  先转的放前面
    Eigen::Matrix3d R12_;

    // 第1步，绕z轴旋转M_PI / 2，
    Eigen::AngleAxisd yaw_z = Eigen::AngleAxisd(yaw, Eigen::Vector3d::UnitZ());

    // 第2步，绕x轴旋转-M_PI / 2
    Eigen::AngleAxisd roll_x_1 = Eigen::AngleAxisd(roll, Eigen::Vector3d::UnitX());

    R12_ = yaw_z.toRotationMatrix()*roll_x_1.toRotationMatrix();


    v_R1 = R12_.transpose() * v_1;    // 因为是要把1坐标系下点投影到 2坐标系下，所以需要的是旋转矩阵R21（ = R12.transpose()；）
    cout << "Method 1: 利用角轴来计算 " << v_R1.transpose() << endl;

    // R12_两次含义：一个是把坐标轴1转到坐标轴2.一个是把坐标系2中点投影到坐标系1
    v_R2 = R12_*v_2;
    cout << "检验：坐标系2投影到坐标系1中 " << v_R2.transpose() << endl << endl;


    /********************Method 2: 利用公式来计算*********************************************/
    Eigen::Matrix3d YPR = YPR2Rotation(yaw,pitch,roll);
    Eigen::Vector3d v = YPR * v_2;
    cout << "Method 2: 利用公式来计算 " << v.transpose() << endl << endl;
}


Eigen::Matrix3d YPR2Rotation(double yaw,double pitch, double roll)
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

    R = Rz * Ry * Rx;   // 动轴，绕zyx，先转的放前面

    return R;
}