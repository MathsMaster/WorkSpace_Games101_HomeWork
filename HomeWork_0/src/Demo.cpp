#include <stdio.h>
#include <iostream>
#include <cmath>
#include<eigen3/Eigen/Core>
#include<eigen3/Eigen/Dense>

using namespace std;
using namespace Eigen;

Vector2d rotate(int array[2]);
Vector3d translation(double x, double y);
Vector3d transform(double x, double y);


/**
 * @brief 将坐标点(2,1)绕原点逆时针旋转45度，在进行平移
 *
 * @return int
 */
int main()
{
    double a = sqrt(2); // 开根号
    cout << "sqrt(2) : " << a << endl;
    // double aa = 2^(1/2);//开根号
    // cout << "2^(1/2) : " << aa << endl;
    double b = pow(2, 4); // 4次方
    cout << "pow(2,4) : " << b << endl;
    // double bb = 2^4;//4次方
    // cout << "2^(4) : " << bb << endl;
    double c = pow(27, 1.0 / 3.0);
    cout << "pow(27,1.0/3.0) : " << c << endl;
    double d = pow(2, 1.0 / 3.0);
    cout << "pow(2,1.0/3.0) : " << d << endl;

    Eigen::Matrix2d mat;
    mat(0, 0) = pow(2, 4);
    mat(1, 0) = 2.5;
    mat(0, 1) = -1;
    mat(1, 1) = mat(1, 0) + mat(0, 1);
    cout << mat << "\n"
         << endl;

    cout << "Hello World." << endl;

    cout << "\n\n\n"
         << endl;

    cout << "\n对坐标(2,1)进行旋转" << endl;
    // 对坐标(2,1)进行旋转
    int array[2] = {2, 1};
    Vector2d result = rotate(array);
    cout << "旋转后的结果 : " << result.x() << " , " << result.y() << endl;
    cout << "旋转后的结果 : " << result[0] << " , " << result[1] << endl;

    cout << "\n对旋转后坐标进行水平1,纵轴2平移" << endl;
    //
    Vector3d vector = translation(result[0], result[1]);
    cout << "平移后的结果 : " << vector.x() << " , " << vector.y() << endl;
    cout << "平移后的结果 : " << vector[0] << " , " << vector[1] << endl;

    //
    cout << "\n对坐标(2,1)进行齐次坐标变换" << endl;
    Vector3d vec = transform(2,1);
    cout << "齐次变换后的结果 : " << vec.x() << " , " << vec.y() << endl;
    cout << "齐次变换后的结果 : " << vec[0] << " , " << vec[1] << endl;
    return 0;
}

// C++里进行矩阵旋转的函数,传入一个数组，经过旋转后进行返回
// 旋转矩阵的形式「cosθ   -sinθ
//               sinθ  cosθ」

Vector2d rotate(int array[2])
{
    // 绕原点逆时针旋转45度
    // 定义2X2的矩阵
    Matrix2d mat;
    mat(0, 0) = sqrt(2) / 2;
    mat(0, 1) = -sqrt(2) / 2;
    mat(1, 0) = sqrt(2) / 2;
    mat(1, 1) = sqrt(2) / 2;

    cout << "旋转矩阵:" << mat << endl;

    // 定义2X1的列向量
    Vector2d vec(2, 1);
    // 矩阵和向量相乘
    Vector2d result = mat * vec;

    return result;
}

/**
 * @brief 在对坐标进行平移时，二位坐标需要使用3X3的矩阵来进行计算;
 * 如果是3维坐标，则需要使用4X4的矩阵来进行计算
 * 平移矩阵:
 *  「1 , 0, tx
 *    0 , 1, ty
 *    0 , 0, 1」
 */
Vector3d translation(double x, double y)
{
    //
    Matrix3d matrix;

    matrix << 1, 0, 1,
        0, 1, 2,
        0, 0, 1;
    Vector3d vec(x, y, 1);

    Vector3d vector = matrix * vec;

    return vector;
}

/**
 * @brief 使用齐次坐标进行变换
 *
 * @param x
 * @param y
 * @return Vector3d
 */
Vector3d transform(double x, double y)
{
    // 原坐标进行齐次化后
    Vector3d vector(x, y, 1);
    // 对变化矩阵进行齐次化
    Matrix3d matrix;
    matrix << sqrt(2) / 2, -sqrt(2) / 2, 1,
        sqrt(2) / 2, sqrt(2) / 2, 2,
        0, 0, 1;
    Vector3d result = matrix * vector;
    return result;
}