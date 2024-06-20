#include <Novice.h>
#include"MyMath.h"

const char kWindowTitle[] = "LC1A_16_スズキ_ミノリ_タイトル";



static const int kRowHeight = 20;



//Vector3の表示関数

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱

	char keys[256] = {0};
	char preKeys[256] = {0};

	Vector3 v1{ 1.0f,3.0f,-5.0f };
	Vector3 v2{ 4.0f,-1.0f,2.0f };
	float k = { 4.0f };

	Vector3 resultAdd = MyMath::Add(v1, v2);
	Vector3 resultSubtract = MyMath::Subtract(v1, v2);
	Vector3 resultMultiply = MyMath::Multiply(k,v1);
	float resultDot = MyMath::Dot(v1, v2);
	float resultLength = MyMath::Length(v1);
	Vector3 resultNormalize = MyMath::Normalize(v2);


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

		MyMath::VectorScreenPrintf(0, 0, resultAdd, ":Add");
		MyMath::VectorScreenPrintf(0, kRowHeight, resultSubtract, ":Subtract");
		MyMath::VectorScreenPrintf(0, kRowHeight * 2, resultMultiply, ":Multiply");
		Novice::ScreenPrintf(0, kRowHeight * 3, "%.02f:Dot", resultDot);
		Novice::ScreenPrintf(0, kRowHeight * 4, "%.02f:Length", resultLength);
		MyMath::VectorScreenPrintf(0, kRowHeight * 5, resultNormalize, ":Normalize");


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

