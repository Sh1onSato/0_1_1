#include <Novice.h>
#include<cmath>

const char kWindowTitle[] = "LE2C_08_サトウ_シオン";

struct Vector3 {
	float x, y, z;
};

struct Matrix4x4 {
	float m[4][4];
};
//// 加算
//Vector3 Add(const Vector3& a, const Vector3& b) {
//	return { a.x + b.x, a.y + b.y, a.z + b.z };
//}
//// 減算
//Vector3 Subtract(const Vector3& a, const Vector3& b) {
//	return { a.x - b.x, a.y - b.y, a.z - b.z };
//}
//// スカラー倍
//Vector3 Multiply(float b, const Vector3& a) {
//	return { a.x * b, a.y * b, a.z * b };
//}
//// 内積
//float Dot(const Vector3& a, const Vector3& b) {
//	return a.x * b.x + a.y * b.y + a.z * b.z;
//}
//// 長さ(ノルム)
//float Length(const Vector3& a) {
//	return std::sqrt(Dot(a, a));
//}
//// 正規化
//Vector3 Normalize(const Vector3& a) {
//	float length = Length(a);
//	if (length == 0) {
//		return { 0, 0, 0 };
//	}
//	return { a.x / length, a.y / length, a.z / length };
//}

//static const int kColumnWidth = 60;
//void VectorScreenPrintf(int x,int y,const Vector3&vector,const char* label){
//	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
//	Novice::ScreenPrintf(x + kColumnWidth, y, "x:%.02f", vector.y);
//	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z);
//	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
//};
//

//１.行列の加法
Matrix4x4 Add(const Matrix4x4& a, const Matrix4x4& b) {
	Matrix4x4 result;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.m[i][j] = a.m[i][j] + b.m[i][j];
		}
	}
	return result;
}
//２.行列の減法
Matrix4x4 Subtract(const Matrix4x4& a, const Matrix4x4& b) {
	Matrix4x4 result;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.m[i][j] = a.m[i][j] - b.m[i][j];
		}
	}
	return result;
}
//３.行列の積
Matrix4x4 Multiply(const Matrix4x4& a, const Matrix4x4& b) {
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
//４.逆行列
Matrix4x4 Inverse(const Matrix4x4& a) {
	Matrix4x4 result;
	// 逆行列の計算を実装する
	float det =a.m[0][3] * a.m[1][2] * a.m[2][1] * a.m[3][0] - a.m[0][2] * a.m[1][3] * a.m[2][1] * a.m[3][0] -
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

	if (det == 0.0f){
		return result;
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
//５.転倒行列
Matrix4x4 Transpose(const Matrix4x4& a) {
	Matrix4x4 result;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.m[i][j] = a.m[j][i];
		}
	}
	return result;
}
//６.単項行列の作成
Matrix4x4 MakeIdentity4x4() {
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


static const int kRowHeight = 20;
static const int kColumnWidth = 60;
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix,const char* label) {
	
	for (int row = 0; row < 4; ++row) {
		if (row == 0){
			Novice::ScreenPrintf(x + 15, y, "%s", label);
		}
		for (int column = 0; column < 4; ++column) {
			
			Novice::ScreenPrintf(x + column * kColumnWidth, y + 20 + row * kRowHeight,"%6.02F", matrix.m[row][column]);
		}

	}
};

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

//	Vector3 v1 = { 1.0f, 3.0f, -5.0f };
//	Vector3 v2 = { 4.0f, -1.0f, 2.0f };
//	float k = { 4.0f };
//
//	Vector3 resultAdd = Add(v1, v2);
//	Vector3 resultSubtract = Subtract(v1, v2);
//	Vector3 resultMultiply = Multiply(k,v1);
//	float resultDot = Dot(v1, v2);
//	float resultLength = Length(v1);
//	Vector3 resultNormalize = Normalize(v2);
//
//	int kRowHeight = 30;
	Matrix4x4 m1 = { 3.2f,0.7f,9.6f,4.4f,5.5f,1.3f,7.8f,2.1f,6.9f,8.0f,2.6f,1.0f,0.5f,7.2f,5.1f,3.3f };
	Matrix4x4 m2 = { 4.1f,6.5f,3.3f,2.2f,8.8f,0.6f,9.9f,7.7f,1.1f,5.5f,6.6f,0.0f,3.3f,9.9f,8.8f,2.2f };

	Matrix4x4 resultAdd = Add(m1, m2);
	Matrix4x4 resultMultiply = Multiply(m1, m2);
	Matrix4x4 resultSubtract = Subtract(m1, m2);
	Matrix4x4 inverseM1 = Inverse(m1);
	Matrix4x4 inverseM2 = Inverse(m2);
	Matrix4x4 transposeM1 = Transpose(m1);
	Matrix4x4 transposeM2 = Transpose(m2);
	Matrix4x4 identity = MakeIdentity4x4();
	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		/*VectorScreenPrintf(0, 0, resultAdd, " : Add");
		VectorScreenPrintf(0, kRowHeight, resultSubtract, " : Subtract");
		VectorScreenPrintf(0, kRowHeight * 2, resultMultiply, " : Multiply");
		Novice::ScreenPrintf(0, kRowHeight * 3,  "%.02f : Dot", resultDot);
		Novice::ScreenPrintf(0, kRowHeight * 4, "%.02f : Length", resultLength);
		VectorScreenPrintf(0, kRowHeight * 5, resultNormalize, " : Normalize");*/
		MatrixScreenPrintf(0, 0, resultAdd,"Add");
		MatrixScreenPrintf(0, kRowHeight * 5, resultSubtract, "Subtract");
		MatrixScreenPrintf(0, kRowHeight * 5 * 2, resultMultiply, "Multiply");
		MatrixScreenPrintf(0, kRowHeight * 5 * 3, inverseM1, "InverseM1");
		MatrixScreenPrintf(0, kRowHeight * 5 * 4, inverseM2, "InverseM2");
		MatrixScreenPrintf(kColumnWidth * 5, 0, transposeM1, "TransposeM1");
		MatrixScreenPrintf(kColumnWidth * 5, kRowHeight * 5, transposeM2, "TransposeM2");
		MatrixScreenPrintf(kColumnWidth * 5, kRowHeight * 5 * 2, identity, "identity");

		///
		
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}