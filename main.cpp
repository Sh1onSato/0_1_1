#include"Calculation.h"
#include <Novice.h>
#include<imgui.h>

const char kWindowTitle[] = "LE2C_12_サトウ_シオン";


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Calculation* calculation = new Calculation();

	Calculation::Sphere sphere{ {0.0f, -2.0f, 1.6f}, 1.0f };

	Calculation::Vector3 cameraRotate{ -0.26f,0.0f,0.0f };

	Calculation::Vector3 cameraTranslate{ 0.0f,1.9f,-6.49f };

	Calculation::Vector3 cameraPosition{ 0.0f, 0.0f, 8.0f };

	uint32_t color = 0xFFFFFFFF;

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
		/*if (keys[DIK_W])
		{
			translate.z += 0.1f;
		}
		else if (keys[DIK_S])
		{
			translate.z -= 0.1f;
		}
		else if (keys[DIK_A])
		{
			translate.x -= 0.1f;
		}
		else if (keys[DIK_D])
		{
			translate.x += 0.1f;
		}

		rotate.y -= 0.03f;*/

		Calculation::Matrix4x4 worldMatrix = calculation->MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, cameraRotate, cameraTranslate);
		Calculation::Matrix4x4 cameraMatrix = calculation->MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, cameraPosition);
		Calculation::Matrix4x4 viewMatrix = calculation->Inverse(cameraMatrix);
		Calculation::Matrix4x4 projectionMatrix = calculation->MakePerspectiveFovMatrix(0.45f, calculation->kColumnWidth/calculation->kRowHeight, 0.1f, 100.0f);
		Calculation::Matrix4x4 worldViewProjectionMatrix = calculation->Multiply(worldMatrix, calculation->Multiply(viewMatrix,projectionMatrix));
		Calculation::Matrix4x4 viewportMatrix = calculation->MakeViewportMatrix(0.0f, 0.0f, calculation->kColumnWidth, calculation->kRowHeight, 0.0f, 1.0f);

		ImGui::Begin("window");
		ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("cameraRotate", &cameraRotate.x, 0.01f);
		ImGui::DragFloat3("cameraCenter", &sphere.center.x, 0.01f);
		ImGui::DragFloat("cameraRadius", &sphere.radius, 0.01f);
		ImGui::End();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		
		calculation->DrawGrid(worldViewProjectionMatrix, viewportMatrix);

		calculation->DrawSphere(sphere, worldViewProjectionMatrix, viewportMatrix, color);
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