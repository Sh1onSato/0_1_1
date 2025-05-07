#include"Calculation.h"
#include <Novice.h>

const char kWindowTitle[] = "LE2C_08_サトウ_シオン";


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Calculation* calculation = new Calculation();

	calculation->m1 =
	{ 3.2f, 0.7f, 9.6f, 4.4f,
	  5.5f, 1.3f, 7.8f, 2.1f,
	  6.9f, 8.0f, 2.6f, 1.0f,
	  0.5f, 7.2f, 5.1f,3.3f
	};

	calculation->m2 =
	{ 4.1f, 6.5f, 3.3f, 2.2f,
	  8.8f, 0.6f, 9.9f, 7.7f,
	  1.1f, 5.5f, 6.6f, 0.0f,
	  3.3f, 9.9f, 8.8f, 2.2f
	};

	calculation->translate = { 4.1f, 2.6f, 0.8f };
	calculation->scale = { 1.5f, 5.2f, 7.3f };
	calculation->rotate = { 0.4f, 1.43f, -0.8f };

	calculation->point = { 2.3f, 3.8f, 1.4f };

	calculation->transformationMatrix =
	{
		1.0f,2.0f,3.0f,4.0f,
		3.0f,1.0f,1.0f,2.0f,
		1.0f,4.0f,2.0f,3.0f,
		2.0f,2.0f,1.0f,3.0f
	};
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
		Calculation::Matrix4x4 rotateXMatrix = calculation->MakeRotationXMatrix(calculation->rotate.x);
		Calculation::Matrix4x4 rotateYMatrix = calculation->MakeRotationYMatrix(calculation->rotate.y);
		Calculation::Matrix4x4 rotateZMatrix = calculation->MakeRotationZMatrix(calculation->rotate.z);
		Calculation::Matrix4x4 rotateXYZMatrix = calculation->Multiply(rotateXMatrix, calculation->Multiply(rotateYMatrix, rotateZMatrix));
		
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		
		calculation->MatrixScreenPrintf(0, 0, rotateXMatrix, "rotateXMatrix");
		calculation->MatrixScreenPrintf(0, calculation->kRowHeight * 5, rotateYMatrix, "rotateYMatrix");
		calculation->MatrixScreenPrintf(0, calculation->kRowHeight * 10, rotateZMatrix, "rotateZMatrix");
		calculation->MatrixScreenPrintf(0, calculation->kRowHeight * 15, rotateXYZMatrix, "rotateXYZMatrix");
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