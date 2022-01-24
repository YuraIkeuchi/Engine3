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
	//safe_delete(objFighter);
	//safe_delete(modelSkydome);
	//safe_delete(modelGround);
	//safe_delete(modelFighter);
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

	// �e�N�X�`���ǂݍ���
	if (!Sprite::LoadTexture(1, L"Resources/BackGround.png")) {
		assert(0);
		return;
	}
	// �w�i�X�v���C�g����
	spriteBG = Sprite::Create(1, { 0.0f,0.0f });
	// 3D�I�u�W�F�N�g����
	objSkydome = Object3d::Create();
	objGround = Object3d::Create();
	objFighter = Object3d::Create();

	// �e�N�X�`��2�Ԃɓǂݍ���
	/*Sprite::LoadTexture(2, L"Resources/texture.png");*/

	modelSkydome = Model::LoadFromOBJ("skydome");
	modelGround = Model::LoadFromOBJ("ground");
	modelFighter = Model::LoadFromOBJ("Player");

	objSkydome->SetModel(modelSkydome);
	objGround->SetModel(modelGround);
	objFighter->SetModel(modelFighter);
}

void GameScene::Update()
{
	//// �I�u�W�F�N�g�ړ�
	//if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN) || input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT))
	//{
	//	// ���݂̍��W���擾
	//	XMFLOAT3 position = object3d->GetPosition();

	//	// �ړ���̍��W���v�Z
	//	if (input->PushKey(DIK_UP)) { position.y += 1.0f; }
	//	else if (input->PushKey(DIK_DOWN)) { position.y -= 1.0f; }
	//	if (input->PushKey(DIK_RIGHT)) { position.x += 1.0f; }
	//	else if (input->PushKey(DIK_LEFT)) { position.x -= 1.0f; }

	//	// ���W�̕ύX�𔽉f
	//	object3d->SetPosition(position);
	//}

	// �J�����ړ�
	if (input->PushKey(DIK_W) || input->PushKey(DIK_S) || input->PushKey(DIK_D) || input->PushKey(DIK_A))
	{
		if (input->PushKey(DIK_W)) { Object3d::CameraMoveVector({ 0.0f,+0.06f,0.0f }); } else if (input->PushKey(DIK_S)) { Object3d::CameraMoveVector({ 0.0f,-0.06f,0.0f }); }
		if (input->PushKey(DIK_D)) { Object3d::CameraMoveVector({ +0.06f,0.0f,0.0f }); } else if (input->PushKey(DIK_A)) { Object3d::CameraMoveVector({ -0.06f,0.0f,0.0f }); }
	}

	// �J�����ړ�
	if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN))
	{
		if (input->PushKey(DIK_UP)) { Object3d::CameraMoveVector({ 0.0f,0.0f,+0.06f }); } else if (input->PushKey(DIK_DOWN)) { Object3d::CameraMoveVector({ 0.0f,0.0f,-0.06f }); }
	}

	objSkydome->Update();
	objGround->Update();
	objFighter->Update();

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
	objFighter->Draw();

	// 3D�I�u�W�F�N�g�`��㏈��
	Object3d::PostDraw();
#pragma endregion

#pragma region �O�i�X�v���C�g�`��
	// �O�i�X�v���C�g�`��O����
	Sprite::PreDraw(cmdList);

	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();
#pragma endregion
}
