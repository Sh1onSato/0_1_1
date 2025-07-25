#include "Calculation.h"
#include <cmath> 
#include <numbers> 

Calculation::Vector3 Calculation::Add(const Vector3& a, const Vector3& b){
	return { a.x + b.x, a.y + b.y, a.z + b.z };
}

Calculation::Vector3 Calculation::Subtract(const Vector3& a, const Vector3& b) {
	return { a.x - b.x, a.y - b.y, a.z - b.z };
}

Calculation::Vector3 Calculation::Multiply(const Vector3& a, float b){
	return { a.x * b, a.y * b, a.z * b };
}
float Calculation::Dot(const Vector3& a, const Vector3& b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

float Calculation::Length(const Vector3& a){
	return std::sqrt(Dot(a, a));
}

Calculation::Vector3 Calculation::Normalize(const Vector3& a){
	float length = Length(a);
	if (length == 0) {
		return { 0, 0, 0 };
	}
	return { a.x / length, a.y / length, a.z / length };
}


void Calculation::VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label){
		Novice::ScreenPrintf(x, y, "%.02f", vector.x);
		Novice::ScreenPrintf(x + kColumnWidth, y, "x:%.02f", vector.y);
		Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z);
		Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
	}
Calculation::Matrix4x4 Calculation::Add(const Matrix4x4& a, const Matrix4x4& b)
{
	Matrix4x4 result;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.m[i][j] = a.m[i][j] + b.m[i][j];
		}
	}
	return result;
}

Calculation::Matrix4x4 Calculation::Subtract(const Matrix4x4& a, const Matrix4x4& b){
	Matrix4x4 result;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.m[i][j] = a.m[i][j] - b.m[i][j];
		}
	}
	return result;
}

Calculation::Matrix4x4 Calculation::Multiply(const Matrix4x4& a, const Matrix4x4& b) {
	Matrix4x4 result;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.m[i][j] = 0;
			for (int k = 0; k < 4; ++k) {
				result.m[i][j] += a.m[i][k] * b.m[k][j];
			}
		}
	}
	return result;
}

Calculation::Matrix4x4 Calculation::Inverse(const Matrix4x4& a) {
	Matrix4x4 result;
	// 逆行列の計算を実装する
	float det = a.m[0][3] * a.m[1][2] * a.m[2][1] * a.m[3][0] - a.m[0][2] * a.m[1][3] * a.m[2][1] * a.m[3][0] -
		a.m[0][3] * a.m[1][1] * a.m[2][2] * a.m[3][0] + a.m[0][1] * a.m[1][3] * a.m[2][2] * a.m[3][0] +
		a.m[0][2] * a.m[1][1] * a.m[2][3] * a.m[3][0] - a.m[0][1] * a.m[1][2] * a.m[2][3] * a.m[3][0] -
		a.m[0][3] * a.m[1][2] * a.m[2][0] * a.m[3][1] + a.m[0][2] * a.m[1][3] * a.m[2][0] * a.m[3][1] +
		a.m[0][3] * a.m[1][0] * a.m[2][2] * a.m[3][1] - a.m[0][0] * a.m[1][3] * a.m[2][2] * a.m[3][1] -
		a.m[0][2] * a.m[1][0] * a.m[2][3] * a.m[3][1] + a.m[0][0] * a.m[1][2] * a.m[2][3] * a.m[3][1] +
		a.m[0][3] * a.m[1][1] * a.m[2][0] * a.m[3][2] - a.m[0][1] * a.m[1][3] * a.m[2][0] * a.m[3][2] -
		a.m[0][3] * a.m[1][0] * a.m[2][1] * a.m[3][2] + a.m[0][0] * a.m[1][3] * a.m[2][1] * a.m[3][2] +
		a.m[0][1] * a.m[1][0] * a.m[2][3] * a.m[3][2] - a.m[0][0] * a.m[1][1] * a.m[2][3] * a.m[3][2] -
		a.m[0][2] * a.m[1][1] * a.m[2][0] * a.m[3][3] + a.m[0][1] * a.m[1][2] * a.m[2][0] * a.m[3][3] +
		a.m[0][2] * a.m[1][0] * a.m[2][1] * a.m[3][3] - a.m[0][0] * a.m[1][2] * a.m[2][1] * a.m[3][3] -
		a.m[0][1] * a.m[1][0] * a.m[2][2] * a.m[3][3] + a.m[0][0] * a.m[1][1] * a.m[2][2] * a.m[3][3];

	if (det == 0.0f) {
		return result = {};
	}
	float invDet = 1.0f / det;

	result.m[0][0] = invDet * (
		a.m[1][2] * a.m[2][3] * a.m[3][1] - a.m[1][3] * a.m[2][2] * a.m[3][1] +
		a.m[1][3] * a.m[2][1] * a.m[3][2] - a.m[1][1] * a.m[2][3] * a.m[3][2] -
		a.m[1][2] * a.m[2][1] * a.m[3][3] + a.m[1][1] * a.m[2][2] * a.m[3][3]);

	result.m[0][1] = invDet * (
		a.m[0][3] * a.m[2][2] * a.m[3][1] - a.m[0][2] * a.m[2][3] * a.m[3][1] -
		a.m[0][3] * a.m[2][1] * a.m[3][2] + a.m[0][1] * a.m[2][3] * a.m[3][2] +
		a.m[0][2] * a.m[2][1] * a.m[3][3] - a.m[0][1] * a.m[2][2] * a.m[3][3]);

	result.m[0][2] = invDet * (
		a.m[0][2] * a.m[1][3] * a.m[3][1] - a.m[0][3] * a.m[1][2] * a.m[3][1] +
		a.m[0][3] * a.m[1][1] * a.m[3][2] - a.m[0][1] * a.m[1][3] * a.m[3][2] -
		a.m[0][2] * a.m[1][1] * a.m[3][3] + a.m[0][1] * a.m[1][2] * a.m[3][3]);

	result.m[0][3] = invDet * (
		a.m[0][3] * a.m[1][2] * a.m[2][1] - a.m[0][2] * a.m[1][3] * a.m[2][1] -
		a.m[0][3] * a.m[1][1] * a.m[2][2] + a.m[0][1] * a.m[1][3] * a.m[2][2] +
		a.m[0][2] * a.m[1][1] * a.m[2][3] - a.m[0][1] * a.m[1][2] * a.m[2][3]);

	result.m[1][0] = invDet * (
		a.m[1][3] * a.m[2][2] * a.m[3][0] - a.m[1][2] * a.m[2][3] * a.m[3][0] -
		a.m[1][3] * a.m[2][0] * a.m[3][2] + a.m[1][0] * a.m[2][3] * a.m[3][2] +
		a.m[1][2] * a.m[2][0] * a.m[3][3] - a.m[1][0] * a.m[2][2] * a.m[3][3]);

	result.m[1][1] = invDet * (
		a.m[0][2] * a.m[2][3] * a.m[3][0] - a.m[0][3] * a.m[2][2] * a.m[3][0] +
		a.m[0][3] * a.m[2][0] * a.m[3][2] - a.m[0][0] * a.m[2][3] * a.m[3][2] -
		a.m[0][2] * a.m[2][0] * a.m[3][3] + a.m[0][0] * a.m[2][2] * a.m[3][3]);

	result.m[1][2] = invDet * (
		a.m[0][3] * a.m[1][2] * a.m[3][0] - a.m[0][2] * a.m[1][3] * a.m[3][0] -
		a.m[0][3] * a.m[1][0] * a.m[3][2] + a.m[0][0] * a.m[1][3] * a.m[3][2] +
		a.m[0][2] * a.m[1][0] * a.m[3][3] - a.m[0][0] * a.m[1][2] * a.m[3][3]);

	result.m[1][3] = invDet * (
		a.m[0][2] * a.m[1][3] * a.m[2][0] - a.m[0][3] * a.m[1][2] * a.m[2][0] +
		a.m[0][3] * a.m[1][0] * a.m[2][2] - a.m[0][0] * a.m[1][3] * a.m[2][2] -
		a.m[0][2] * a.m[1][0] * a.m[2][3] + a.m[0][0] * a.m[1][2] * a.m[2][3]);

	result.m[2][0] = invDet * (
		a.m[1][1] * a.m[2][3] * a.m[3][0] - a.m[1][3] * a.m[2][1] * a.m[3][0] +
		a.m[1][3] * a.m[2][0] * a.m[3][1] - a.m[1][0] * a.m[2][3] * a.m[3][1] -
		a.m[1][1] * a.m[2][0] * a.m[3][3] + a.m[1][0] * a.m[2][1] * a.m[3][3]);

	result.m[2][1] = invDet * (
		a.m[0][3] * a.m[2][1] * a.m[3][0] - a.m[0][1] * a.m[2][3] * a.m[3][0] -
		a.m[0][3] * a.m[2][0] * a.m[3][1] + a.m[0][0] * a.m[2][3] * a.m[3][1] +
		a.m[0][1] * a.m[2][0] * a.m[3][3] - a.m[0][0] * a.m[2][1] * a.m[3][3]);

	result.m[2][2] = invDet * (
		a.m[0][1] * a.m[1][3] * a.m[3][0] - a.m[0][3] * a.m[1][1] * a.m[3][0] +
		a.m[0][3] * a.m[1][0] * a.m[3][1] - a.m[0][0] * a.m[1][3] * a.m[3][1] -
		a.m[0][1] * a.m[1][0] * a.m[3][3] + a.m[0][0] * a.m[1][1] * a.m[3][3]);

	result.m[2][3] = invDet * (
		a.m[0][3] * a.m[1][1] * a.m[2][0] - a.m[0][1] * a.m[1][3] * a.m[2][0] -
		a.m[0][3] * a.m[1][0] * a.m[2][1] + a.m[0][0] * a.m[1][3] * a.m[2][1] +
		a.m[0][1] * a.m[1][0] * a.m[2][3] - a.m[0][0] * a.m[1][1] * a.m[2][3]);

	result.m[3][0] = invDet * (
		a.m[1][2] * a.m[2][1] * a.m[3][0] - a.m[1][1] * a.m[2][2] * a.m[3][0] -
		a.m[1][2] * a.m[2][0] * a.m[3][1] + a.m[1][0] * a.m[2][2] * a.m[3][1] +
		a.m[1][1] * a.m[2][0] * a.m[3][2] - a.m[1][0] * a.m[2][1] * a.m[3][2]);

	result.m[3][1] = invDet * (
		a.m[0][1] * a.m[2][2] * a.m[3][0] - a.m[0][2] * a.m[2][1] * a.m[3][0] +
		a.m[0][2] * a.m[2][0] * a.m[3][1] - a.m[0][0] * a.m[2][2] * a.m[3][1] -
		a.m[0][1] * a.m[2][0] * a.m[3][2] + a.m[0][0] * a.m[2][1] * a.m[3][2]);

	result.m[3][2] = invDet * (
		a.m[0][2] * a.m[1][1] * a.m[3][0] - a.m[0][1] * a.m[1][2] * a.m[3][0] -
		a.m[0][2] * a.m[1][0] * a.m[3][1] + a.m[0][0] * a.m[1][2] * a.m[3][1] +
		a.m[0][1] * a.m[1][0] * a.m[3][2] - a.m[0][0] * a.m[1][1] * a.m[3][2]);

	result.m[3][3] = invDet * (
		a.m[0][1] * a.m[1][2] * a.m[2][0] - a.m[0][2] * a.m[1][1] * a.m[2][0] +
		a.m[0][2] * a.m[1][0] * a.m[2][1] - a.m[0][0] * a.m[1][2] * a.m[2][1] -
		a.m[0][1] * a.m[1][0] * a.m[2][2] + a.m[0][0] * a.m[1][1] * a.m[2][2]);

	return result;

}

Calculation::Matrix4x4 Calculation::Transpose(const Matrix4x4& a) {
	Matrix4x4 result;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.m[i][j] = a.m[j][i];
		}
	}
	return result;
}

Calculation::Matrix4x4 Calculation::MakeIdentity4x4() {
	Matrix4x4 result;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (i == j) {
				result.m[i][j] = 1.0f;
			}
			else {
				result.m[i][j] = 0.0f;
			}
		}
	}
	return result;
}

Calculation::Matrix4x4 Calculation::MakeScaleMatrix(const Vector3& Scale) {
	Matrix4x4 result;
	result.m[0][0] = Scale.x;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;
	result.m[1][0] = 0.0f;
	result.m[1][1] = Scale.y;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;
	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = Scale.z;
	result.m[2][3] = 0.0f;
	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;

	return result;
}

Calculation::Matrix4x4 Calculation::MakeTranslationMatrix(const Vector3& Translate){
	Matrix4x4 result;
	result.m[0][0] = 1.0f;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;
	result.m[1][0] = 0.0f;
	result.m[1][1] = 1.0f;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;
	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = 1.0f;
	result.m[2][3] = 0.0f;
	result.m[3][0] = Translate.x;
	result.m[3][1] = Translate.y;
	result.m[3][2] = Translate.z;
	result.m[3][3] = 1.0f;

	return result;
}

Calculation::Vector3 Calculation::Transform(const Vector3& vector,const  Matrix4x4& matrix){
	Vector3 result;
	// 行列とベクトルの積を計算
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + matrix.m[3][3];

	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;

	return result;
}

Calculation::Matrix4x4 Calculation::MakeRotationXMatrix(float radian)
{
	Matrix4x4 result;

	float cosRadian = std::cosf(radian);
	float sinRadian = std::sinf(radian);

	result.m[0][0] = 1.0f;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = cosRadian;
	result.m[1][2] = sinRadian;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = -sinRadian;
	result.m[2][2] = cosRadian;
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;

	return result;
}

Calculation::Matrix4x4 Calculation::MakeRotationYMatrix(float radian){
	Matrix4x4 result;

	float cosRadian = std::cosf(radian);
	float sinRadian = std::sinf(radian);

	result.m[0][0] = cosRadian;
	result.m[0][1] = 0.0f;
	result.m[0][2] = -sinRadian;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = 1.0f;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = sinRadian;
	result.m[2][1] = 0.0f;
	result.m[2][2] = cosRadian;
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;

	return result;
}

Calculation::Matrix4x4 Calculation::MakeRotationZMatrix(float radian){
	Matrix4x4 result;

	float cosRadian = std::cosf(radian);
	float sinRadian = std::sinf(radian);

	result.m[0][0] = cosRadian;
	result.m[0][1] = sinRadian;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = -sinRadian;
	result.m[1][1] = cosRadian;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = 1.0f;
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;

	// 行列を返す
	return result;
}

Calculation::Matrix4x4 Calculation::MakeAffineMatrix(const Vector3& Scale, const Vector3& Rotate, const Vector3& Translate){
	Matrix4x4 result;
	
	Matrix4x4 scaleMatrix = MakeScaleMatrix(Scale);
	Matrix4x4 rotateXMatrix = MakeRotationXMatrix(Rotate.x);
	Matrix4x4 rotateYMatrix = MakeRotationYMatrix(Rotate.y);
	Matrix4x4 rotateZMatrix = MakeRotationZMatrix(Rotate.z);
	Matrix4x4 translationMatrix = MakeTranslationMatrix(Translate);

	result = Multiply(scaleMatrix, rotateXMatrix);
	result = Multiply(result, rotateYMatrix);
	result = Multiply(result, rotateZMatrix);
	result = Multiply(result, translationMatrix);

	// 結果を返す
	return result;
}

Calculation::Matrix4x4 Calculation::MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farCrip){
	Matrix4x4 result;
	
	result.m[0][0] = (1/aspectRatio)/(fovY/2);
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = 1/(fovY/2);
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = farCrip/(farCrip-nearClip);
	result.m[2][3] = 1.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = ( -nearClip*farCrip )/(farCrip-nearClip);
	result.m[3][3] = 0.0f;



	return result;
}

Calculation::Matrix4x4 Calculation::MakeOrthographicMatrix(float left, float top,float right,float bottom, float nearClip, float farClip){
	Matrix4x4 result;

	result.m[0][0] = (2/(right-left));
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = (2/(top-bottom));
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = 1.0f/(farClip-nearClip);
	result.m[2][3] = 0.0f;

	result.m[3][0] = (left+right)/(left-right);
	result.m[3][1] = (top+bottom)/(bottom-top);
	result.m[3][2] = nearClip/(nearClip-farClip);
	result.m[3][3] = 1.0f;


	return result;
}

Calculation::Matrix4x4 Calculation::MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth){
	Matrix4x4 result;

	result.m[0][0] = width/2;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = -height/2;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = maxDepth-minDepth;
	result.m[2][3] = 0.0f;

	result.m[3][0] = left+(width/2);
	result.m[3][1] = top+(height/2);
	result.m[3][2] = minDepth;
	result.m[3][3] = 1.0f;


	return result;
}

void Calculation::MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label){
	for (int row = 0; row < 4; ++row) {
		if (row == 0) {
			Novice::ScreenPrintf(x + 15, y, "%s", label);
		}
		for (int column = 0; column < 4; ++column) {

			Novice::ScreenPrintf(x + column * kColumnWidth, y + 20 + row * kRowHeight, "%6.02F", matrix.m[row][column]);
		}

	}
}
Calculation::Vector3 Calculation::Cross(const Vector3& a, const Vector3& b){
	Vector3 result;
	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;

	return result;
}

void Calculation::DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	const uint32_t kSubdivisions = 16;
	const float kLonEvery = float(2 * std::numbers::pi) / kSubdivisions;
	const float kLatEvery = float(std::numbers::pi) / kSubdivisions;
	for (uint32_t lotIndex = 0; lotIndex < kSubdivisions; ++lotIndex) {
		float lat = float(-std::numbers::pi) / 2 + lotIndex * kLatEvery;
		for (uint32_t lonIndex = 0; lonIndex < kSubdivisions; ++lonIndex) {
			float lon = lonIndex * kLonEvery;
			Vector3 a, b, c;
			a = {
			   sphere.center.x + sphere.radius * cosf(lat) * cosf(lon),
			   sphere.center.y + sphere.radius * sinf(lat),
			   sphere.center.z + sphere.radius * cosf(lat) * sinf(lon)
			};

			b = {
				sphere.center.x + sphere.radius * cosf(lat + kLatEvery) * cosf(lon),
				sphere.center.y + sphere.radius * sinf(lat + kLatEvery),
				sphere.center.z + sphere.radius * cosf(lat + kLatEvery) * sinf(lon)
			};

			c = {
				sphere.center.x + sphere.radius * cosf(lat) * cosf(lon + kLonEvery),
				sphere.center.y + sphere.radius * sinf(lat),
				sphere.center.z + sphere.radius * cosf(lat) * sinf(lon + kLonEvery)
			};

			Vector3 screenA = Transform(Transform(a, viewProjectionMatrix), viewportMatrix);
			Vector3 screenB = Transform(Transform(b, viewProjectionMatrix), viewportMatrix);
			Vector3 screenC = Transform(Transform(c, viewProjectionMatrix), viewportMatrix);

			Novice::DrawLine(int(screenA.x), int(screenA.y), int(screenB.x), int(screenB.y), color);
			Novice::DrawLine(int(screenA.x), int(screenA.y), int(screenC.x), int(screenC.y), color);
		}
	}
}

void Calculation::DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) {
	const float  kGridHalfWidth = 2.0f;

	const uint32_t kSubdivision = 10;

	const float kGridEvery = (kGridHalfWidth * 2.0f) / float(kSubdivision);

	for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex) {
		float x = -kGridHalfWidth + kGridEvery * xIndex;

		Vector3 start = { x, 0.0f, -kGridHalfWidth };

		Vector3 end = { x, 0.0f, kGridHalfWidth };

		Vector3 screenStart = Transform(Transform(start, viewProjectionMatrix), viewportMatrix);
		Vector3 screenEnd = Transform(Transform(end, viewProjectionMatrix), viewportMatrix);

		Novice::DrawLine(int(screenStart.x), int(screenStart.y), int(screenEnd.x), int(screenEnd.y), 0xAAAAAAFF);
	}

	for (uint32_t zIndex = 0; zIndex <= kSubdivision; ++zIndex) {

		float z = -kGridHalfWidth + kGridEvery * zIndex;

		Vector3 start = { -kGridHalfWidth, 0.0f, z };
		Vector3 end = { kGridHalfWidth, 0.0f, z };

		Vector3 screenStart = Transform(Transform(start, viewProjectionMatrix), viewportMatrix);
		Vector3 screenEnd = Transform(Transform(end, viewProjectionMatrix), viewportMatrix);

		//変換した座標を使って描画
		Novice::DrawLine(int(screenStart.x), int(screenStart.y), int(screenEnd.x), int(screenEnd.y), 0xAAAAAAFF);
	}

}

Calculation::Vector3 Calculation::Project(const Vector3& v1, const Vector3& v2){
	float v2LenSq = Dot(v2, v2);

	if (v2LenSq == 0.0f) {
		return { 0, 0, 0 };
	};

	float t = Dot(v1, v2) / v2LenSq;
	return Multiply(v2, t);
}

Calculation::Vector3 Calculation::Closestpoint(const Vector3& point, const Segment& segment){
	Vector3 toPoint = Subtract(point, segment.origin);
	float segLenSq = Dot(segment.diff, segment.diff);
	if (segLenSq == 0.0f) {
		return segment.origin;
	}
	float t = Dot(toPoint, segment.diff) / segLenSq;

	if (t < 0.0f) t = 0.0f;
	if (t > 1.0f) t = 1.0f;

	return Add(segment.origin, Multiply(segment.diff, t));
}

bool Calculation::IsCollision(const Triangle& triangle, const Segment& segment){
	Vector3 v0 = triangle.vertices[0];
	Vector3 v1 = triangle.vertices[1];
	Vector3 v2 = triangle.vertices[2];

	Vector3 p0 = segment.origin;
	Vector3 p1 = Add(segment.origin, segment.diff);

	// 線分と平面の衝突判定  
	Plane plane;
	plane.normal = Normalize(Cross(Subtract(v1, v0), Subtract(v2, v0)));
	plane.distance = Dot(plane.normal, v0);

	float dot = Dot(plane.normal, segment.diff);
	float distanceOriginToPlane = Dot(segment.origin, plane.normal) - plane.distance;
	float t = -distanceOriginToPlane / dot;
	Vector3 collisionPoint = Add(segment.origin, Multiply(segment.diff, t));

	Vector3 v01 = Subtract(v1, v0);
	Vector3 v12 = Subtract(v2, v1);
	Vector3 v20 = Subtract(v0, v2);

	Vector3 v0p = Subtract(collisionPoint, v0);
	Vector3 v1p = Subtract(collisionPoint, v1);
	Vector3 v2p = Subtract(collisionPoint, v2);

	Vector3 cross01 = Cross(v01, v0p);
	Vector3 cross12 = Cross(v12, v1p);
	Vector3 cross20 = Cross(v20, v2p);

	if (Dot(cross01, cross12) >= 0.0f &&Dot(cross12, cross20) >= 0.0f){
		return true;
	}
	return false;

}

Calculation::Vector3 Calculation::Perpendicular(const Vector3& vector) {
	if (std::abs(vector.x) > 1e-6f || std::abs(vector.y) > 1e-6f) { // Z軸と揃っていない場合
		return { -vector.y, vector.x, 0.0f };
	}
	return{ 0.0f,-vector.z,vector.y };
}

void Calculation::DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color){
	Calculation::Vector3 center = Multiply(plane.normal, plane.distance);

	Calculation::Vector3 perpendiculars[4];

	// まず、法線に直交する一つのベクトルを生成し、正規化します。
	// Perpendicular関数が正しく直交ベクトルを返すことが前提です。
	perpendiculars[0] = Normalize(Perpendicular(plane.normal));

	// そのベクトルと法線の外積を取り、2つ目の直交するベクトルを生成します。
	// これが平面を構成する基底ベクトルになります。
	perpendiculars[2] = Normalize(Cross(plane.normal, perpendiculars[0]));

	// これらのベクトルの逆方向も用意します（ただし、直接点計算に使うのは[0]と[2]の組み合わせのみ）
	perpendiculars[1] = Multiply(perpendiculars[0], -1.0f); // -perpendiculars[0]
	perpendiculars[3] = Multiply(perpendiculars[2], -1.0f); // -perpendiculars[2]

	// 平面の描画サイズを定義します。これは平面の視覚的な大きさを決めます。
	const float planeHalfSize = 5.0f; // 例えば、一辺が10の正方形として描画する場合

	Vector3 points[4];

	// 平面の四隅の点を計算します。
	// centerから、perpendiculars[0]とperpendiculars[2]を±planeHalfSize分だけ伸ばして加算します。
	points[0] = Add(center, Add(Multiply(perpendiculars[0], -planeHalfSize), Multiply(perpendiculars[2], -planeHalfSize))); // 左下
	points[1] = Add(center, Add(Multiply(perpendiculars[0], planeHalfSize), Multiply(perpendiculars[2], -planeHalfSize))); // 右下
	points[2] = Add(center, Add(Multiply(perpendiculars[0], planeHalfSize), Multiply(perpendiculars[2], planeHalfSize))); // 右上
	points[3] = Add(center, Add(Multiply(perpendiculars[0], -planeHalfSize), Multiply(perpendiculars[2], planeHalfSize))); // 左上

	// ビュープロジェクション行列とビューポート行列で変換します。
	Vector3 transformedPoints[4];
	for (int32_t index = 0; index < 4; ++index) {
		transformedPoints[index] = Transform(Transform(points[index], viewProjectionMatrix), viewportMatrix);
	}

	// Noviceで線を描画します。点のインデックスを修正し、四角形を形成するようにします。
	Novice::DrawLine((int)transformedPoints[0].x, (int)transformedPoints[0].y, (int)transformedPoints[1].x, (int)transformedPoints[1].y, color);
	Novice::DrawLine((int)transformedPoints[1].x, (int)transformedPoints[1].y, (int)transformedPoints[2].x, (int)transformedPoints[2].y, color);
	Novice::DrawLine((int)transformedPoints[2].x, (int)transformedPoints[2].y, (int)transformedPoints[3].x, (int)transformedPoints[3].y, color);
	Novice::DrawLine((int)transformedPoints[3].x, (int)transformedPoints[3].y, (int)transformedPoints[0].x, (int)transformedPoints[0].y, color);
}

Calculation::PlaneSegmentCollisionInfo Calculation::GetPlaneSegmentCollision(const Segment& segment, const Plane& plane) {
	PlaneSegmentCollisionInfo info;
	info.hit = false;
	info.t = -1.0f;
	info.hitPoint = { 0.0f, 0.0f, 0.0f };

	Vector3 A = segment.origin;
	Vector3 v = segment.diff; // これは (B - A) です

	// 平面の法線 N と距離 D (N.P + D = 0 を仮定)
	Vector3 N = plane.normal;
	float D = plane.distance;

	// 法線と線分方向の内積 N_dot_v を計算
	float N_dot_v = Dot(N, v);

	if (std::abs(N_dot_v) < 1e-6f) {
		float N_dot_A_plus_D = Dot(N, A) + D;
		if (std::abs(N_dot_A_plus_D) < 1e-6f) {
			info.hit = true; info.hitPoint = segment.origin;
			info.t = 0.0f;
		}
		return info; 
	}
	float t = -(Dot(N, A) + D) / N_dot_v;

	if (t >= 0.0f && t <= 1.0f) {
		info.hit = true;
		info.t = t;
		info.hitPoint = Add(A, Multiply(v, t)); // P = A + t*v
	}

	return info;
}

void Calculation::DrawTriangle(const Triangle& triangle, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color){
	Vector3 screenVertices[3];

	for (int i = 0; i < 3; ++i){
		Vector3 projected = Transform(triangle.vertices[i], viewProjectionMatrix);

		screenVertices[i] = Transform(projected, viewportMatrix);
	}

	// 三辺を描画
	Novice::DrawLine(static_cast<int>(screenVertices[0].x), static_cast<int>(screenVertices[0].y),static_cast<int>(screenVertices[1].x), static_cast<int>(screenVertices[1].y),color);
	
	Novice::DrawLine(static_cast<int>(screenVertices[1].x), static_cast<int>(screenVertices[1].y),static_cast<int>(screenVertices[2].x), static_cast<int>(screenVertices[2].y),color);
	
	Novice::DrawLine(static_cast<int>(screenVertices[2].x), static_cast<int>(screenVertices[2].y),static_cast<int>(screenVertices[0].x), static_cast<int>(screenVertices[0].y),color);
}

