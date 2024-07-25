#pragma once
#define _USE_MATH_DEFINES
#include "math.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Matrix4x4.h"
#include "cmath"
#include <algorithm>
#include <cassert>
#include "Novice.h"

/// <summary>
/// カメラ
/// </summary>
struct Camera {
	Vector3 scale;
	Vector3 translate;
	Vector3 rotate;
	float translateSpeed;
	float rotateSpeed;
};

/// <summary>
/// 球
/// </summary>
struct Sphere {
	Vector3 center;
	float radius;
};

/// <summary>
/// 直線
/// </summary>
struct Line {
	Vector3 origin;	//!< 始点
	Vector3 diff;	//!< 終点への差分ベクトル
};

/// <summary>
/// 半直線
/// </summary>
struct Ray {
	Vector3 origin;	//!< 始点
	Vector3 diff;	//!< 終点への差分ベクトル
};

/// <summary>
/// 線分
/// </summary>
struct Segment {
	Vector3 origin;	//!< 始点
	Vector3 diff;	//!< 終点への差分ベクトル
};

/// <summary>
/// 平面
/// </summary>
struct Plane {
	Vector3 normal;	// !< 法線
	float distance;	// !< 距離
};

/// <summary>
/// 三角形
/// </summary>
struct Triangle {
	Vector3 vertices[3]; //!< 頂点
};

struct AABB {
	Vector3 min; //!< 最小点
	Vector3 max; //!< 最大点
};

struct OBB {
	Vector3 center; //!< 中心点
	Vector3 orientations[3]; //!< 座標軸。正規化・直交必須
	Vector3 size; //!< 座標軸方向の長さの半分。中心から面までの距離
};

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

struct Pendulum {
	Vector3 anchor;	// アンカーポイント。固定された端の位置
	float length;	// 紐の長さ
	float angle;	// 現在の角度
	float angularVelocity;	// 角速度ω
	float angularAcceleration;	// 角加速度
};

struct ConicalPendulum {
	Vector3 anchor;	// アンカーポイント。固定された端の位置
	float length;	// 紐の長さ
	float halfApexAngle;	// 円錐の頂角の半分
	float angle;	// 現在の角度
	float angularVelocity;	// 角速度ω
};


// ベクトル変換
Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m);


Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t);

// 加算
Vector2 Add(const Vector2& v1, const Vector2& v2);
Vector3 Add(const Vector3& v1, const Vector3& v2);

Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2);

// 減算
Vector2 Subtract(const Vector2& v1, const Vector2& v2);
Vector3 Subtract(const Vector3& v1, const Vector3& v2);

Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2);

// スカラー倍
Vector2 Multiply(float scalar, const Vector2& v);
Vector3 Multiply(float scalar, const Vector3& v);

// 内積
float Dot(const Vector3& v1, const Vector3& v2);

// 長さ（ノルム）
float Length(const Vector3& v);

// 正規化
Vector3 Normalize(const Vector3& v);

// クロス積
Vector3 Cross(const Vector3& v1, const Vector3& v2);

// 行列の積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

// 拡大縮小行列
Matrix4x4 MakeScaleMatrix(const Vector3& scale);

// X軸回転行列
Matrix4x4 MakeRotateXMatrix(float radian);

// Y軸回転行列
Matrix4x4 MakeRotateYMatrix(float radian);

// Z軸回転行列
Matrix4x4 MakeRotateZMatrix(float radian);

// 平行移動行列
Matrix4x4 MakeTranslateMatrix(const Vector3& translate);

// 3次元アフィン変換行列
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

// 透視投影行列
Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);

// 正射影行列
Matrix4x4 MakeOrthographMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);

// ビューポート行列
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);

// 座標変換
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);

// 逆行列
Matrix4x4 Inverse(const Matrix4x4& m);

Vector3 GetWorldPosition(const Matrix4x4& matrix);

/// 演算子オーバーロード

// Vector2
// 二項演算子
Vector2 operator+(const Vector2& v1, const Vector2& v2);
Vector2 operator-(const Vector2& v1, const Vector2& v2);
Vector2 operator*(float s, const Vector2& v);
Vector2 operator*(const Vector2& v, float s);
Vector2 operator/(const Vector2& v, float s);
// 単項演算子
Vector2 operator+(const Vector2& v);
Vector2 operator-(const Vector2& v);

// Vector3
// 二項演算子
Vector3 operator+(const Vector3& v1, const Vector3& v2);
Vector3 operator-(const Vector3& v1, const Vector3& v2);
Vector3 operator*(float s, const Vector3& v);
Vector3 operator*(const Vector3& v, float s);
Vector3 operator/(const Vector3& v, float s);
// 単項演算子
Vector3 operator+(const Vector3& v);
Vector3 operator-(const Vector3& v);

// Matrix4x4
// 二項演算子
//Matrix4x4 operator+(const Matrix4x4& m1, const Matrix4x4& m2);
//Matrix4x4 operator-(const Matrix4x4& m1, const Matrix4x4& m2);
Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2);

/// <summary>
/// グリッド描画
/// </summary>
void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);

float Clamp(float x, float a, float b);

/// <summary>
/// 正射影ベクトル
/// </summary>
Vector3 Project(const Vector3& v1, const Vector3& v2);

/// <summary>
/// 最近接点
/// </summary>
Vector3 ClosestPoint(const Vector3& point, const Segment& segment);

/// <summary>
/// 球描画
/// </summary>
void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);
void DrawSphere(const Ball& ball, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

/// <summary>
/// 平面描画
/// </summary>
void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

Vector3 Perpendicular(const Vector3& vector);

/// <summary>
/// 三角形描画
/// </summary>
void DrawTriangle(const Triangle& triangle, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

/// <summary>
/// AABB描画
/// </summary>
void DrawAABB(const AABB& aabb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

/// <summary>
/// OBB描画
/// </summary>
void DrawOBB(const OBB& obb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

/// <summary>
/// 直線描画
/// </summary>
void DrawLine(const Line& line, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

/// <summary>
/// 半直線描画
/// </summary>
void DrawRay(const Ray& ray, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

/// <summary>
/// 線分描画
/// </summary>
void DrawSegment(const Segment& segment, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

/// <summary>
/// ベジェ曲線描画
/// </summary>
void DrawBezier(const Vector3& controlPoint0, const Vector3& controlPoint1, const Vector3& controlPoint2,
	const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

/// <summary>
/// 衝突判定：球と球
/// </summary>
bool IsCollision(const Sphere& s1, const Sphere& s2);

/// <summary>
/// 衝突判定：平面と球
/// </summary>
bool IsCollision(const Sphere& sphere, const Plane& plane);

/// <summary>
/// 衝突判定：線分と平面
/// </summary>
bool IsCollision(const Segment& segment, const Plane& plane);

/// <summary>
/// 衝突判定：直線と平面
/// </summary>
bool IsCollision(const Line& line, const Plane& plane);

/// <summary>
/// 衝突判定：半直線と平面
/// </summary>
bool IsCollision(const Ray& ray, const Plane& plane);

/// <summary>
/// 衝突判定：三角形と線
/// </summary>
bool IsCollision(const Triangle& triangle, const Segment& segment);

/// <summary>
/// 衝突判定：AABBとAABB
/// </summary>
bool IsCollision(const AABB& aabb1, const AABB& aabb2);

/// <summary>
/// 衝突判定：AABBと球
/// </summary>
bool IsCollision(const AABB& aabb, const Sphere& sphere);

/// <summary>
/// 衝突判定：AABBと線分
/// </summary>
bool IsCollision(const AABB& aabb, const Segment& segment);


/// <summary>
/// カメラ操作
/// </summary>
void CameraOperation(Camera& camera, char* keys);
