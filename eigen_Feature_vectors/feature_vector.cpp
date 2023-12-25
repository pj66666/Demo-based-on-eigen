#include <iostream>
#include <Eigen/Dense>

int main() {
    // 定义一个3x3的矩阵
    Eigen::MatrixXd A(3, 3);
    A << 1, 0, 0,
         0, 1, 0,
         0, 0, 1;

    // 使用Eigen库求解特征值和特征向量  如果 solver.eigenvalues() 返回了一个复数矩阵 complexEigenvalues，
    // 那么 solver.eigenvalues().real() 就会返回一个实数向量 eigenvalues
    Eigen::EigenSolver<Eigen::MatrixXd> solver(A);
    Eigen::VectorXd eigenvalues = solver.eigenvalues().real();
    Eigen::MatrixXd eigenvectors = solver.eigenvectors().real();

    // 输出特征值
    std::cout << "Eigenvalues:" << std::endl << eigenvalues << std::endl;

    // 输出特征向量
    std::cout << "Eigenvectors:" << std::endl << eigenvectors << std::endl;

    return 0;
}
