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

/// �Q�[���V�[��
class GameScene
{
private: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

private: // �ÓI�����o�ϐ�
	static const int debugTextTexNumber = 0;

public: // �����o�֐�

	//�R���X�g�N���^
	GameScene();

	//�f�X�g���N�^
	~GameScene();

	//������
	void Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio);

	//���t���[������
	void Update();

	//�`��
	void Draw();

private://�����o�ϐ�
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;
	Audio* audio = nullptr;
	DebugText debugText;
	Collision* collision;
	///�Q�[���V�[���p
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
	//�����蔻�� ��
	Sphere sphere;
	//�����蔻�� ����
	Plane plane;
	//�����蔻�� �O�p�`
	Triangle triangle;
	//�����蔻�� ���C
	Ray ray;



};

