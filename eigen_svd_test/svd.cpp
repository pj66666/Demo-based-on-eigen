#include <iostream>
#include <Eigen/Dense>

int main() {
    // 定义一个3x3的矩阵
    Eigen::MatrixXd A(4, 5);
    A << 1, 0, 0, 0, 2,
         0, 0, 3, 0, 0,
         0, 0, 0, 0, 0,
         0, 4, 0, 0, 0;

    // 求解A^T*A特征值和特征向量
    Eigen::EigenSolver<Eigen::MatrixXd> solver1(A.transpose() * A);
    Eigen::VectorXd eigenvaluesV = solver1.eigenvalues().real();
    Eigen::MatrixXd eigenvectorsV = solver1.eigenvectors().real();

    // 求解A*A^T特征值和特征向量
    Eigen::EigenSolver<Eigen::MatrixXd> solver2(A * A.transpose());
    Eigen::VectorXd eigenvaluesU = solver2.eigenvalues().real();
    Eigen::MatrixXd eigenvectorsU = solver2.eigenvectors().real();

    Eigen::JacobiSVD<Eigen::MatrixXd> svd(A, Eigen::ComputeThinU | Eigen::ComputeThinV);
    
    // 调用svd对象的singularValues()成员函数，矩阵D的奇异值
    Eigen::VectorXd delta = svd.singularValues();
    std::cout << "奇异值分解中的奇异值singularValues:" << delta.transpose() << std::endl;

    // 取最小奇异值对应的右奇异向量
    // Eigen::Vector4d u4 = svd.matrixU().col(3);
    Eigen::MatrixXd U = svd.matrixU();
    Eigen::MatrixXd V = svd.matrixV();

    //
    std::cout << "A^T*A 的特征值Eigenvalues:"  << std::endl << eigenvaluesV << std::endl;
    std::cout << "A^T*A 的特征向量Eigenvectors:"  << std::endl << eigenvectorsV << std::endl;
    std::cout << "A奇异值分解中的矩阵 V:" << std::endl << V << std::endl;


    std::cout << "A*A^T 的特征值Eigenvalues:"  << std::endl << eigenvaluesU << std::endl;
    std::cout << "A*A^T 的特征向量Eigenvectors:"  << std::endl << eigenvectorsU << std::endl;
    std::cout << "A奇异值分解中的矩阵 U:" << std::endl << U << std::endl;


    return 0;
}


// #include <iostream>
// #include <Eigen/Dense>

// int main() {
//     Eigen::MatrixXd A(3, 2);
//     A << 1, 2,
//          3, 4,
//          5, 6;

//     // 计算 A^T A 的特征值和特征向量
//     Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> eigensolver(A.transpose() * A);
//     Eigen::VectorXd eigenvalues = eigensolver.eigenvalues();
//     Eigen::MatrixXd eigenvectors = eigensolver.eigenvectors();

//     // 进行奇异值分解
//     Eigen::JacobiSVD<Eigen::MatrixXd> svd(A, Eigen::ComputeThinU | Eigen::ComputeThinV);
//     Eigen::MatrixXd U = svd.matrixU();
//     Eigen::MatrixXd V = svd.matrixV();

//     // 输出结果
//     std::cout << "A^T A 的特征值:" << std::endl << eigenvalues << std::endl;
//     std::cout << "A^T A 的特征向量:" << std::endl << eigenvectors << std::endl;
//     std::cout << "奇异值分解中的矩阵 V:" << std::endl << V << std::endl;

//     return 0;
// }
