#pragma once
#include <Novice.h>
#include <cmath>
#include <assert.h>

class Calculation{
public:

	struct Vector3{
		float x, y, z;
		Vector3 operator+(const Vector3& other) const {
			return Vector3(x + other.x, y + other.y, z + other.z);
		}
		Vector3 operator-(const Vector3& other) const {
			return Vector3(x - other.x, y - other.y, z - other.z);
		}
		Vector3 operator*(float scalar) const {
			return Vector3(x * scalar, y * scalar, z * scalar);
		}
		float operator*(const Vector3& other) const {
			return x * other.x + y * other.y + z * other.z;
		}
		Vector3 operator/(float scalar) const {
			return Vector3(x / scalar, y / scalar, z / scalar);
		}
	};

	struct Matrix4x4 {
		float m[4][4];
		Matrix4x4 operator+(const Matrix4x4& other) const {
			Matrix4x4 result;
			for (int i = 0; i < 4; ++i) {
				for (int j = 0; j < 4; ++j) {
					result.m[i][j] = m[i][j] + other.m[i][j];
				}
			}
			return result;
		}

		Matrix4x4 operator-(const Matrix4x4& other) const {
			Matrix4x4 result;
			for (int i = 0; i < 4; ++i) {
				for (int j = 0; j < 4; ++j) {
					result.m[i][j] = m[i][j] - other.m[i][j];
				}
			}
			return result;
		}

		Matrix4x4 operator*(const Matrix4x4& other) const {
			Matrix4x4 result;
			for (int i = 0; i < 4; ++i) {
				for (int j = 0; j < 4; ++j) {
					result.m[i][j] = 0.0f;
					for (int k = 0; k < 4; ++k) {
						result.m[i][j] += m[i][k] * other.m[k][j];
					}
				}
			}
			return result;
		}
	};

	struct Sphere {
		Vector3 center;
		float radius;
		int	color;
	};

	struct Segment{
		Vector3 origin;
		Vector3 diff;
		uint32_t color;
	};

	struct Plane {
		Vector3 normal;
		float distance;
		uint32_t color;
	};
	struct PlaneSegmentCollisionInfo {
		bool hit;          
		Vector3 hitPoint;   
		float t;
	};

	struct Triangle {
		Calculation::Vector3 vertices[3];
		uint32_t color;
	};

	struct AABB{
		Vector3 min;
		Vector3 max;
		uint32_t color;
	};



	Vector3 translate = {};
	Vector3 scale = {};
	Vector3 rotate = {};

	Matrix4x4 m1 = {};
	Matrix4x4 m2 = {};
	Matrix4x4 transformationMatrix = {};

	static const int kColumnWidth = 60;
	static const int kRowHeight = 20;
	// 加算
	Vector3 Add(const Vector3& a, const Vector3& b);
	// 減算
	Vector3 Subtract(const Vector3& a, const Vector3& b);
	// スカラー倍
	Vector3 Multiply(const Vector3& a, float b);
	// 内積
	float Dot(const Vector3& a, const Vector3& b);
	// 長さ(ノルム)
	float Length(const Vector3& a);
	// 正規化
	Vector3 Normalize(const Vector3& a);

	
	void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label);


	//１.行列の加法
	Matrix4x4 Add(const Matrix4x4& a, const Matrix4x4& b);
	//２.行列の減法
	Matrix4x4 Subtract(const Matrix4x4& a, const Matrix4x4& b);
	//３.行列の積
	Matrix4x4 Multiply(const Matrix4x4& a, const Matrix4x4& b);
	//４.逆行列
	Matrix4x4 Inverse(const Matrix4x4& a);
	//５.転倒行列
	Matrix4x4 Transpose(const Matrix4x4& a);
	//６.単項行列の作成
	Matrix4x4 MakeIdentity4x4();

	Matrix4x4 MakeScaleMatrix(const Vector3& scale);

	//平行移動行列
	Matrix4x4 MakeTranslationMatrix(const Vector3& translate);

	//座標変換行列
	Vector3 Transform(const Vector3& vector,const Matrix4x4& matrix);

	//1.X軸回転行列
	Matrix4x4 MakeRotationXMatrix(float radian);
	//2.Y軸回転行列
	Matrix4x4 MakeRotationYMatrix(float radian);
	//3.Z軸回転行列
	Matrix4x4 MakeRotationZMatrix(float radian);

	// 3次元アフィン変換行列
	Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

	//1. 遠視投影行列
	Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farCrip);
	//2. 正射影行列
	Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);
	//3. ビューポート変換行列
	Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height,float minDepth,float maxDepth);

	void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label);

	// クロス積
	Vector3 Cross(const Vector3& a, const Vector3& b);


	void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);
	
	void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);

	Vector3 Project(const Vector3& v1, const Vector3& v2);
	
	Vector3 Closestpoint(const Vector3& point, const Segment& segment);

	bool IsCollision(const AABB& aabb, const Segment& segment);

	Vector3 Perpendicular(const Vector3& vector);

	void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

	PlaneSegmentCollisionInfo GetPlaneSegmentCollision(const Segment& segment, const Plane& plane);

	void DrawTriangle(const Triangle& triangle, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

	void DrawAABB(const AABB& aabb, Matrix4x4& viewProjectionMatrix, Matrix4x4& viewportMatrix, uint32_t color);

	Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t);

	void DrawBezier(const Vector3& controlPoint0, const Vector3& controlPoint1, const Vector3& controlPoint2, Matrix4x4& viewProjectionMatrix, Matrix4x4& viewportMatrix, uint32_t color);

};


