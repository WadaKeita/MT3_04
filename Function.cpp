#include "Function.h"

float Clamp(float x, float a, float b) {
	if (a < b) {
		if (x < a) {
			return a;
		}
		else if (x > b) {
			return b;
		}
		else {
			return x;
		}
	}
	else if (a > b) {
		if (x > a) {
			return a;
		}
		else if (x < b) {
			return b;
		}
		else {
			return x;
		}
	}
	return 0;
}

// ベクトル変換
Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m) {

	Vector3 result{
		v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0],
		v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1],
		v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2],
	};

	return result;
}

Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t) {
	Vector3 result;

	result.x = (1.0f - t) * v1.x + t * v2.x;
	result.y = (1.0f - t) * v1.y + t * v2.y;
	result.z = (1.0f - t) * v1.z + t * v2.z;

	return result;
}


/// -^-^- ベクトル演算 -^-^- ///

// 加算
Vector2 Add(const Vector2& v1, const Vector2& v2) {
	Vector2 result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;

	return result;
}
Vector3 Add(const Vector3& v1, const Vector3& v2) {
	Vector3 result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;

	return result;
}

Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result;

	for (int column = 0; column < 4; column++) {
		for (int row = 0; row < 4; row++) {
			result.m[column][row] = m1.m[column][row] + m2.m[column][row];
		}
	}

	return result;
};

// 減算
Vector2 Subtract(const Vector2& v1, const Vector2& v2) {
	Vector2 result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;

	return result;
}
Vector3 Subtract(const Vector3& v1, const Vector3& v2) {
	Vector3 result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;

	return result;
};

Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result;

	for (int column = 0; column < 4; column++) {
		for (int row = 0; row < 4; row++) {
			result.m[column][row] = m1.m[column][row] - m2.m[column][row];
		}
	}

	return result;
};

// スカラー倍
Vector2 Multiply(float scalar, const Vector2& v) {
	Vector2 result;

	result.x = v.x * scalar;
	result.y = v.y * scalar;

	return result;
}
Vector3 Multiply(float scalar, const Vector3& v) {
	Vector3 result;

	result.x = v.x * scalar;
	result.y = v.y * scalar;
	result.z = v.z * scalar;

	return result;
};


// 内積
float Dot(const Vector3& v1, const Vector3& v2) { return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z); };

// 長さ（ノルム）
float Length(const Vector3& v) { return sqrtf(Dot(v, v)); };

// 正規化
Vector3 Normalize(const Vector3& v) {
	Vector3 result;

	result.x = v.x / Length(v);
	result.y = v.y / Length(v);
	result.z = v.z / Length(v);

	return result;
};

// クロス積
Vector3 Cross(const Vector3& v1, const Vector3& v2) { return { {v1.y * v2.z - v1.z * v2.y}, {v1.z * v2.x - v1.x * v2.z}, {v1.x * v2.y - v1.y * v2.x} }; };


/// -^-^- 行列演算 -^-^- ///

// 行列の積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result;

	for (int column = 0; column < 4; column++) {
		for (int row = 0; row < 4; row++) {

			result.m[column][row] = (m1.m[column][0] * m2.m[0][row]) + (m1.m[column][1] * m2.m[1][row]) + (m1.m[column][2] * m2.m[2][row]) + (m1.m[column][3] * m2.m[3][row]);
		}
	}

	return result;
};

// 拡大縮小行列
Matrix4x4 MakeScaleMatrix(const Vector3& scale) {
	Matrix4x4 result = { 0 };

	result.m[0][0] = scale.x;
	result.m[1][1] = scale.y;
	result.m[2][2] = scale.z;
	result.m[3][3] = 1;

	return result;
};

// X軸回転行列
Matrix4x4 MakeRotateXMatrix(float radian) {
	Matrix4x4 result = {
		{
			{ 1, 0, 0, 0},
			{ 0, std::cos(radian), std::sin(radian), 0 },
			{ 0, -std::sin(radian), std::cos(radian), 0 },
			{ 0, 0, 0, 1 }
		},
	};

	return result;
};

// Y軸回転行列
Matrix4x4 MakeRotateYMatrix(float radian) {
	Matrix4x4 result = {
		{
			{ std::cos(radian), 0, -std::sin(radian), 0 },
			{ 0, 1, 0, 0},
			{ std::sin(radian), 0, std::cos(radian), 0 },
			{ 0, 0, 0, 1}
		},
	};

	return result;
};

// Z軸回転行列
Matrix4x4 MakeRotateZMatrix(float radian) {
	Matrix4x4 result = {
		{
			{std::cos(radian), std::sin(radian), 0, 0},
			{-std::sin(radian), std::cos(radian), 0, 0},
			{0, 0, 1, 0},
			{0, 0, 0, 1}
		},
	};

	return result;
};

// 平行移動行列
Matrix4x4 MakeTranslateMatrix(const Vector3& translate) {
	Matrix4x4 result = { 0 };

	result.m[0][0] = 1;
	result.m[1][1] = 1;
	result.m[2][2] = 1;
	result.m[3][3] = 1;

	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;

	return result;
};

// 3次元アフィン変換行列
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {
	Matrix4x4 result = { 0 };

	result = Multiply(MakeScaleMatrix(scale), Multiply(MakeRotateXMatrix(rotate.x), Multiply(MakeRotateYMatrix(rotate.y), MakeRotateZMatrix(rotate.z))));
	result = Multiply(result, MakeTranslateMatrix(translate));

	return result;
};

// 透視投影行列
Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip) {
	Matrix4x4 result = {
		{
		 {1.0f / (aspectRatio * std::tan(fovY / 2.0f)), 0, 0, 0},
		 {0, 1.0f / std::tan(fovY / 2.0f), 0, 0},
		 {0, 0, farClip / (farClip - nearClip), 1},
		 {0, 0, (-nearClip * farClip) / (farClip - nearClip), 0},
		 },
	};
	return result;
};

// 正射影行列
Matrix4x4 MakeOrthographMatrix(float left, float top, float right, float bottom, float nearClip, float farClip) {
	Matrix4x4 result = {
		{
		 {2.0f / (right - left), 0, 0, 0},
		 {0, 2.0f / (top - bottom), 0, 0},
		 {0, 0, 1.0f / (farClip - nearClip), 0},
		 {(left + right) / (left - right), (top + bottom) / (bottom - top), nearClip / (nearClip - farClip), 1},
		 },
	};
	return result;
};

// ビューポート行列
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth) {
	Matrix4x4 result = {
		{
		 {width / 2.0f, 0, 0, 0},
		 {0, -(height / 2.0f), 0, 0},
		 {0, 0, maxDepth - minDepth, 0},
		 {left + (width / 2.0f), top + (height / 2.0f), minDepth, 1},
		 },
	};
	return result;
};

// 座標変換
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix) {
	Vector3 result{};

	result.x = (vector.x * matrix.m[0][0]) + (vector.y * matrix.m[1][0]) + (vector.z * matrix.m[2][0]) + (1.0f * matrix.m[3][0]);
	result.y = (vector.x * matrix.m[0][1]) + (vector.y * matrix.m[1][1]) + (vector.z * matrix.m[2][1]) + (1.0f * matrix.m[3][1]);
	result.z = (vector.x * matrix.m[0][2]) + (vector.y * matrix.m[1][2]) + (vector.z * matrix.m[2][2]) + (1.0f * matrix.m[3][2]);
	float w = (vector.x * matrix.m[0][3]) + (vector.y * matrix.m[1][3]) + (vector.z * matrix.m[2][3]) + (1.0f * matrix.m[3][3]);
	//assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;

	return result;
};

// 逆行列
Matrix4x4 Inverse(const Matrix4x4& m) {
	Matrix4x4 result;

	float x = 1 / (m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3] + m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1] + m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2]

		- m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1] - m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3] - m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2]

		- m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3] - m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1] - m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2]

		+ m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1] + m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3] + m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2]

		+ m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3] + m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1] + m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2]

		- m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1] - m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3] - m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2]

		- m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0] - m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0] - m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0]

		+ m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0] + m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0] + m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0]);

	result.m[0][0] = ((m.m[1][1] * m.m[2][2] * m.m[3][3]) + (m.m[1][2] * m.m[2][3] * m.m[3][1]) + (m.m[1][3] * m.m[2][1] * m.m[3][2]) - (m.m[1][3] * m.m[2][2] * m.m[3][1]) -
		(m.m[1][2] * m.m[2][1] * m.m[3][3]) - (m.m[1][1] * m.m[2][3] * m.m[3][2])) *
		x;

	result.m[0][1] = ((-m.m[0][1] * m.m[2][2] * m.m[3][3]) - (m.m[0][2] * m.m[2][3] * m.m[3][1]) - (m.m[0][3] * m.m[2][1] * m.m[3][2]) + (m.m[0][3] * m.m[2][2] * m.m[3][1]) +
		(m.m[0][2] * m.m[2][1] * m.m[3][3]) + (m.m[0][1] * m.m[2][3] * m.m[3][2])) *
		x;

	result.m[0][2] = ((m.m[0][1] * m.m[1][2] * m.m[3][3]) + (m.m[0][2] * m.m[1][3] * m.m[3][1]) + (m.m[0][3] * m.m[1][1] * m.m[3][2]) - (m.m[0][3] * m.m[1][2] * m.m[3][1]) -
		(m.m[0][2] * m.m[1][1] * m.m[3][3]) - (m.m[0][1] * m.m[1][3] * m.m[3][2])) *
		x;

	result.m[0][3] = ((-m.m[0][1] * m.m[1][2] * m.m[2][3]) - (m.m[0][2] * m.m[1][3] * m.m[2][1]) - (m.m[0][3] * m.m[1][1] * m.m[2][2]) + (m.m[0][3] * m.m[1][2] * m.m[2][1]) +
		(m.m[0][2] * m.m[1][1] * m.m[2][3]) + (m.m[0][1] * m.m[1][3] * m.m[2][2])) *
		x;

	result.m[1][0] = ((-m.m[1][0] * m.m[2][2] * m.m[3][3]) - (m.m[1][2] * m.m[2][3] * m.m[3][0]) - (m.m[1][3] * m.m[2][0] * m.m[3][2]) + (m.m[1][3] * m.m[2][2] * m.m[3][0]) +
		(m.m[1][2] * m.m[2][0] * m.m[3][3]) + (m.m[1][0] * m.m[2][3] * m.m[3][2])) *
		x;

	result.m[1][1] = ((m.m[0][0] * m.m[2][2] * m.m[3][3]) + (m.m[0][2] * m.m[2][3] * m.m[3][0]) + (m.m[0][3] * m.m[2][0] * m.m[3][2]) - (m.m[0][3] * m.m[2][2] * m.m[3][0]) -
		(m.m[0][2] * m.m[2][0] * m.m[3][3]) - (m.m[0][0] * m.m[2][3] * m.m[3][2])) *
		x;

	result.m[1][2] = ((-m.m[0][0] * m.m[1][2] * m.m[3][3]) - (m.m[0][2] * m.m[1][3] * m.m[3][0]) - (m.m[0][3] * m.m[1][0] * m.m[3][2]) + (m.m[0][3] * m.m[1][2] * m.m[3][0]) +
		(m.m[0][2] * m.m[1][0] * m.m[3][3]) + (m.m[0][0] * m.m[1][3] * m.m[3][2])) *
		x;

	result.m[1][3] = ((m.m[0][0] * m.m[1][2] * m.m[2][3]) + (m.m[0][2] * m.m[1][3] * m.m[2][0]) + (m.m[0][3] * m.m[1][0] * m.m[2][2]) - (m.m[0][3] * m.m[1][2] * m.m[2][0]) -
		(m.m[0][2] * m.m[1][0] * m.m[2][3]) - (m.m[0][0] * m.m[1][3] * m.m[2][2])) *
		x;

	result.m[2][0] = ((m.m[1][0] * m.m[2][1] * m.m[3][3]) + (m.m[1][1] * m.m[2][3] * m.m[3][0]) + (m.m[1][3] * m.m[2][0] * m.m[3][1]) - (m.m[1][3] * m.m[2][1] * m.m[3][0]) -
		(m.m[1][1] * m.m[2][0] * m.m[3][3]) - (m.m[1][0] * m.m[2][3] * m.m[3][1])) *
		x;

	result.m[2][1] = ((-m.m[0][0] * m.m[2][1] * m.m[3][3]) - (m.m[0][1] * m.m[2][3] * m.m[3][0]) - (m.m[0][3] * m.m[2][0] * m.m[3][1]) + (m.m[0][3] * m.m[2][1] * m.m[3][0]) +
		(m.m[0][1] * m.m[2][0] * m.m[3][3]) + (m.m[0][0] * m.m[2][3] * m.m[3][1])) *
		x;

	result.m[2][2] = ((m.m[0][0] * m.m[1][1] * m.m[3][3]) + (m.m[0][1] * m.m[1][3] * m.m[3][0]) + (m.m[0][3] * m.m[1][0] * m.m[3][1]) - (m.m[0][3] * m.m[1][1] * m.m[3][0]) -
		(m.m[0][1] * m.m[1][0] * m.m[3][3]) - (m.m[0][0] * m.m[1][3] * m.m[3][1])) *
		x;

	result.m[2][3] = ((-m.m[0][0] * m.m[1][1] * m.m[2][3]) - (m.m[0][1] * m.m[1][3] * m.m[2][0]) - (m.m[0][3] * m.m[1][0] * m.m[2][1]) + (m.m[0][3] * m.m[1][1] * m.m[2][0]) +
		(m.m[0][1] * m.m[1][0] * m.m[2][3]) + (m.m[0][0] * m.m[1][3] * m.m[2][1])) *
		x;

	result.m[3][0] = ((-m.m[1][0] * m.m[2][1] * m.m[3][2]) - (m.m[1][1] * m.m[2][2] * m.m[3][0]) - (m.m[1][2] * m.m[2][0] * m.m[3][1]) + (m.m[1][2] * m.m[2][1] * m.m[3][0]) +
		(m.m[1][1] * m.m[2][0] * m.m[3][2]) + (m.m[1][0] * m.m[2][2] * m.m[3][1])) *
		x;

	result.m[3][1] = ((m.m[0][0] * m.m[2][1] * m.m[3][2]) + (m.m[0][1] * m.m[2][2] * m.m[3][0]) + (m.m[0][2] * m.m[2][0] * m.m[3][1]) - (m.m[0][2] * m.m[2][1] * m.m[3][0]) -
		(m.m[0][1] * m.m[2][0] * m.m[3][2]) - (m.m[0][0] * m.m[2][2] * m.m[3][1])) *
		x;

	result.m[3][2] = ((-m.m[0][0] * m.m[1][1] * m.m[3][2]) - (m.m[0][1] * m.m[1][2] * m.m[3][0]) - (m.m[0][2] * m.m[1][0] * m.m[3][1]) + (m.m[0][2] * m.m[1][1] * m.m[3][0]) +
		(m.m[0][1] * m.m[1][0] * m.m[3][2]) + (m.m[0][0] * m.m[1][2] * m.m[3][1])) *
		x;

	result.m[3][3] = ((m.m[0][0] * m.m[1][1] * m.m[2][2]) + (m.m[0][1] * m.m[1][2] * m.m[2][0]) + (m.m[0][2] * m.m[1][0] * m.m[2][1]) - (m.m[0][2] * m.m[1][1] * m.m[2][0]) -
		(m.m[0][1] * m.m[1][0] * m.m[2][2]) - (m.m[0][0] * m.m[1][2] * m.m[2][1])) *
		x;

	return result;
};

Vector3 GetWorldPosition(const Matrix4x4& matrix) {

	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の並行移動成分を取得（ワールド座標）
	worldPos.x = matrix.m[3][0];
	worldPos.y = matrix.m[3][1];
	worldPos.z = matrix.m[3][2];

	return worldPos;
}

// 正射影ベクトル
Vector3 Project(const Vector3& v1, const Vector3& v2) {
	Vector3 result{};

	result = Multiply(Dot(v1, Normalize(v2)), Normalize(v2));

	return result;
};

// 最近接点
Vector3 ClosestPoint(const Vector3& point, const Segment& segment) {
	Vector3 result{};

	result = Add(segment.origin, Project(Subtract(point, segment.origin), segment.diff));

	result.x = Clamp(result.x, segment.origin.x, segment.origin.x + segment.diff.x);
	result.y = Clamp(result.y, segment.origin.y, segment.origin.y + segment.diff.y);
	result.z = Clamp(result.z, segment.origin.z, segment.origin.z + segment.diff.z);

	return result;
};


/// -^-^- 演算子オーバーロード -^-^- ///
// Vector2
// 二項演算子
Vector2 operator+(const Vector2& v1, const Vector2& v2) { return Add(v1, v2); }
Vector2 operator-(const Vector2& v1, const Vector2& v2) { return Subtract(v1, v2); }
Vector2 operator*(float s, const Vector2& v) { return Multiply(s, v); }
Vector2 operator*(const Vector2& v, float s) { return s * v; }
Vector2 operator/(const Vector2& v, float s) { return Multiply(1.0f / s, v); }
// 単項演算子
Vector2 operator+(const Vector2& v) { return v; }
Vector2 operator-(const Vector2& v) { return { -v.x,-v.y }; }

// Vector3
// 二項演算子
Vector3 operator+(const Vector3& v1, const Vector3& v2) { return Add(v1, v2); }
Vector3 operator-(const Vector3& v1, const Vector3& v2) { return Subtract(v1, v2); }
Vector3 operator*(float s, const Vector3& v) { return Multiply(s, v); }
Vector3 operator*(const Vector3& v, float s) { return s * v; }
Vector3 operator/(const Vector3& v, float s) { return Multiply(1.0f / s, v); }
// 単項演算子
Vector3 operator+(const Vector3& v) { return v; }
Vector3 operator-(const Vector3& v) { return { -v.x,-v.y,-v.z }; }

// Matrix4x4
// 二項演算子
//Matrix4x4 operator+(const Matrix4x4& m1, const Matrix4x4& m2) { return Add(m1, m2); }
//Matrix4x4 operator-(const Matrix4x4& m1, const Matrix4x4& m2) { return Subtract(m1, m2); }
Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2) { return Multiply(m1, m2); }


/// -^-^- 描画 -^-^- ///

// グリッド描画
void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) {
	const float kGridHalfWidth = 2.0f;
	const uint32_t kSobdivision = 10;
	const float kGridEvery = (kGridHalfWidth * 2.0f) / float(kSobdivision);
	Vector3 linePos[2]{};
	// 奥から手前への線を順々に引いていく
	for (uint32_t xIndex = 0; xIndex <= kSobdivision; ++xIndex) {
		linePos[0] = { -kGridHalfWidth, 0.0f, kGridHalfWidth - (kGridEvery * xIndex) };
		linePos[1] = { kGridHalfWidth, 0.0f, kGridHalfWidth - (kGridEvery * xIndex) };

		for (uint32_t i = 0; i < 2; i++) {
			Vector3 ndcVertex = Transform(linePos[i], viewProjectionMatrix);
			linePos[i] = Transform(ndcVertex, viewportMatrix);
		}
		if (xIndex == 5) {
			Novice::DrawLine(int(linePos[0].x), int(linePos[0].y), int(linePos[1].x), int(linePos[1].y), 0x000000FF);
		}
		else {
			Novice::DrawLine(int(linePos[0].x), int(linePos[0].y), int(linePos[1].x), int(linePos[1].y), 0xAAAAAAFF);
		}
	}
	// 左から右への線を順々に引いていく
	for (uint32_t zIndex = 0; zIndex <= kSobdivision; ++zIndex) {
		linePos[0] = { kGridHalfWidth - (kGridEvery * zIndex), 0.0f, -kGridHalfWidth };
		linePos[1] = { kGridHalfWidth - (kGridEvery * zIndex), 0.0f, kGridHalfWidth };

		for (uint32_t i = 0; i < 2; i++) {
			Vector3 ndcVertex = Transform(linePos[i], viewProjectionMatrix);
			linePos[i] = Transform(ndcVertex, viewportMatrix);
		}
		if (zIndex == 5) {
			Novice::DrawLine(int(linePos[0].x), int(linePos[0].y), int(linePos[1].x), int(linePos[1].y), 0x000000FF);
		}
		else {
			Novice::DrawLine(int(linePos[0].x), int(linePos[0].y), int(linePos[1].x), int(linePos[1].y), 0xAAAAAAFF);
		}
	}
}

// 球描画
void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {


	Matrix4x4 worldMatrix = MakeAffineMatrix({ 1,1,1 }, { 0,0,0 }, sphere.center);
	Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, viewProjectionMatrix);

	const uint32_t kSubdivision = 10; // 分割数
	const float kLonEvery = (2.0f * (float)M_PI) / kSubdivision; // 経度分割1つ分の角度
	const float kLatEvery = (float)M_PI / kSubdivision; // 緯度分割1つ分の角度

	// 緯度の方向に分割 -π/2 ～ π/2
	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {
		float lat = -(float)M_PI / 2.0f + kLatEvery * latIndex; // 現在の緯度

		// 緯度方向に分割 0 ～ 2π
		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
			float lon = lonIndex * kLonEvery;
			// world座標系でのa,b,cを求める
			Vector3 a, b, c;

			a = { sphere.radius * cosf(lat) * cosf(lon), sphere.radius * sinf(lat), sphere.radius * cosf(lat) * sin(lon) };
			b = { sphere.radius * cosf(lat + kLatEvery) * cosf(lon), sphere.radius * sinf(lat + kLatEvery), sphere.radius * cosf(lat + kLatEvery) * sin(lon) };
			c = { sphere.radius * cosf(lat) * cosf(lon + kLonEvery), sphere.radius * sinf(lat), sphere.radius * cosf(lat) * sin(lon + kLonEvery) };

			// a,b,cをScreen座標系まで変換
			a = Transform(Transform(a, worldViewProjectionMatrix), viewportMatrix);
			b = Transform(Transform(b, worldViewProjectionMatrix), viewportMatrix);
			c = Transform(Transform(c, worldViewProjectionMatrix), viewportMatrix);


			// ab,bcで線を引く
			Novice::DrawLine((int)a.x, (int)a.y, (int)b.x, (int)b.y, color);
			Novice::DrawLine((int)a.x, (int)a.y, (int)c.x, (int)c.y, color);
		}
	}
}

// 平面描画
void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	Vector3 center = Multiply(plane.distance, plane.normal);
	Vector3 perpendiculars[4];
	perpendiculars[0] = Normalize(Perpendicular(plane.normal));
	perpendiculars[1] = { -perpendiculars[0].x,-perpendiculars[0].y,-perpendiculars[0].z };
	perpendiculars[2] = Cross(plane.normal, perpendiculars[0]);
	perpendiculars[3] = { -perpendiculars[2].x,-perpendiculars[2].y,-perpendiculars[2].z };

	Vector3 points[4];
	for (int32_t index = 0; index < 4; ++index) {
		Vector3 extend = Multiply(2.0f, perpendiculars[index]);
		Vector3 point = Add(center, extend);
		points[index] = Transform(Transform(point, viewProjectionMatrix), viewportMatrix);
	}

	Novice::DrawLine((int)points[0].x, (int)points[0].y, (int)points[2].x, (int)points[2].y, color);
	Novice::DrawLine((int)points[2].x, (int)points[2].y, (int)points[1].x, (int)points[1].y, color);
	Novice::DrawLine((int)points[1].x, (int)points[1].y, (int)points[3].x, (int)points[3].y, color);
	Novice::DrawLine((int)points[3].x, (int)points[3].y, (int)points[0].x, (int)points[0].y, color);
}

Vector3 Perpendicular(const Vector3& vector) {
	if (vector.x != 0.0f || vector.y != 0.0f) {
		return{ -vector.y,vector.x,0.0f };
	}
	return { 0.0f,-vector.z,vector.y };
}

// 三角形描画
void DrawTriangle(const Triangle& triangle, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {

	Vector3 points[3];
	for (int32_t index = 0; index < 3; index++) {
		points[index] = Transform(Transform(triangle.vertices[index], viewProjectionMatrix), viewportMatrix);
	}

	Novice::DrawLine((int)points[0].x, (int)points[0].y, (int)points[1].x, (int)points[1].y, color);
	Novice::DrawLine((int)points[1].x, (int)points[1].y, (int)points[2].x, (int)points[2].y, color);
	Novice::DrawLine((int)points[2].x, (int)points[2].y, (int)points[0].x, (int)points[0].y, color);
}

// AABB描画
void DrawAABB(const AABB& aabb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {

	Vector3 points[8];
	points[0] = { aabb.min.x, aabb.min.y, aabb.min.z };
	points[1] = { aabb.min.x, aabb.min.y, aabb.max.z };
	points[2] = { aabb.max.x, aabb.min.y, aabb.min.z };
	points[3] = { aabb.max.x, aabb.min.y, aabb.max.z };

	points[4] = { aabb.min.x, aabb.max.y, aabb.min.z };
	points[5] = { aabb.min.x, aabb.max.y, aabb.max.z };
	points[6] = { aabb.max.x, aabb.max.y, aabb.min.z };
	points[7] = { aabb.max.x, aabb.max.y, aabb.max.z };

	for (int32_t index = 0; index < 8; index++) {
		points[index] = Transform(Transform(points[index], viewProjectionMatrix), viewportMatrix);
	}

	Novice::DrawLine((int)points[0].x, (int)points[0].y, (int)points[1].x, (int)points[1].y, color);
	Novice::DrawLine((int)points[0].x, (int)points[0].y, (int)points[2].x, (int)points[2].y, color);
	Novice::DrawLine((int)points[0].x, (int)points[0].y, (int)points[4].x, (int)points[4].y, color);

	Novice::DrawLine((int)points[6].x, (int)points[6].y, (int)points[2].x, (int)points[2].y, color);
	Novice::DrawLine((int)points[6].x, (int)points[6].y, (int)points[4].x, (int)points[4].y, color);
	Novice::DrawLine((int)points[6].x, (int)points[6].y, (int)points[7].x, (int)points[7].y, color);

	Novice::DrawLine((int)points[5].x, (int)points[5].y, (int)points[1].x, (int)points[1].y, color);
	Novice::DrawLine((int)points[5].x, (int)points[5].y, (int)points[4].x, (int)points[4].y, color);
	Novice::DrawLine((int)points[5].x, (int)points[5].y, (int)points[7].x, (int)points[7].y, color);

	Novice::DrawLine((int)points[3].x, (int)points[3].y, (int)points[1].x, (int)points[1].y, color);
	Novice::DrawLine((int)points[3].x, (int)points[3].y, (int)points[2].x, (int)points[2].y, color);
	Novice::DrawLine((int)points[3].x, (int)points[3].y, (int)points[7].x, (int)points[7].y, color);
}

// OBB描画
void DrawOBB(const OBB& obb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {

	Matrix4x4 worldMatrix = {
		{
			{ { obb.orientations[0].x }, { obb.orientations[0].y }, { obb.orientations[0].z }, { 0 } },
			{ { obb.orientations[1].x }, { obb.orientations[1].y }, { obb.orientations[1].z }, { 0 } },
			{ { obb.orientations[2].x }, { obb.orientations[2].y }, { obb.orientations[2].z }, { 0 } },
			{ { obb.center.x }, { obb.center.y }, { obb.center.z }, { 1 } },
		},
	};

	Vector3 points[8];
	points[0] = { -obb.size.x, -obb.size.y, -obb.size.z };
	points[1] = { -obb.size.x, -obb.size.y, obb.size.z };
	points[2] = { obb.size.x, -obb.size.y, -obb.size.z };
	points[3] = { obb.size.x, -obb.size.y, obb.size.z };

	points[4] = { -obb.size.x, obb.size.y, -obb.size.z };
	points[5] = { -obb.size.x, obb.size.y, obb.size.z };
	points[6] = { obb.size.x, obb.size.y, -obb.size.z };
	points[7] = { obb.size.x, obb.size.y, obb.size.z };


	Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, viewProjectionMatrix);

	for (int32_t index = 0; index < 8; index++) {
		points[index] = Transform(Transform(points[index], worldViewProjectionMatrix), viewportMatrix);
	}

	Novice::DrawLine((int)points[0].x, (int)points[0].y, (int)points[1].x, (int)points[1].y, color);
	Novice::DrawLine((int)points[0].x, (int)points[0].y, (int)points[2].x, (int)points[2].y, color);
	Novice::DrawLine((int)points[0].x, (int)points[0].y, (int)points[4].x, (int)points[4].y, color);

	Novice::DrawLine((int)points[6].x, (int)points[6].y, (int)points[2].x, (int)points[2].y, color);
	Novice::DrawLine((int)points[6].x, (int)points[6].y, (int)points[4].x, (int)points[4].y, color);
	Novice::DrawLine((int)points[6].x, (int)points[6].y, (int)points[7].x, (int)points[7].y, color);

	Novice::DrawLine((int)points[5].x, (int)points[5].y, (int)points[1].x, (int)points[1].y, color);
	Novice::DrawLine((int)points[5].x, (int)points[5].y, (int)points[4].x, (int)points[4].y, color);
	Novice::DrawLine((int)points[5].x, (int)points[5].y, (int)points[7].x, (int)points[7].y, color);

	Novice::DrawLine((int)points[3].x, (int)points[3].y, (int)points[1].x, (int)points[1].y, color);
	Novice::DrawLine((int)points[3].x, (int)points[3].y, (int)points[2].x, (int)points[2].y, color);
	Novice::DrawLine((int)points[3].x, (int)points[3].y, (int)points[7].x, (int)points[7].y, color);

}

// 直線描画
void DrawLine(const Line& line, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {

	Vector3 start = Transform(Transform(line.origin, viewProjectionMatrix), viewportMatrix);
	Vector3 end = Transform(Transform(Add(line.origin, line.diff), viewProjectionMatrix), viewportMatrix);

	Novice::DrawLine(int(start.x), int(start.y), int(end.x), int(end.y), color);
}

// 半直線描画
void DrawRay(const Ray& ray, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {

	Vector3 start = Transform(Transform(ray.origin, viewProjectionMatrix), viewportMatrix);
	Vector3 end = Transform(Transform(Add(ray.origin, ray.diff), viewProjectionMatrix), viewportMatrix);

	Novice::DrawLine(int(start.x), int(start.y), int(end.x), int(end.y), color);
}

// 線分描画
void DrawSegment(const Segment& segment, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {

	Vector3 start = Transform(Transform(segment.origin, viewProjectionMatrix), viewportMatrix);
	Vector3 end = Transform(Transform(Add(segment.origin, segment.diff), viewProjectionMatrix), viewportMatrix);

	Novice::DrawLine(int(start.x), int(start.y), int(end.x), int(end.y), color);
}

// ベジェ曲線描画
void DrawBezier(const Vector3& controlPoint0, const Vector3& controlPoint1, const Vector3& controlPoint2,
	const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {

	Vector3 point[11];

	float t = 0;
	for (int i = 0; i < 11; i++) {
		Vector3 p0p1 = Lerp(controlPoint0, controlPoint1, t);
		Vector3 p1p2 = Lerp(controlPoint1, controlPoint2, t);

		point[i] = Lerp(p0p1, p1p2, t);

		point[i] = Transform(Transform(point[i], viewProjectionMatrix), viewportMatrix);

		t += 0.1f;
	}

	// 描画
	for (int i = 0; i < 10; i++) {
		Novice::DrawLine(int(point[i].x), int(point[i].y), int(point[int(i + 1)].x), int(point[int(i + 1)].y), color);
	}

}

/// -^-^- 衝突判定 -^-^- ///

// 衝突判定：球と球
bool IsCollision(const Sphere& s1, const Sphere& s2) {
	// 2つの球の中心点間の距離を求める
	float distance = Length({ s2.center.x - s1.center.x,s2.center.y - s1.center.y,s2.center.z - s1.center.z });
	// 半径の合計よりも短ければ衝突
	if (distance <= s1.radius + s2.radius) {
		return true;
	}
	return false;
}

// 衝突判定：平面と球
bool IsCollision(const Sphere& sphere, const Plane& plane) {

	float k = Dot(plane.normal, sphere.center) - plane.distance;

	k = k < 0 ? -k : k; // kの絶対値をとる

	if (k <= sphere.radius) {
		return true;
	}
	return false;
}

// 衝突判定：線分と平面
bool IsCollision(const Segment& segment, const Plane& plane) {
	// まずは垂直判定を行うために、法線と線の内積を求める
	float dot = Dot(plane.normal, segment.diff);

	// 垂直=平行であるので、衝突しているはずがない
	if (dot == 0.0f) {
		return false;
	}

	// tを求める
	float t = (plane.distance - Dot(segment.origin, plane.normal)) / dot;

	if (t < 0) {
		return false;
	}
	else if (t > 1) {
		return false;
	}
	return true;
}

// 衝突判定：直線と平面
bool IsCollision(const Line& line, const Plane& plane) {
	// まずは垂直判定を行うために、法線と線の内積を求める
	float dot = Dot(plane.normal, line.diff);

	// 垂直=平行であるので、衝突しているはずがない
	if (dot == 0.0f) {
		return false;
	}

	// tを求める
	float t = (plane.distance - Dot(line.origin, plane.normal)) / dot;

	if (t == 0) {
		return false;
	}
	return true;
}

// 衝突判定：半直線と平面
bool IsCollision(const Ray& ray, const Plane& plane) {
	// まずは垂直判定を行うために、法線と線の内積を求める
	float dot = Dot(plane.normal, ray.diff);

	// 垂直=平行であるので、衝突しているはずがない
	if (dot == 0.0f) {
		return false;
	}

	// tを求める
	float t = (plane.distance - Dot(ray.origin, plane.normal)) / dot;

	if (t < 0) {
		return false;
	}
	return true;
}

// 衝突判定：三角形と線
bool IsCollision(const Triangle& triangle, const Segment& segment) {
	// 三角形の頂点から平面を求める
	Plane plane;
	Vector3 v1, v2;
	v1 = Subtract(triangle.vertices[1], triangle.vertices[0]);
	v2 = Subtract(triangle.vertices[2], triangle.vertices[1]);

	plane.normal = Normalize(Cross(v1, v2));
	plane.distance = Dot(triangle.vertices[0], plane.normal);

	// 線と平面が当たっているか
	if (IsCollision(segment, plane) == true) {

		float dot = Dot(plane.normal, segment.diff);
		// 垂直=平行であるので、衝突しているはずがない
		if (dot == 0.0f) {
			return false;
		}
		// tを求める
		float t = (plane.distance - Dot(segment.origin, plane.normal)) / dot;

		Vector3 point = Multiply(t, segment.diff);
		point = Add(point, segment.origin);

		Vector3 cross01 = Cross(Subtract(triangle.vertices[1], triangle.vertices[0]), Subtract(point, triangle.vertices[1]));
		Vector3 cross12 = Cross(Subtract(triangle.vertices[2], triangle.vertices[1]), Subtract(point, triangle.vertices[2]));
		Vector3 cross20 = Cross(Subtract(triangle.vertices[0], triangle.vertices[2]), Subtract(point, triangle.vertices[0]));

		if (Dot(cross01, plane.normal) >= 0.0f &&
			Dot(cross12, plane.normal) >= 0.0f &&
			Dot(cross20, plane.normal) >= 0.0f) {

			return true;
		}
	}
	return false;
}

// 衝突判定：AABBとAABB
bool IsCollision(const AABB& aabb1, const AABB& aabb2) {
	if ((aabb1.min.x <= aabb2.max.x && aabb1.max.x >= aabb2.min.x) &&
		(aabb1.min.y <= aabb2.max.y && aabb1.max.y >= aabb2.min.y) &&
		(aabb1.min.z <= aabb2.max.z && aabb1.max.z >= aabb2.min.z)) {
		return true;
	}
	return false;
}

// 衝突判定：AABBと球
bool IsCollision(const AABB& aabb, const Sphere& sphere) {
	// 最近接点を求める
	Vector3 closestPoint{ std::clamp(sphere.center.x,aabb.min.x,aabb.max.x),
		std::clamp(sphere.center.y, aabb.min.y, aabb.max.y),
		std::clamp(sphere.center.z, aabb.min.z, aabb.max.z) };
	// 最近接点と球の中心との距離を求める
	float distance = Length(Subtract(closestPoint, sphere.center));
	// 距離が半径よりも小さければ衝突
	if (distance <= sphere.radius) {
		return true;
	}
	return false;
}

// 衝突判定：AABBと線分
bool IsCollision(const AABB& aabb, const Segment& segment) {

	float txMin = (aabb.min.x - segment.origin.x) / segment.diff.x;
	float txMax = (aabb.max.x - segment.origin.x) / segment.diff.x;

	float tyMin = (aabb.min.y - segment.origin.y) / segment.diff.y;
	float tyMax = (aabb.max.y - segment.origin.y) / segment.diff.y;

	float tzMin = (aabb.min.z - segment.origin.z) / segment.diff.z;
	float tzMax = (aabb.max.z - segment.origin.z) / segment.diff.z;

	float tNearX = min(txMin, txMax); float tFarX = max(txMin, txMax);
	float tNearY = min(tyMin, tyMax); float tFarY = max(tyMin, tyMax);
	float tNearZ = min(tzMin, tzMax); float tFarZ = max(tzMin, tzMax);

	// AABBとの衝突点（貫通点）のtが小さい方
	float tmin = max(max(tNearX, tNearY), tNearZ);
	// AABBとの衝突点（貫通点）のtが大きい方
	float tmax = min(min(tFarX, tFarY), tFarZ);

	if (tmin <= tmax) {
		if ((tmin >= 0 && tmin <= 1) || (tmax >= 0 && tmax <= 1) || (tmin < 0 && tmax >1)) {
			return true;
		}
	}
	return false;
}

void CameraOperation(Camera& camera, char* keys)
{

	if (keys[DIK_W]) {
		camera.translate.z += camera.translateSpeed;
	}
	if (keys[DIK_S]) {
		camera.translate.z -= camera.translateSpeed;
	}
	if (keys[DIK_A]) {
		camera.translate.x -= camera.translateSpeed;
	}
	if (keys[DIK_D]) {
		camera.translate.x += camera.translateSpeed;
	}
	if (keys[DIK_LEFT]) {
		camera.rotate.y -= camera.rotateSpeed;
	}
	if (keys[DIK_RIGHT]) {
		camera.rotate.y += camera.rotateSpeed;
	}
	if (keys[DIK_UP]) {
		camera.rotate.x -= camera.rotateSpeed;
	}
	if (keys[DIK_DOWN]) {
		camera.rotate.x += camera.rotateSpeed;
	}
}
