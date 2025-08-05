#include"Calculation.h"
#include <Novice.h>
#include <cmath>
#include <numbers>
#include <algorithm>
#include<imgui.h>
#include <iostream>
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/glm.hpp"
#include "glm/gtx/norm.hpp"


const char kWindowTitle[] = "LE2C_12_サトウ_シオン";


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Calculation* calculation = new Calculation();

	Calculation::Segment segment{
		{-0.7f,0.3f, 0.0f},
		{ 2.0f, -0.5f, 0.0f},
		0xFFFFFFFF,
	};

	struct Transform {
		Calculation::Vector3 scale;
		Calculation::Vector3 rotate;
		Calculation::Vector3 translate;
	};

	Calculation::Plane plane{
		{0.0f,1.0f,0.0f},
		1.0f,
		0xFFFFFFFF,
	};

	Calculation::Vector3 controlPoints[3] = {
		{-1.0f, 0.58f, 1.0f,},
		{1.76f, 1.0f, -0.3f,},
		{0.94f, -0.7f, 2.3f,},
	};

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

	//Calculation::Vector3 point{ -1.5f,0.6f,0.6f };

	//Calculation::Vector3 cameraRotate{ 0.26f,0.0f,0.0f };

	/*Calculation::Vector3 cameraTranslate{ 0.0f,1.9f,-6.49f };*/

	/*Calculation::Vector3 cameraPosition{ 0.0f, 1.9f, -6.25f };*/

	/*uint32_t color = 0xFFFFFFFF;*/

	/*Calculation::Sphere sphere= {0.0f,0.0f ,- 1.0f,1.0f};*/

	Calculation::Sphere sphere[2];
	sphere[0].center = { 1.0f,1.0f ,1.0f };
	sphere[0].radius = { 1.0f };
	sphere[0].color = 0xFFFFFFFF;
	sphere[1].center = { 1.7f,0.0f ,1.0f };
	sphere[1].radius = { 0.4f };
	sphere[1].color = 0xFFFFFFFF;

	Calculation::Triangle  triangle{
		{
			{ -1.0f,  0.0f, 0.0f },	
			{  0.0f,  1.0f, 0.0f },  
			{  1.0f,  0.0f, 0.0f }  
		},

		0xFFFFFFFF
	};


	Transform  transform{
	{1.0f,1.0f,1.0f},
	{0.0f,0.0f,0.0f},
	{0.0f,0.0f,0.0f},
	};


	Transform  cameraPosition{
	{1.0f,1.0f,1.0f},
	{ 0.26f,0.0f,0.0f },
	{ 0.0f,1.9f,-6.25f },
	};

	Calculation::AABB aabb1{
		.min{-0.5f,-0.5f,-0.5f},
		.max{ 0.5f, 0.5f, 0.5f},
	};

	aabb1.color = 0xFFFFFFFF;

	//Calculation::AABB aabb2{
	//	.min{ 0.2f, 0.2f, 0.2f},
	//	.max{ 1.0f, 1.0f, 1.0f},
	//};

	//aabb2.color = 0xFFFFFFFF;

	/*Calculation::Vector3 translates[3] = {
		{0.2f,1.0f,0.0f},
		{0.4f,0.0f,0.0f},
		{0.3f,0.0f,0.0f},
	};

	Calculation::Vector3 rotates[3] = {
		{0.0f,0.0f,-0.8f},
		{0.0f,0.0f,-1.4f},
		{0.0f,0.0f,0.0f},
	};

	Calculation::Vector3 scales[3] = {
		{1.0f,1.0f,1.0f},
		{1.0f,1.0f,1.0f},
		{1.0f,1.0f,1.0f},
	};

	uint32_t jointColors[3] = {
	0xFF0000FF,
	0x00FF00FF,
	0x0000FFFF 
	};

	Calculation::Vector3 jointPositions[3];

	Calculation::Vector3 screenA;
	Calculation::Vector3 screenB;*/

	Calculation::Vector3 a{ 0.2f,1.0f,0.0f };
	Calculation::Vector3 b{ 2.4f,3.1f,1.2f };
	Calculation::Vector3 c = a + b;
	Calculation::Vector3 d = a - b;
	Calculation::Vector3 e = a * 2.4f;
	Calculation::Vector3 rotate{ 0.4f,1.43f,-0.8f };
	Calculation::Matrix4x4 rotateXMatrix = calculation->MakeRotationXMatrix(rotate.x);
	Calculation::Matrix4x4 rotateYMatrix = calculation->MakeRotationYMatrix(rotate.y);
	Calculation::Matrix4x4 rotateZMatrix = calculation->MakeRotationZMatrix(rotate.z);
	Calculation::Matrix4x4 rotateMatrix = rotateXMatrix * rotateYMatrix * rotateZMatrix;

	int mouseX = 0;
	int mouseY = 0;
	int preMouseX = 0;
	int preMouseY = 0;;
	int mouseWheel = 0;
	bool isRightMouseDown = false;


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

		if (keys[DIK_W])
		{
			cameraPosition.translate.y += 0.01f;
		}

		if (keys[DIK_S])
		{
			cameraPosition.translate.y -= 0.01f;
		}

		if (keys[DIK_D])
		{
			cameraPosition.translate.x += 0.01f;
		}

		if (keys[DIK_A])
		{
			cameraPosition.translate.x -= 0.01f;
		}



		/*rotate.y -= 0.03f;*/
		preMouseX = mouseX;
		preMouseY = mouseY;
		mouseWheel = Novice::GetWheel();
		Novice::GetMousePosition(&mouseX, &mouseY);
		isRightMouseDown = Novice::IsPressMouse(1);

		//const float kRotateSensitivity = 0.001f;

		/*if (isRightMouseDown)
		{
			float dx = float(mouseX - preMouseX);
			float dy = float(mouseY - preMouseY);

			cameraPosition.rotate.y += dx * kRotateSensitivity;
	
			cameraPosition.rotate.x += dy * kRotateSensitivity;

			float limit = std::numbers::pi_v<float> / 2.0f;
			cameraPosition.rotate.x = std::clamp(cameraPosition.rotate.x, -limit, limit);
		}

		cameraPosition.translate.z += float(mouseWheel) * kRotateSensitivity;

		Calculation::Vector3 diff_calc_vec = sphere[1].center - sphere[0].center;*/


		/*Calculation::Matrix4x4 jointWorldMatrix[3];

		jointWorldMatrix[0] = calculation->MakeAffineMatrix(scales[0], rotates[0], translates[0]);

		Calculation::Matrix4x4 elbowLocal = calculation->MakeAffineMatrix(scales[1], rotates[1], translates[1]);

		jointWorldMatrix[1] = calculation->Multiply(elbowLocal, jointWorldMatrix[0]);

		Calculation::Matrix4x4 handLocal = calculation->MakeAffineMatrix(scales[2], rotates[2], translates[2]);


		jointWorldMatrix[2] = calculation->Multiply(handLocal, jointWorldMatrix[1]);
*/

		/*float distance = glm::length(glm::vec3(diff_calc_vec.x, diff_calc_vec.y, diff_calc_vec.z));*/

		//if(distance < sphere[0].radius + sphere[1].radius) {
		//	// 衝突している場合の処理
		//	sphere[0].color = 0xFFFF00FF; // 赤色に変更
		//}
		//else {
		//	// 衝突していない場合の処理
		//	sphere[0].color = 0xFFFFFFFF; // 元の色に戻す
		//}
		//Calculation::PlaneSegmentCollisionInfo collisionResult = calculation->GetPlaneSegmentCollision(segment, plane);

		//if (collisionResult.hit) {
		//	// 衝突検出！ 線分の色を変更してヒットを示す
		//	segment.color = 0xFF0000FF; // 衝突時は赤色
		//}
		//else {
		//	// 衝突なし、デフォルトの色に戻す
		//	segment.color = 0xFFFFFFFF; // 白
		//}
		/*if (calculation->IsCollision(aabb1, segment)){
			aabb1.color = 0xFF0000FF;
		}
		else{
			aabb1.color = 0xFFFFFFFF;
		}*/
		//Calculation::Matrix4x4 worldMatrix = calculation->MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, cameraRotate, cameraTranslate);
		//Calculation::Matrix4x4 cameraMatrix = calculation->MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, cameraPosition);
		//Calculation::Matrix4x4 viewMatrix = calculation->Inverse(cameraMatrix);
		//Calculation::Matrix4x4 projectionMatrix = calculation->MakePerspectiveFovMatrix(0.45f, 1280.0f/720.0f, 0.1f, 100.0f);
		//Calculation::Matrix4x4 worldViewProjectionMatrix = calculation->Multiply(worldMatrix, calculation->Multiply(viewMatrix,projectionMatrix));
		//Calculation::Matrix4x4 viewportMatrix = calculation->MakeViewportMatrix(0.0f, 0.0f, 1280.0f, 720.0f, 0.0f, 1.0f);
	/*	Calculation::Vector3 screenVertics[3];*/
		//for (uint32_t i = 0; i < 3; ++i) {
		//	Calculation::Vector3 ndcVertex = calculation->Transform(kLocalVertices[i], worldViewProjectionMatrix);
		//	screenVertics[i] = calculation->Transform(ndcVertex, viewportMatrix);
		//}
		/*Calculation::Vector3 project = calculation->Project(calculation->Subtract(point, segment.origin), segment.diff);*/

		//Calculation::Vector3 closesPoint = calculation->Closestpoint(point, segment);

		Calculation::Matrix4x4 worldMateix = calculation->MakeAffineMatrix(transform.scale, transform.rotate, transform.translate);
		Calculation::Matrix4x4 cameraMatrix = calculation->MakeAffineMatrix(cameraPosition.scale, cameraPosition.rotate, cameraPosition.translate);
		Calculation::Matrix4x4 viewMatrix = calculation->Inverse(cameraMatrix);
		Calculation::Matrix4x4 projectionMatrix = calculation->MakePerspectiveFovMatrix(0.45f, 1280.0f /720.0f, 0.1f, 100.0f);
		//WVPMatrixの作成
		Calculation::Matrix4x4 ViewProjectionMatrix = calculation->Multiply(viewMatrix, projectionMatrix);
		//viewPortMatrixの作成
		Calculation::Matrix4x4 viewportMatrix = calculation->MakeViewportMatrix(0, 0, 1280.0f , 720.0f, 0.0f, 1.0f);

		ImGui::Begin("window");
		ImGui::Text("c:%f,%f,%f", c.x, c.y, c.z);
		ImGui::Text("c:%f,%f,%f", d.x, d.y, d.z);
		ImGui::Text("c:%f,%f,%f", e.x, e.y, e.z);
		ImGui::Text(
			"matrix:\n%f, %f, %f,%f\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n",
			rotateMatrix.m[0][0], rotateMatrix.m[0][1], rotateMatrix.m[0][2],
			rotateMatrix.m[0][3], rotateMatrix.m[1][0], rotateMatrix.m[1][1],
			rotateMatrix.m[1][2], rotateMatrix.m[1][3], rotateMatrix.m[2][0],
			rotateMatrix.m[2][1], rotateMatrix.m[2][2], rotateMatrix.m[2][3],
			rotateMatrix.m[3][0], rotateMatrix.m[3][1], rotateMatrix.m[3][2],
			rotateMatrix.m[3][3]);
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

		/*calculation->DrawGrid(worldViewProjectionMatrix, viewportMatrix);

		calculation->DrawSphere(sphere, worldViewProjectionMatrix, viewportMatrix, color);*/
		


		/*calculation->DrawSphere(sphere[0], ViewProjectionMatrix, viewportMatrix, sphere[0].color);*/
	/*	calculation->DrawPlane(plane, ViewProjectionMatrix, viewportMatrix, plane.color);*/


		/*calculation->DrawGrid(ViewProjectionMatrix, viewportMatrix);*/

		/*calculation->DrawSphere(sphere[0], ViewProjectionMatrix, viewportMatrix, sphere[0].color);*/


		/*Calculation::Vector3 start = calculation->Transform(calculation->Transform(segment.origin, ViewProjectionMatrix), viewportMatrix);

		Calculation::Vector3 end =calculation->Transform(calculation->Transform(calculation->Add(segment.origin, segment.diff), ViewProjectionMatrix), viewportMatrix);*/

		//Novice::DrawLine(int(start.x), int(start.y), int(end.x), int(end.y), segment.color);

		/*calculation->DrawTriangle(triangle, ViewProjectionMatrix, viewportMatrix, triangle.color);*/

		/*calculation->DrawAABB(aabb1, ViewProjectionMatrix, viewportMatrix, aabb1.color);
		*///calculation->DrawAABB(aabb2, ViewProjectionMatrix, viewportMatrix, aabb2.color);

		/*Novice::DrawLine(int(start.x), int(start.y), int(end.x), int(end.y), segment.color);*/

	/*	calculation->DrawBezier(controlPoints[0], controlPoints[1], controlPoints[2], ViewProjectionMatrix, viewportMatrix, 0x003CB3FF);*/

		//for (int i = 0; i < 2; ++i)
		//{
		//	Calculation::Vector3 a = jointPositions[i];       // 現在の関節
		//	Calculation::Vector3 b = jointPositions[i + 1];   // 次の関節

		//	screenA = calculation->Transform(calculation->Transform(a, ViewProjectionMatrix), viewportMatrix);

		//	screenB = calculation->Transform(calculation->Transform(b, ViewProjectionMatrix), viewportMatrix);

		//	Novice::DrawLine(int(screenA.x), int(screenA.y), int(screenB.x), int(screenB.y), 0xFFFFFFFF);
		//}


		//for (int i = 0; i < 3; ++i)
		//{
		//	jointPositions[i] = { jointWorldMatrix[i].m[3][0], jointWorldMatrix[i].m[3][1], jointWorldMatrix[i].m[3][2] };

		//	Calculation::Sphere s;
		//	s.center = jointPositions[i];
		//	s.radius = 0.1f;
		//	s.color = jointColors[i];

		//	calculation->DrawSphere(s, ViewProjectionMatrix, viewportMatrix, s.color);
		//}

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