#include <stdio.h>
#include <iostream>
#include <Dense>
#include <cmath>

using namespace std;
using namespace Eigen;
/**
 * @brief Model变换矩阵和投影矩阵
 *     1,构建一个矩阵,完成在三维空间中，绕Z轴的任意角度的旋转
 *     2,完成透视投影到正交投影 这个过程的变换
 *     3,构建一个函数，完成绕过原点的任意轴的旋转
 *
 * @return int
 */

Vector3d getVectorByZRoate(int[3], double degress);
double *getVectorByAnyRoate(double array[3], Vector3d vector_3d, double degress);

int main()
{
    cout << "Hello World!" << std::endl;
    cout << "3D空间中绕Z轴旋转:" << std::endl;
    //
    int array[3] = {2, 256, 221};//待旋转的点
    Vector3d vec_1 = getVectorByZRoate(array, 180); // 绕Z轴旋转180度
    cout << "初始点 : [" << array[0] << "," << array[1] << "," << array[2] << "]" << endl;
    cout << "绕Z轴旋转后的向量结果 : [" << vec_1.x() << "," << vec_1[1] << "," << vec_1.z() << "]" << endl;

    cout << "\n\n3D空间中绕原点的任意轴旋转:" << std::endl;
    Vector3d vec_n(0, 1.0, 1.0);//旋轴的向量
    double arr_source[3] = {0, 0, 1};//待旋转的点
    double *result = getVectorByAnyRoate(arr_source, vec_n, 180.0);
    cout << "初始点 : [" << arr_source[0] << "," << arr_source[1] << "," << arr_source[2] << "]" << endl;
    cout << "绕原点的轴旋转后的向量结果 : [" << result[0] << "," << result[1] << "," << result[2] << "]" << endl;
}

/**
 * @brief 进行模型变换完成透视投影的矩阵变换
 *      1,先完成平面的挤压缩放的操作
 *      2,再进行透视投影到正交投影的变换
 * 
 * 思路:
 *     在观察物体时,需要先确定相机所在的位置(当前假设在原点)
 *                  再确定观察的方向(默认为-Z轴的方向)
 *                  再确定相机的倾斜，这里默认和Y轴一致。
 *                 （这里相当于默认相机在原点位置,看向-Z轴方向,水平角度与Y轴垂直）
 * 
 *      第二步:确定屏幕所在的位置,包括屏幕的宽高(默认屏幕中点在-Z 轴上)
 *      第三步:确定所要观察的对象位置。
 *      
 *      这里需要多少个变量？    
 *          屏幕 宽width,高height,距离原点距离 zNear
 *          被观察范围的距离 原点距离 zFar.
 * 
 */
void getModelTransform()
{

}




/**
 * @brief Get the Vector By Z Roate object
 *
 * @param a 传入的旋转角度，这里以弧度进行计算
 * @return Vector3d
 */
Vector3d getVectorByZRoate(int array[3], double degress)
{

    double roateRate = degress * M_PI / 180.0;

    // 创建绕Z轴旋转的4维矩阵
    Matrix4d matrix;
    matrix << cos(roateRate), -sin(roateRate), 0, 0,
        sin(roateRate), cos(roateRate), 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1;

    Vector4d vector(array[0], array[1], array[2], 1);

    Vector4d result4d = matrix * vector;
    Vector3d result3d(result4d.x(), result4d.y(), result4d[2]);
    return result3d;
}

/**
 * @brief 围绕过原点的任意轴进行任意角度的选择
 *
 * @param array 待旋转的坐标点
 * @param degress
 * @return vector_3d 旋转的轴
 */
double *getVectorByAnyRoate(double array_source[3], Vector3d vector_n, double degress)
{
    double rotateDegress = degress * M_PI / 180;
    // 将传入的坐标点构建成向量，方便计算
    Vector3d vec_value(array_source[0], array_source[1], array_source[2]);

    // 构建选择矩阵

    Matrix3d matrix_1 = cos(rotateDegress) * Matrix3d::Identity(); // 构建单位阵
    Matrix3d matrix_2 = vector_n * (vector_n.transpose()) * (1.0 - cos(rotateDegress));
    Matrix3d matrix_temp(3, 3); // 创建3X3的矩阵
    matrix_temp(0, 0) = 0;
    matrix_temp(0, 1) = -vector_n[2];
    matrix_temp(0, 2) = vector_n[1];
    matrix_temp(1, 0) = vector_n[2];
    matrix_temp(1, 1) = 0;
    matrix_temp(1, 2) = vector_n[0];
    matrix_temp(2, 0) = -vector_n[1];
    matrix_temp(2, 1) = vector_n[0];
    matrix_temp(2, 2) = 0;
    Matrix3d matrix_3 = sin(rotateDegress) * matrix_temp;

    // 最后得到的旋转矩阵
    Matrix3d rotateMatrix = matrix_1 + matrix_2 + matrix_3;

    // 进行旋转
    Vector3d vec_result = rotateMatrix * vec_value;

    //动态分配数组返回
    double* arr = new double[3];
    arr[0] = vec_result[0];
    arr[1] = vec_result[1];
    arr[2] = vec_result[2];
    return arr;
}
