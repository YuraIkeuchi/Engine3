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
	// nullptr�`�F�b�N
	assert(dxCommon);
	assert(input);
	assert(audio);

	this->dxCommon = dxCommon;
	this->input = input;
	this->audio = audio;


	// �f�o�b�O�e�L�X�g�p�e�N�X�`���ǂݍ���
	if (!Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png")) {
		assert(0);
		return;
	}
	// �f�o�b�O�e�L�X�g������
	debugText.Initialize(debugTextTexNumber);

	// �e�N�X�`���ǂݍ���
	if (!Sprite::LoadTexture(1, L"Resources/BackGround.png")) {
		assert(0);
		return;
	}
	// �w�i�X�v���C�g����
	spriteBG = Sprite::Create(1, { 0.0f,0.0f });
	//spriteBG->SetSize({ 1280,720 });
	// 3D�I�u�W�F�N�g����
	objSkydome = Object3d::Create();
	objGround = Object3d::Create();
	objPlayer = Object3d::Create();
	objFighter = Object3d::Create();
	objFloor = Object3d::Create();

	// �e�N�X�`��2�Ԃɓǂݍ���
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
	
	//// �J�����ړ�
	//if (input->PushKey(DIK_W) || input->PushKey(DIK_S) || input->PushKey(DIK_D) || input->PushKey(DIK_A))
	//{
	//	if (input->PushKey(DIK_W)) { Object3d::CameraMoveVector({ 0.0f,+0.06f,0.0f }); } else if (input->PushKey(DIK_S)) { Object3d::CameraMoveVector({ 0.0f,-0.06f,0.0f }); }
	//	if (input->PushKey(DIK_D)) { Object3d::CameraMoveVector({ +0.06f,0.0f,0.0f }); } else if (input->PushKey(DIK_A)) { Object3d::CameraMoveVector({ -0.06f,0.0f,0.0f }); }
	//}

	//// �J�����ړ�
	//if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN))
	//{
	//	if (input->PushKey(DIK_UP)) { Object3d::CameraMoveVector({ 0.0f,0.0f,+0.06f }); } else if (input->PushKey(DIK_DOWN)) { Object3d::CameraMoveVector({ 0.0f,0.0f,-0.06f }); }
	//}

	// �I�u�W�F�N�g�ړ�
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
	// �R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCmdList();

#pragma region �w�i�X�v���C�g�`��
	// �w�i�X�v���C�g�`��O����
	Sprite::PreDraw(cmdList);
	// �w�i�X�v���C�g�`��
	spriteBG->Draw();

	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();
	// �[�x�o�b�t�@�N���A
	dxCommon->ClearDepthBuffer();
#pragma endregion

#pragma region 3D�I�u�W�F�N�g�`��
	// 3D�I�u�W�F�N�g�`��O����
	Object3d::PreDraw(cmdList);

	// 3D�I�u�N�W�F�N�g�̕`��
	//objSkydome->Draw();
	//objGround->Draw();
	objPlayer->Draw();
	objFighter->Draw();
	objFloor->Draw();
	// 3D�I�u�W�F�N�g�`��㏈��
	Object3d::PostDraw();
#pragma endregion

#pragma region �O�i�X�v���C�g�`��
	// �O�i�X�v���C�g�`��O����
	Sprite::PreDraw(cmdList);

	//�Ńo�b�N�e�L�X�g�̕`��
	debugText.DrawAll(cmdList);
	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();
#pragma endregion
}
