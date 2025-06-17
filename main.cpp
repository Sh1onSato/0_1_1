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

	Calculation::Sphere sphere{ {0.0f, 0.0f, 0.5f}, 1.0f };
	/*calculation->m1 =
	{ 3.2f, 0.7f, 9.6f, 4.4f,
	  5.5f, 1.3f, 7.8f, 2.1f,
	  6.9f, 8.0f, 2.6f, 1.0f,
	  0.5f, 7.2f, 5.1f,3.3f
	};*/

	/*calculation->m2 =
	{ 4.1f, 6.5f, 3.3f, 2.2f,
	  8.8f, 0.6f, 9.9f, 7.7f,
	  1.1f, 5.5f, 6.6f, 0.0f,
	  3.3f, 9.9f, 8.8f, 2.2f
	};*/

	/*calculation->scale = { 1.2f, 0.79f, -2.1f };
	calculation->rotate = { 0.4f, 1.43f, -0.8f };
	calculation->translate = { 2.7f, -4.15f, 1.57f };*/

	/*calculation->point = { 2.3f, 3.8f, 1.4f };*/

	/*calculation->transformationMatrix =
	{
		1.0f,2.0f,3.0f,4.0f,
		3.0f,1.0f,1.0f,2.0f,
		1.0f,4.0f,2.0f,3.0f,
		2.0f,2.0f,1.0f,3.0f
	};*/
	/*Calculation::Matrix4x4 orthograhicMatrix = calculation->MakeOrthographicMatrix(-160.0f, 160.0f, 200.0f, 300.0f, 0.0f, 1000.0f);
	Calculation::Matrix4x4 perspectiveMatrix = calculation->MakePerspectiveFovMatrix(0.63f, 1.33f, 0.1f, 1000.0f);
	Calculation::Matrix4x4 viewportMatrix = calculation->MakeViewportMatrix(100.0f, 200.0f, 600.0, 300.0f,0.0f, 1.0f);*/

	/*Calculation::Vector3 v1 = { 1.2f,-3.9f,2.0f };
	Calculation::Vector3 v2 = { 2.8f,0.4f,-1.3f };
	Calculation::Vector3 cross = calculation->Cross(v1, v2);

	Calculation::Vector3 rotate{};
	Calculation::Vector3 translate{};
	Calculation::Vector3 cameraPosition{ 0.0f, 0.0f, -10.0f };

	Calculation::Vector3 kLocalVertices[3] = {
		{ 0.0f, 1.0f, 0.0f },
		{ -1.0f, -1.0f, 0.0f },
		{ 1.0f, -1.0f, 0.0f }
	};*/

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
	/*	Calculation::Matrix4x4 rotateXMatrix = calculation->MakeRotationXMatrix(calculation->rotate.x);
		Calculation::Matrix4x4 rotateYMatrix = calculation->MakeRotationYMatrix(calculation->rotate.y);
		Calculation::Matrix4x4 rotateZMatrix = calculation->MakeRotationZMatrix(calculation->rotate.z);
		Calculation::Matrix4x4 rotateXYZMatrix = calculation->Multiply(rotateXMatrix, calculation->Multiply(rotateYMatrix, rotateZMatrix));*/
		
		/*Calculation::Matrix4x4 worldMatrix = calculation->MakeAffineMatrix(calculation->scale, calculation->rotate, calculation->translate);*/

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
	/*	Calculation::Vector3 screenVertics[3];*/
		//for (uint32_t i = 0; i < 3; ++i) {
		//	Calculation::Vector3 ndcVertex = calculation->Transform(kLocalVertices[i], worldViewProjectionMatrix);
		//	screenVertics[i] = calculation->Transform(ndcVertex, viewportMatrix);
		//}


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
		
		/*calculation->MatrixScreenPrintf(0, 0, rotateXMatrix, "rotateXMatrix");
		calculation->MatrixScreenPrintf(0, calculation->kRowHeight * 5, rotateYMatrix, "rotateYMatrix");
		calculation->MatrixScreenPrintf(0, calculation->kRowHeight * 10, rotateZMatrix, "rotateZMatrix");
		calculation->MatrixScreenPrintf(0, calculation->kRowHeight * 15, rotateXYZMatrix, "rotateXYZMatrix");*/
		///
		/*calculation->MatrixScreenPrintf(0, 0, worldMatrix, "worldMatrix");*/

		/*calculation->MatrixScreenPrintf(0, 0, orthograhicMatrix, "orthograhicMatrix");
		calculation->MatrixScreenPrintf(0, calculation->kRowHeight * 5, perspectiveMatrix, "perspectiveMatrix");
		calculation->MatrixScreenPrintf(0, calculation->kRowHeight * 10, viewportMatrix, "viewportMatrix");*/
		
		/*calculation->VectorScreenPrintf(0, 0, cross, "cross");
		Novice::DrawTriangle(int(screenVertics[0].x), int(screenVertics[0].y),
			int(screenVertics[1].x), int(screenVertics[1].y),
			int(screenVertics[2].x), int(screenVertics[2].y),
			RED, kFillModeSolid);*/

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