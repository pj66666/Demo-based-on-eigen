#include <iostream>
#include <Eigen/Dense>
#include <chrono>

using namespace Eigen;
using namespace std;
using namespace std::chrono;

int main() {
    // 初始化随机矩阵A和向量b
    MatrixXf A = MatrixXf::Random(100, 100);
    VectorXf b = VectorXf::Random(100);

    // QR分解求解Ax = b
    auto start = high_resolution_clock::now();
    VectorXf x_qr = A.householderQr().solve(b);
    // VectorXf x_qr = A.colPivHouseholderQr().solve(b);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "QR分解求解耗时: " << duration.count() << "微秒" << endl;

    // SVD分解求解Ax = b
    start = high_resolution_clock::now();
    VectorXf x_svd = A.jacobiSvd(ComputeThinU | ComputeThinV).solve(b);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "SVD分解求解耗时: " << duration.count() << "微秒" << endl;

    // .norm()计算2范数
    double res1 = (A * x_qr - b).norm();
    double res2 = (A * x_svd - b).norm();

    std::cout << "ColPivHouseholderQR残差: " << res1 << std::endl;
    std::cout << "SVD残差: " << res2 << std::endl;

    return 0;
}
