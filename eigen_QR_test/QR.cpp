#include <iostream>
#include <Eigen/Dense>

int main() {
    // 任何矩阵都有QR分解，满秩矩阵的QR分解唯一
    Eigen::MatrixXd A(3, 3); 

    A << 6, 5, 0,
        5, 1, 4,
        0, 4, 3;

    /**************1  Householder 变换**********************/
    Eigen::HouseholderQR<Eigen::MatrixXd> qr1(A);
    Eigen::MatrixXd Q_Householder = qr1.householderQ();  // 6*6
    // 用于获取矩阵的上三角部分
    Eigen::MatrixXd R_Householder = qr1.matrixQR().triangularView<Eigen::Upper>();   // 6*3


    /**************2   Givens吉文斯旋转变换**********************/
    Eigen::ColPivHouseholderQR<Eigen::MatrixXd> qr2(A);
    Eigen::MatrixXd Q_Givens = qr2.matrixQ();
    Eigen::MatrixXd R_Givens = qr2.matrixR().template triangularView<Eigen::Upper>();



    std::cout << "Q_Householder matrix:\n" << Q_Householder << std::endl;
    std::cout << "R_Householder matrix:\n" << R_Householder << std::endl;

    std::cout << "Q_Givens matrix:\n" << Q_Givens << std::endl;
    std::cout << "R_Givens matrix:\n" << R_Givens << std::endl;


    /**************3  验证QR乘积**********************/
    Eigen::MatrixXd AA = Q_Householder * R_Householder;
    Eigen::MatrixXd AB = Q_Givens * R_Givens;


    std::cout << "AA matrix:\n" << AA << std::endl;
    std::cout << "AB matrix:\n" << AB << std::endl;

    return 0;
}

