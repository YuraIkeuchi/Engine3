#pragma region include周りの宣言
#include<Windows.h>
#include<d3d12.h>
#include<d3dx12.h>
#include<dxgi1_6.h>
#include<vector>
#include<string>
#include<DirectXMath.h>
#include<d3dcompiler.h>
#define DIRECTiNPUT_VERSION 
#include<dinput.h>
#include<dinput.h>

#include<DirectXTex.h>
#include<wrl.h>

#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"d3d12.lib")

#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

#include"Sprite.h"
#include"Input.h"
#include"WinApp.h"
#include"DirectXCommon.h"
#include"Object3d.h"
#include"Model.h"
#include"GameScene.h"
#pragma endregion

using namespace DirectX;
using namespace Microsoft::WRL;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
#pragma region DirectXの初期化
	
	WinApp* winApp = nullptr;
	//初期化
	winApp = new WinApp();
	winApp->Initialize();

	MSG msg{};
#ifdef _DEBUG
	ID3D12Debug* debugController;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)))) {
		debugController->EnableDebugLayer();
	}
#endif
#pragma endregion
#pragma region 入力と共通部分のポインタ置き場
	//DirectXの共通部分
	DirectXCommon* dxCommon = nullptr;
	dxCommon = new DirectXCommon();
	dxCommon->Initialize(winApp);
	HRESULT result;

	// キーボードなどの入力処理
	Input* input = nullptr;
	input = new Input();
	input->Initialize(winApp);

	// オーディオの初期化
	Audio* audio = nullptr;
	audio = new Audio();
	if (!audio->Initialize()) {
		assert(0);
		return 1;
	}

#pragma endregion
	//頂点データ3点分の座標
#pragma region 描画初期化処理

	//射影変換行列の作り

	// スプライト静的初期化
	if (!Sprite::StaticInitialize(dxCommon->GetDev(), WinApp::window_width, WinApp::window_height)) {
		assert(0);
		return 1;
	}

#pragma endregion
#pragma region 静的初期化
	Object3d::StaticInitialize(dxCommon->GetDev(), WinApp::window_width, WinApp::window_height);
#pragma endregion
	GameScene* gscene = new GameScene();
	gscene->Initialize(dxCommon, input, audio);

	while (true) {
		//ウィンドウメッセージ処理
		if (winApp->ProcessMessage()) {
			break;
		}
		//更新処理
		input->Update();
		gscene->Update();
		//描画処理
		dxCommon->PreDraw();
		gscene->Draw();
		dxCommon->PostDraw();//ループ内の末尾らへんに
	}
#pragma endregion
#pragma endregion
	winApp->Finalize();
	//解放処理
	delete input;
	delete dxCommon;
	delete winApp;
	return 0;
}

