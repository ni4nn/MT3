#include "MyMath.h"
#include<cmath>
#include<Novice.h>

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