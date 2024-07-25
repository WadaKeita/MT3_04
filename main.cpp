#include <Novice.h>

#include "Function.h"

#include <imgui.h>

const char kWindowTitle[] = "LD2A_02_ワダ_ケイタ";

struct ConicalPendulum {
	Vector3 anchor;	// アンカーポイント。固定された端の位置
	float length;	// 紐の長さ
	float halfApexAngle;	// 円錐の頂角の半分
	float angle;	// 現在の角度
	float angularVelocity;	// 角速度ω
};


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	const int kWindowWidth = 1280;
	const int kWindowHeight = 720;

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	const float deltaTime = 1.0f / 60.0f;

	bool start = false;

	// カメラ
	Camera camera{
		{ 1.0f, 1.0f, 1.0f },
		{ 0.0f, 1.9f, -6.49f },
		{ 0.26f, 0.0f, 0.0f },
		0.05f,
		0.01f,
	};

	ConicalPendulum conicalPendulum;
	conicalPendulum.anchor = { 0.0f,1.0f,0.0f };
	conicalPendulum.length = 0.8f;
	conicalPendulum.halfApexAngle = 0.7f;
	conicalPendulum.angle = 0.7f;
	conicalPendulum.angularVelocity = 0.0f;


	Sphere sphere{};
	sphere.center = { 0.0f, 0.0f, 0.0f };
	sphere.radius = 0.08f;

	Segment segment{};
	segment.origin = conicalPendulum.anchor;
	segment.diff = sphere.center - conicalPendulum.anchor;

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

		// カメラ移動操作
		CameraOperation(camera, keys);


		if (start) {
			conicalPendulum.angularVelocity = std::sqrtf(9.8f / (conicalPendulum.length * std::cos(conicalPendulum.halfApexAngle)));
			conicalPendulum.angle += conicalPendulum.angularVelocity * deltaTime;
		}

		float radius = std::sin(conicalPendulum.halfApexAngle) * conicalPendulum.length;
		float height = std::cos(conicalPendulum.halfApexAngle) * conicalPendulum.length;

		sphere.center.x = conicalPendulum.anchor.x + std::cos(conicalPendulum.angle) * radius;
		sphere.center.y = conicalPendulum.anchor.y - height;
		sphere.center.z = conicalPendulum.anchor.z - std::sin(conicalPendulum.angle) * radius;


		segment.diff = sphere.center - conicalPendulum.anchor;

		Matrix4x4 cameraMatrix = MakeAffineMatrix(camera.scale, camera.rotate, camera.translate);
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		Matrix4x4 viewProjectionMatrix = Multiply(viewMatrix, projectionMatrix);
		//Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		// グリッド描画
		DrawGrid(viewProjectionMatrix, viewportMatrix);

		DrawSegment(segment, viewProjectionMatrix, viewportMatrix, WHITE);

		DrawSphere(sphere, viewProjectionMatrix, viewportMatrix, WHITE);


		ImGui::Begin("camera");
		ImGui::DragFloat3("scale", &camera.scale.x, 0.01f);
		ImGui::DragFloat3("Translation", &camera.translate.x, 0.01f);
		ImGui::DragFloat3("rotate", &camera.rotate.x, 0.01f);
		ImGui::DragFloat("translateSpeed", &camera.translateSpeed, 0.01f);
		ImGui::DragFloat("rotateSpeed", &camera.rotateSpeed, 0.01f);
		ImGui::End();

		ImGui::Begin("control");

		if (ImGui::Button("start")) {
			start = true;
		}
		ImGui::SameLine();
		if (ImGui::Button("reset")) {
			start = false;
			conicalPendulum.anchor = { 0.0f,1.0f,0.0f };
			conicalPendulum.length = 0.8f;
			conicalPendulum.halfApexAngle = 0.7f;
			conicalPendulum.angle = 0.7f;
			conicalPendulum.angularVelocity = 0.0f;
		}
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
