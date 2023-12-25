#include <iostream>
#include <Eigen/Dense>


/*Eigen::Map：允许将一个外部的内存区域映射到一个Eigen对象上，而无需进行额外的内存拷贝*/
/*避免内存拷贝：当处理大型数据时，避免了不必要的内存复制是非常重要的，因为它可以节省内存和提高性能。

与外部库的交互：Eigen::Map 允许我们将Eigen库与其他使用不同数据结构的库进行无缝集成。例如，将一个C风格数组映射为Eigen矩阵，可以方便地使用Eigen的数学运算符和函数。

减少资源占用：在某些情况下，特别是在内存受限的环境下，避免复制数据可以节省大量内存。*/

int main() {
    double data[3] = {1.0, 2.0, 3.0};

    // 将 data 数组映射为一个 Eigen 向量
    Eigen::Map<Eigen::VectorXd> vec(data, 3); 

    // 使用 Eigen 操作
    vec = vec * 2.0;

    // data 数组也被修改了
    for (int i = 0; i < 3; ++i) {
        std::cout << data[i] << " "; // 输出 2 4 6
    }

    return 0;
}
