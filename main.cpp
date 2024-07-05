#include <Novice.h>

#include "Function.h"

#include <imgui.h>

const char kWindowTitle[] = "LD2A_02_ワダ_ケイタ";

struct Spring {
	Vector3 anchor;				// 固定された端の位置
	float naturalLength;		// 自然長
	float stiffness;			// 剛性,ばね定数k
	float dampingCoefficient;	// 減衰抵抗
};

struct Ball {
	Vector3 position;		// ボールの位置
	Vector3 velocity;		// ボールの速度
	Vector3 acceleration;	// ボールの加速度
	float mass;				// ボールの質量
	float radius;			// ボールの半径
	unsigned int color;		// ボールの色
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

	// カメラ
	Camera camera{
		 { 1.0f,1.0f,1.0f },
		 { 0.0f,1.9f,-6.49f },
		 { 0.26f,0.0f,0.0f },
		0.05f,
		0.01f,
	};

	const Vector3 kGravity{ 0.0f, -9.8f, 0.0f };

	bool start = false;

	Spring spring{};
	spring.anchor = { 0.0f, 1.0f, 0.0f };
	spring.naturalLength = 0.7f;
	spring.stiffness = 100.0f;
	spring.dampingCoefficient = 2.0f;

	Ball ball{};
	ball.position = { 0.8f, 0.2f, 0.0f };
	ball.mass = 2.0f;
	ball.radius = 0.05f;
	ball.color = BLUE;

	float deltaTime = 1.0f / 60.0f;

	Sphere sphere{};
	sphere.center = ball.position;
	sphere.radius = 0.1f;

	Segment segment{};
	segment.origin = spring.anchor;
	segment.diff = ball.position - spring.anchor;

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
			Vector3 diff = ball.position - spring.anchor;
			float length = Length(diff);
			if (length != 0.0f) {
				Vector3 direction = Normalize(diff);
				Vector3 restPosition = spring.anchor + direction * spring.naturalLength;
				Vector3 displacement = length * (ball.position - restPosition);
				Vector3 restoringForce = -spring.stiffness * displacement;
				Vector3 dampingForce = -spring.dampingCoefficient * ball.velocity;
				Vector3 force = restoringForce + dampingForce;
				ball.acceleration = force / ball.mass;
			}

			ball.velocity = ball.velocity + kGravity * deltaTime;
			ball.velocity = ball.velocity + ball.acceleration * deltaTime;
			ball.position = ball.position + ball.velocity * deltaTime;

		}
		sphere.center = ball.position;
		segment.origin = spring.anchor;
		segment.diff = ball.position - spring.anchor;


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
		DrawSphere(sphere, viewProjectionMatrix, viewportMatrix, ball.color);


		ImGui::Begin("camera");
		ImGui::DragFloat3("scale", &camera.scale.x, 0.01f);
		ImGui::DragFloat3("Translation", &camera.translate.x, 0.01f);
		ImGui::DragFloat3("rotate", &camera.rotate.x, 0.01f);
		ImGui::DragFloat("translateSpeed", &camera.translateSpeed, 0.01f);
		ImGui::DragFloat("rotateSpeed", &camera.rotateSpeed, 0.01f);
		ImGui::End();

		ImGui::Begin("control");
		ImGui::DragFloat3("anchorPoint", &spring.anchor.x, 0.01f);

		if (ImGui::Button("start")) {
			start = true;
		}
		ImGui::SameLine();
		if (ImGui::Button("reset")) {
			start = false;

			spring.anchor = { 0.0f, 1.0f, 0.0f };
			ball.position = { 0.8f, 0.2f, 0.0f };
			ball.velocity = { 0,0,0 };
			ball.acceleration = { 0,0,0 };
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
