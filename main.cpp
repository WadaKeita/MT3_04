#include <Novice.h>

#include "Function.h"

#include <imgui.h>

const char kWindowTitle[] = "LD2A_02_ワダ_ケイタ";

// 反射ベクトルを求める
Vector3 Reflect(const Vector3& input, const Vector3& normal) {
	Vector3 result;
	result = input - 2 * (Dot(input, normal)) * normal;
	return result;
}


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

	// 地面
	Plane plane;
	plane.normal = Normalize({ -0.2f,0.9f,-0.3f });
	plane.distance = 0.0f;

	// 球
	Ball ball{};
	ball.position = { 0.8f,1.2f,0.3f };
	ball.mass = 2.0f;
	ball.radius = 0.05f;
	ball.color = WHITE;

	ball.acceleration = { 0.0f,-9.8f,0.0f };

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
			ball.velocity = ball.velocity + ball.acceleration * deltaTime;
			ball.position = ball.position + ball.velocity * deltaTime;
			if (IsCollision(Sphere{ ball.position,ball.radius }, plane)) {
				Vector3 reflected = Reflect(ball.velocity, plane.normal);
				Vector3 projectToNormal = Project(reflected, plane.normal);
				Vector3 movingDirection = reflected - projectToNormal;
				ball.velocity = projectToNormal * 0.6f + movingDirection;
			}

		}

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

		DrawPlane(plane, viewProjectionMatrix, viewportMatrix, WHITE);

		DrawSphere(ball, viewProjectionMatrix, viewportMatrix, WHITE);


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
			ball.velocity = { 0.0f, 0.0f, 0.0f };
			ball.position = { 0.8f, 1.2f, 0.3f };
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
