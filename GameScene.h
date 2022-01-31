#pragma once

#include "DirectXCommon.h"
#include <DirectXMath.h>
#include "Input.h"
#include "Sprite.h"
#include "Object3d.h"
#include "Audio.h"
#include "DebugText.h"
#include "CollisionPrimitive.h"
#include "Collision.h"

/// ゲームシーン
class GameScene
{
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

private: // 静的メンバ変数
	static const int debugTextTexNumber = 0;

public: // メンバ関数

	//コンストクラタ
	GameScene();

	//デストラクタ
	~GameScene();

	//初期化
	void Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio);

	//毎フレーム処理
	void Update();

	//描画
	void Draw();

private://メンバ変数
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;
	Audio* audio = nullptr;
	DebugText debugText;
	Collision* collision;
	///ゲームシーン用
	Sprite* spriteBG = nullptr;

	Model* modelSkydome = nullptr;
	Model* modelGround = nullptr;
	Model* modelFighter = nullptr;
	Model* modelPlayer = nullptr;
	Model* modelFloor = nullptr;

	Object3d* objSkydome = nullptr;
	Object3d* objGround = nullptr;
	Object3d* objFighter = nullptr;
	Object3d* objPlayer = nullptr;
	Object3d* objFloor = nullptr;
	XMFLOAT3 PlayerPosition = { -5.0f,0.0f,0.0f };
	XMFLOAT3 FighterPosition = { 5.0f,0.0f,0.0f };
	XMFLOAT3 FloorPosition = { 0.0f,-2.0f,0.0f };
	//当たり判定 球
	Sphere sphere;
	//当たり判定 平面
	Plane plane;
	//当たり判定 三角形
	Triangle triangle;
	//当たり判定 レイ
	Ray ray;



};

