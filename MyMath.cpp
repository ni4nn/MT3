#include "MyMath.h"
#include<cmath>
#include<Novice.h>
#include <cassert>

Vector3 MyMath::Add(const Vector3& v1, const Vector3& v2)
{
	Vector3 v3;

	v3.x = v1.x + v2.x;
	v3.y = v1.y + v2.y;
	v3.z = v1.z + v2.z;

	return v3;
}

Vector3 MyMath::Subtract(const Vector3& v1, const Vector3& v2)
{
	Vector3 v3;

	v3.x = v1.x - v2.x;
	v3.y = v1.y - v2.y;
	v3.z = v1.z - v2.z;

	return v3;
}

Vector3 MyMath::Multiply(float scalar, const Vector3& v)
{
	Vector3 v3;

	v3.x = v.x * scalar;
	v3.y = v.y * scalar;
	v3.z = v.z * scalar;

	return v3;
}

float  MyMath::Dot(const Vector3& v1, const Vector3& v2)
{
	float v3;

	v3 = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);

	return v3;
}

float  MyMath::Length(const Vector3& v)
{
	float result;

	result = sqrtf((v.x * v.x) + (v.y * v.y) + (v.z * v.z));

	return result;
}

Vector3 MyMath::Normalize(const Vector3& v)
{
	Vector3 result;
	float length;

	length = Length(v);

	result.x = v.x / length;
	result.y = v.y / length;
	result.z = v.z / length;

	return result;
}


void MyMath::VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
}


Vector3 MyMath::Transform(const Vector3& vector, const Matrix4x4& matrix)
{
	Vector3 result;

	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0]+vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
	result.y= vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
	result.z= vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];
	float w=vector.x*matrix.m[0][3]+vector.y*matrix.m[1][3]+ vector.z * matrix.m[3][3] + 1.0f * matrix.m[3][3];

	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;

	return result;
	

}


//
//Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rot, const Vector3& translate) {
//
//    Matrix4x4 scallMatrix,
//        rotate, rotateX, rotateY, rotateZ,
//        translateMatrix,
//        returnMat;
//
//    // スケール行列作成
//    scallMatrix = { scale.x, 0, 0, 0,
//                0, scale.y, 0, 0,
//                0, 0, scale.z, 0,
//                0, 0, 0, 1 };
//
//    // XYZ回転行列作成
//    rotateX = { 1, 0, 0, 0,
//                cosf(rot.x), sinf(rot.x), 0,
//                0,-sinf(rot.x), cosf(rot.x), 0,
//                0, 0, 0, 1 };
//
//    rotateY = { cosf(rot.y), 0,-sinf(rot.y), 0,
//                0, 1, 0, 0,
//                sinf(rot.y), 0, cosf(rot.y), 0,
//                0, 0, 0, 1 };
//
//    rotateZ = { cosf(rot.z), sinf(rot.z), 0, 0,
//                -sinf(rot.z), cosf(rot.z), 0, 0,
//                0, 0, 1, 0,
//                0, 0, 0, 1 };
//
//    // XYZ回転行列の合成(Z*X*Y)
//    rotate = MatrixMultiply(rotateZ, rotateX);
//    // ↑の結果＊Y軸回転
//    rotate = MatrixMultiply(rotate, rotateY);
//
//    // 平行移動行列作成
//    translateMatrix = { 1, 0, 0, 0,
//                    0, 1, 0, 0,
//                    0, 0, 1, 0,
//                    translate.x, translate.y, translate.z, 1 };
//
//    // スケール＊回転＊平行移動をワールド変換行列に
//    returnMat = MatrixMultiply(scallMatrix, rotate);
//    returnMat = MatrixMultiply(returnMat, translateMatrix);
//
//    return returnMat;
//}

