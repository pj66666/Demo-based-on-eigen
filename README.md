# eigen_test
 Here is a set of tests for the Eigen library, including rotations, mappings, and more.
更多参考博客https://blog.csdn.net/qq_49561752?spm=1000.2115.3001.5343
# 1 pose_generate
实际会生成三维路标点和位姿，下图以绿色表示位姿，蓝色表示路标点。

![image](https://github.com/pj66666/eigen_test/assets/68932539/c628ba87-8fb2-4673-916b-82cff0cc8682)
![image](https://github.com/pj66666/eigen_test/assets/68932539/08c97118-d006-4a7e-903b-3fd502bcf216)


# 2 eigen_svd_test
![image](https://github.com/pj66666/eigen_test/assets/68932539/9545263a-5fff-4cac-89d9-6bf82f171c8f)


# 3 nullspace_test
详见博客https://blog.csdn.net/qq_49561752/article/details/136204850?spm=1001.2014.3001.5501
![image](https://github.com/pj66666/eigen_test/assets/68932539/2a1d5333-68fe-4c7b-b712-21554647694a)

 
# 4 rotation
详见博客https://blog.csdn.net/qq_49561752/article/details/130649489?spm=1001.2014.3001.5501
![测试](https://github.com/pj66666/eigen_test/assets/68932539/bbd04a95-35e3-45d2-836a-7917fbbd0a02)


# 5 QR
QR分解会用于左零空间投影、解线性方程、以及减小计算量等，Q是正交矩阵，R是上三角矩阵。
![image](https://github.com/pj66666/eigen_test/assets/68932539/b02dd518-1c1d-4414-b342-512ce9bafb01)


# 6 solve_liner_equation
给出了几种常见的求解线性方程Ax=b的方法，包括QR、SVD等等

# 7 Triangulate
三角化，利用仿真位姿，进行三角化实验验证。理论https://blog.csdn.net/qq_49561752/article/details/136285024?spm=1001.2014.3001.5501

![image](https://github.com/pj66666/eigen_test/assets/68932539/4817ebc9-9e9d-4749-bc20-4a15e712e74a)

# 8 the use of cmake
cmake笔记：https://blog.csdn.net/qq_49561752/article/details/136354062?spm=1001.2014.3001.5501
这里主要是对cmake中install的使用https://blog.csdn.net/qq_49561752/article/details/130585398?spm=1001.2014.3001.5501


