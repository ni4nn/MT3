#include <Novice.h>
#include<string>
#include "Matrix4x4.h"
#include "MatrixMath.h"
#include"MyMath.h"
#include"Vector3.h"
#include <cassert>
#define _USE_MATH_DEFINES
#include<math.h>
#include<cmath>
#include <imgui.h>

const char kWindowTitle[] = "LC1A_16_スズキ_ミノリ_タイトル";


////座標変換
//Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix) {
//	Vector3 result{};
//	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
//	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
//	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];
//	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];
//	assert(w != 0.0f);
//	result.x /= w;
//	result.y /= w;
//	result.z /= w;
//	return result;
//
//}


struct Sphere {
	Vector3 center;
	float radius;
};



void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	
	//分割数
	const uint32_t kSubdivision = 12;
	//経度一分割の角度
	const float kLonEvery = (2 * (static_cast<float>(M_PI))) / kSubdivision;
	//緯度一分割の角度
	const float kLatEvery = (static_cast<float>(M_PI)) / kSubdivision;


	//緯度の方向に分割　-π/2 ~ π/2
	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {
		float lat = -(static_cast<float>(M_PI)) / 2.0f + kLatEvery * latIndex;//緯度

		//経度の方向に分割
		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
			float lon = lonIndex * kLonEvery;//経度

			//world座標系でのa,b,c
			Vector3 a = { (sphere.radius) * cosf(lat) * cosf(lon), (sphere.radius) * sinf(lat), (sphere.radius) * cosf(lat) * sin(lon) };
			Vector3 b = { (sphere.radius) * cosf(lat + kLatEvery) * cosf(lon), (sphere.radius) * sinf(lat + kLatEvery), (sphere.radius) * cos(lat + kLatEvery) * sinf(lon) };
			Vector3 c = { (sphere.radius) * cosf(lat) * cosf(lon + kLonEvery), (sphere.radius) * sinf(lat), (sphere.radius) * cosf(lat) * sinf(lon + kLonEvery) };

			Matrix4x4 worldMatrixA = MatrixMath::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, sphere.center);
			Matrix4x4 worldMatrixB = MatrixMath::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, sphere.center);
			Matrix4x4 worldMatrixC = MatrixMath::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, sphere.center);

			Matrix4x4 wvpMatrixA = MatrixMath::Multiply(worldMatrixA, viewProjectionMatrix);
			Matrix4x4 wvpMatrixB = MatrixMath::Multiply(worldMatrixB, viewProjectionMatrix);
			Matrix4x4 wvpMatrixC = MatrixMath::Multiply(worldMatrixC, viewProjectionMatrix);

			Vector3 localA = MyMath::Transform(a, wvpMatrixA);
			Vector3 localB = MyMath::Transform(b, wvpMatrixB);
			Vector3 localC = MyMath::Transform(c, wvpMatrixC);

			Vector3 screenA = MyMath::Transform(localA, viewportMatrix);
			Vector3 screenB = MyMath::Transform(localB, viewportMatrix);
			Vector3 screenC = MyMath::Transform(localC, viewportMatrix);

			

			Novice::DrawLine(static_cast<int>(screenA.x), static_cast<int>(screenA.y), static_cast<int>(screenB.x), static_cast<int>(screenB.y), color);
			Novice::DrawLine(static_cast<int>(screenA.x), static_cast<int>(screenA.y), static_cast<int>(screenC.x), static_cast<int>(screenC.y), color);
		}
	}
}



void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) {
	
	const float kGridHalfWidth = 2.0f;
	const uint32_t kSubdivision = 10;
	const float kGridEvery = (kGridHalfWidth * 2.0f) / float(kSubdivision);


	//左から右
	for (uint32_t zIndex = 0; zIndex <= kSubdivision; ++zIndex) {

		Vector3 start(-kGridHalfWidth, 0.0f, -kGridHalfWidth + zIndex * kGridEvery);
		Vector3 end(kGridHalfWidth, 0.0f, -kGridHalfWidth + zIndex * kGridEvery);

		//座標変換
		Matrix4x4 startWorldMatrix = MatrixMath::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, start);
		Matrix4x4 endWorldMatrix = MatrixMath::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, end);

		Matrix4x4 startWvpMatrix = MatrixMath::Multiply(startWorldMatrix, viewProjectionMatrix);
		Matrix4x4 endWvpMatrix = MatrixMath::Multiply(endWorldMatrix, viewProjectionMatrix);

		Vector3 startLocal = MyMath::Transform(start, startWvpMatrix);
		Vector3 endLocal = MyMath::Transform(end, endWvpMatrix);

		Vector3 startScreen = MyMath::Transform(startLocal, viewportMatrix);
		Vector3 endScreen = MyMath::Transform(endLocal, viewportMatrix);


		Novice::DrawLine(int(startScreen.x), int(startScreen.y), int(endScreen.x), int(endScreen.y), 0xAAAAAAFF);
	}


	//奥から手前
	for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex) {

		Vector3 start(-kGridHalfWidth + xIndex * kGridEvery, 0.0f, -kGridHalfWidth);
		Vector3 end(-kGridHalfWidth + xIndex * kGridEvery, 0.0f, kGridHalfWidth);

		//座標変換
		Matrix4x4 startWorldMatrix = MatrixMath::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, start);
		Matrix4x4 endWorldMatrix = MatrixMath::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, end);

		Matrix4x4 startWvpMatrix = MatrixMath::Multiply(startWorldMatrix, viewProjectionMatrix);
		Matrix4x4 endWvpMatrix = MatrixMath::Multiply(endWorldMatrix, viewProjectionMatrix);

		Vector3 startLocal = MyMath::Transform(start, startWvpMatrix);
		Vector3 endLocal = MyMath::Transform(end, endWvpMatrix);

		Vector3 startScreen = MyMath::Transform(startLocal, viewportMatrix);
		Vector3 endScreen = MyMath::Transform(endLocal, viewportMatrix);


		Novice::DrawLine(int(startScreen.x), int(startScreen.y), int(endScreen.x), int(endScreen.y), 0xAAAAAAFF);

	}


}



//Vector3の表示関数
static const int kRowHeight = 20;
static const int kColumnWidth = 60;

void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label) {

	Novice::ScreenPrintf(x, y, label);
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(x + column * kColumnWidth, y + row * kRowHeight + kRowHeight, "%6.02f", matrix.m[row][column]);
		}
	}
}



// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	int kWindowWidth = 1280;
	int kWindowHeight = 720;


Sphere sphere{
		{0.0f,0.0f,0.0f},
		1.0f
};


	// キー入力結果を受け取る箱

	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Vector3 rotate = {};
	Vector3 translate = {};

	Vector3 cameraTranslate = { 0.0f,1.9f,-6.49f };
	Vector3 cameraRotate = { 0.26f,0.0f,0.0f };


	//Matrix4x4 m1 = {
	//	3.2f,0.7f,9.6f,4.4f,
	//	5.5f,1.3f,7.8f,2.1f,
	//	6.9f,8.0f,2.6f,1.0f,
	//	0.5f,7.2f,5.1f,3.3f
	//};

	//Matrix4x4 m2 = {
	//	4.1f,6.5f,3.3f,2.2f,
	//	8.8f,0.6f,9.9f,7.7f,
	//	1.1f,5.5f,6.6f,0.0f,
	//	3.3f,9.9f,8.8f,2.2f
	//};


	//Matrix4x4 resultAdd = MatrixMath::Add(m1, m2);
	//Matrix4x4 resultMultiply = MatrixMath::Multiply(m1, m2);
	//Matrix4x4 resultSubtract = MatrixMath::Subtract(m1, m2);
	//Matrix4x4 inverseM1 = MatrixMath::Inverse(m1);
	//Matrix4x4 inverseM2 = MatrixMath::Inverse(m2);
	//Matrix4x4 transposeM1 = MatrixMath::Transpose(m1);
	//Matrix4x4 transposeM2 = MatrixMath::Transpose(m2);
	//Matrix4x4 identity = MatrixMath::MakeIdentity4x4();

	//Vector3 translate{ 4.1f,2.6f,0.8f };
	//Vector3 scale{ 1.5f,5.2f,7.3f };
	//Matrix4x4 translateMatrix = MatrixMath::MakeTranslateMatrix(translate);
	//Matrix4x4 scaleMatrix = MatrixMath::MakeScaleMatrix(scale);
	//Vector3 point{ 2.3f,3.8f,1.4f };
	//Matrix4x4 transformMatrix = {
	//	1.0f,2.0f,3.0f,4.0f,
	//	3.0f,1.0f,1.0f,2.0f,
	//	1.0f,4.0f,2.0f,3.0f,
	//	2.0f,2.0f,1.0f,3.0f
	//};
	//Vector3 transformed = MyMath::Transform(point, transformMatrix);
	//Vector3 rotate{ 0.4f,1.43f,-0.8f };
	//Matrix4x4 rotateXMatrix = MatrixMath::MakeRotateXMatrix(rotate.x);
	//Matrix4x4 rotateYMatrix = MatrixMath::MakeRotateYMatrix(rotate.y);
	//Matrix4x4 rotateZMatrix = MatrixMath::MakeRotateZMatrix(rotate.z);
	//Matrix4x4 rotateXYZMatrix = MatrixMath::Multiply(rotateXMatrix, MatrixMath::Multiply(rotateYMatrix, rotateZMatrix));

	//Vector3 scale{ 1.2f,0.79f,-2.1f };
	//Vector3 rotate{ 0.4f,1.43f,-0.8f };
	//Vector3 translate{ 2.7f,-4.15f,1.57f };
	//Matrix4x4 worldMatrix = MatrixMath::MakeAffineMatrix(scale, rotate, translate);


	/*Matrix4x4 orthographicMatrix = MatrixMath::MakeOrthographicMatrix(-160.0f, 160.0f, 200.0f, 300.0f, 0.0f, 1000.0f);
	Matrix4x4 perspectiveFovMatrix = MatrixMath::MakePerspectiveFovMatrix(0.63f, 1.33f, 0.1f, 1000.0f);
	Matrix4x4 viewportMatrix = MatrixMath::MakeViewportMatrix(100.0f, 200.0f, 600.0f, 300.0f, 0.0f, 1.0f);*/


	/*int kWindowWidth = 1280;
	int kWindowHeight = 720;


	Vector3 v1{ 1.2f,-3.9f,2.5f };
	Vector3 v2{ 2.8f,0.4f,-1.3f };
	Vector3 cross = MyMath::Cross(v1, v2);

	Vector3 rotate{};
	Vector3 translate{};

	Vector3 cameraPosition = { 0.0f,0.0f,-50.0f };

	Vector3 kLocalVertices[3] = {};
	kLocalVertices[0] = { 0.0f,6.0f,0.0f };
	kLocalVertices[1] = { 6.0f,-6.0f,0.0f };
	kLocalVertices[2] = { -6.0f,-6.0f,0.0f};*/



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


		/*MatrixScreenPrintf(0, 0, resultAdd, "Add");
		MatrixScreenPrintf(0, kRowHeight * 5, resultSubtract, "Subtract");
		MatrixScreenPrintf(0, kRowHeight * 5 * 2, resultMultiply, "Multiply");
		MatrixScreenPrintf(0, kRowHeight * 5 * 3, inverseM1, "inverseM1");
		MatrixScreenPrintf(0, kRowHeight * 5 * 4, inverseM2, "inverseM2");
		MatrixScreenPrintf(kColumnWidth * 5, 0, transposeM1, "transposeM1");
		MatrixScreenPrintf(kColumnWidth * 5,kRowHeight*5,transposeM2,"transposeM2");
		MatrixScreenPrintf(kColumnWidth * 5, kRowHeight * 5 * 2, identity, "identity");*/

	/*	MyMath::VectorScreenPrintf(0, 0, transformed, "transformed");
		MatrixScreenPrintf(0, 15, translateMatrix, "translateMatrix");
		MatrixScreenPrintf(0, 15 + kRowHeight * 5, scaleMatrix, "scaleMatrix");*/


		/*MatrixScreenPrintf(0, 0, rotateXMatrix, "rotateXMatrix");
		MatrixScreenPrintf(0, kRowHeight * 5, rotateYMatrix, "rotateYMatrix");
		MatrixScreenPrintf(0, kRowHeight * 5 * 2, rotateZMatrix, "rotateZMatrix");
		MatrixScreenPrintf(0, kRowHeight * 5 * 3, rotateXYZMatrix, "rotateXYZMatrix");*/

		//MatrixScreenPrintf(0, 0, worldMatrix, "worldMatrix");

		/*MatrixScreenPrintf(0, 0, orthographicMatrix, "orthographicMatrix");
		MatrixScreenPrintf(0, kRowHeight * 5, perspectiveFovMatrix, "perspectiveFovMatrix");
		MatrixScreenPrintf(0, kRowHeight * 10, viewportMatrix, "viewportMatrix") ;*/

		//if (keys[DIK_W] ) {
		//	translate.z += 0.5f;
		//}

		//if (keys[DIK_S]) {
		//	translate.z -= 0.5f;
		//}
		//
		//if (keys[DIK_A]) {
		//	translate.x -= 0.5f;
		//}

		//if (keys[DIK_D]) {
		//	translate.x += 0.5f;
		//}

		//
		////計算処理
		//Matrix4x4 worldMatrix = MatrixMath::MakeAffineMatrix({ 1.0f,1.0f,1.0f, }, rotate, translate);
		//Matrix4x4 cameraMatrix = MatrixMath::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, cameraPosition);
		//Matrix4x4 viewMatrix = MatrixMath::Inverse(cameraMatrix);
		//Matrix4x4 projectionMatrix = MatrixMath::MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		//Matrix4x4 worldViewProjectionMatrix = MatrixMath::Multiply(worldMatrix, MatrixMath::Multiply(viewMatrix, projectionMatrix));
		//Matrix4x4 viewportMatrix = MatrixMath::MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);
		//Vector3 screenVertices[3];
		//for (uint32_t i = 0; i < 3; ++i) {
		//	Vector3 ndcVertex = Transform(kLocalVertices[i], worldViewProjectionMatrix);
		//	screenVertices[i] = Transform(ndcVertex, viewportMatrix);
		//}

		//rotate.y += 0.1f;


		Matrix4x4 cameraMatrix = MatrixMath::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraTranslate);
		Matrix4x4 viewMatrix = MatrixMath::Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = MatrixMath::MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		Matrix4x4 worldViewProjectionMatrix = MatrixMath::Multiply(viewMatrix, projectionMatrix);
		Matrix4x4 viewportMatrix = MatrixMath::MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);




		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		/*MyMath::VectorScreenPrintf(0, 0, cross, "Cross");
		Novice::DrawTriangle(int(screenVertices[0].x), int(screenVertices[0].y), int(screenVertices[1].x), int(screenVertices[1].y), int(screenVertices[2].x), int(screenVertices[2].y), RED, kFillModeSolid);*/
		
		DrawGrid(worldViewProjectionMatrix, viewportMatrix);
		DrawSphere(sphere, worldViewProjectionMatrix, viewportMatrix, BLACK);

		ImGui::Begin("Window");
		ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);
		ImGui::DragFloat3("SphereCenter", &sphere.center.x, 0.01f);
		ImGui::DragFloat3("CameraTranslate", &sphere.radius, 0.01f);
		ImGui::End();


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

