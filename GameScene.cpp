#include "GameScene.h"
#include "Model.h"
#include <cassert>
#include <sstream>
#include <iomanip>

using namespace DirectX;

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	//safe_delete(spriteBG);
	//safe_delete(objSkydome);
	//safe_delete(objGround);
	//safe_delete(objPlayer);
	//safe_delete(modelSkydome);
	//safe_delete(modelGround);
	//safe_delete(modelPlayer);
}

void GameScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio)
{
	// nullptrチェック
	assert(dxCommon);
	assert(input);
	assert(audio);

	this->dxCommon = dxCommon;
	this->input = input;
	this->audio = audio;


	// デバッグテキスト用テクスチャ読み込み
	if (!Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png")) {
		assert(0);
		return;
	}
	// デバッグテキスト初期化
	debugText.Initialize(debugTextTexNumber);

	// テクスチャ読み込み
	if (!Sprite::LoadTexture(1, L"Resources/BackGround.png")) {
		assert(0);
		return;
	}
	// 背景スプライト生成
	spriteBG = Sprite::Create(1, { 0.0f,0.0f });
	//spriteBG->SetSize({ 1280,720 });
	// 3Dオブジェクト生成
	objSkydome = Object3d::Create();
	objGround = Object3d::Create();
	objPlayer = Object3d::Create();
	objFighter = Object3d::Create();
	objFloor = Object3d::Create();

	// テクスチャ2番に読み込み
	/*Sprite::LoadTexture(2, L"Resources/texture.png");*/

	modelSkydome = Model::LoadFromOBJ("skydome");
	modelGround = Model::LoadFromOBJ("ground");
	modelPlayer = Model::LoadFromOBJ("Player");
	modelFighter = Model::LoadFromOBJ("chr_sword");
	modelFloor = Model::LoadFromOBJ("floor");


	objSkydome->SetModel(modelSkydome);
	objGround->SetModel(modelGround);
	objPlayer->SetModel(modelPlayer);
	objFighter->SetModel(modelFighter);
	objFloor->SetModel(modelFloor);
	objFloor->SetPosition({ 0,-2,0 });
	objPlayer->SetPosition(PlayerPosition);
	objFighter->SetPosition({ 5.0f,0.0f,0.0f });
	objFloor->SetScale({ 3.0f,1.0f,3.0f });
}

void GameScene::Update()
{
	
	//// カメラ移動
	//if (input->PushKey(DIK_W) || input->PushKey(DIK_S) || input->PushKey(DIK_D) || input->PushKey(DIK_A))
	//{
	//	if (input->PushKey(DIK_W)) { Object3d::CameraMoveVector({ 0.0f,+0.06f,0.0f }); } else if (input->PushKey(DIK_S)) { Object3d::CameraMoveVector({ 0.0f,-0.06f,0.0f }); }
	//	if (input->PushKey(DIK_D)) { Object3d::CameraMoveVector({ +0.06f,0.0f,0.0f }); } else if (input->PushKey(DIK_A)) { Object3d::CameraMoveVector({ -0.06f,0.0f,0.0f }); }
	//}

	//// カメラ移動
	//if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN))
	//{
	//	if (input->PushKey(DIK_UP)) { Object3d::CameraMoveVector({ 0.0f,0.0f,+0.06f }); } else if (input->PushKey(DIK_DOWN)) { Object3d::CameraMoveVector({ 0.0f,0.0f,-0.06f }); }
	//}

	// オブジェクト移動
	if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN) || input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT))
	{
		if (input->PushKey(DIK_UP)) {
			PlayerPosition.y += 0.1f;
		}
		if (input->PushKey(DIK_DOWN)) {
			PlayerPosition.y -= 0.1f;
		}
		if (input->PushKey(DIK_LEFT)) {
			PlayerPosition.x -= 0.1f;
		}
		if (input->PushKey(DIK_RIGHT)) {
			PlayerPosition.x += 0.1f;
		}
		objPlayer->SetPosition(PlayerPosition);
	}

	objSkydome->Update();
	objGround->Update();
	objPlayer->Update();
	objFighter->Update();
	objFloor->Update();
	debugText.Print("Hello", 5.0, 5.0, 5.0f);
}

void GameScene::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCmdList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	// 背景スプライト描画
	spriteBG->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Object3d::PreDraw(cmdList);

	// 3Dオブクジェクトの描画
	//objSkydome->Draw();
	//objGround->Draw();
	objPlayer->Draw();
	objFighter->Draw();
	objFloor->Draw();
	// 3Dオブジェクト描画後処理
	Object3d::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(cmdList);

	//でバックテキストの描画
	debugText.DrawAll(cmdList);
	// スプライト描画後処理
	Sprite::PostDraw();
#pragma endregion
}
