#include <Novice.h>
#include<Vector3.h>
#include<stdio.h>
#include<Matrix4x4.h>

const char kWindowTitle[] = "LC1A_16_スズキ_ミノリ_タイトル";


//加算
Vector3 Add(const Vector3& v1,const Vector3& v2);
//減算
Vector3 Subtract(const Vector3& v1, const Vector3& v2);
//スカラー倍
Vector3 Multiply(float scalar, const Vector3& v);
//内積
float Dot(const Vector3& v1, const Vector3& v2);
//長さ(ノルム)
float Length(const Vector3& v);
//正規化
Vector3 Normalize(const Vector3& v);




//Vector3の表示関数
static const int kColumnWidth = 60;
void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColumnWidth + 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColumnWidth + 3, y, "%s", label);
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱

	char keys[256] = {0};
	char preKeys[256] = {0};

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

		//Vector3の関数



		//減算



		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

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

Vector3 Add(const Vector3& v1, const Vector3& v2)
{
	Vector3 v3;

	v3.x = v1.x + v2.x;
	v3.y = v1.y + v2.y;
	v3.z = v1.z + v2.z;

	return v3;
}

Vector3 Subtract(const Vector3& v1, const Vector3& v2)
{
	Vector3 v3;

	v3.x = v1.x - v2.x;
	v3.y = v1.y - v2.y;
	v3.z = v1.z - v2.z;

	return v3;
}

Vector3 Multiply(float scalar, const Vector3& v)
{
	Vector3 v3;

	v3.x = v.x * scalar;
	v3.y = v.y * scalar;
	v3.z = v.z * scalar;

	return v3;
}

float Dot(const Vector3& v1, const Vector3& v2)
{
	return 0.0f;
}

float Length(const Vector3& v)
{
	return 0.0f;
}

Vector3 Normalize(const Vector3& v)
{
	return Vector3();
}
