#include "stdafx.h"
#include "Drop_item.h"
#include "Left_arm_weapons.h"
#include "Player.h"
#include "Customize_UI.h"
#include "Customize_UI_ver2.h"
#include "GameCamera.h"
#include "Game.h"

namespace
{
	//アイテムの大きさ
	const float MACHINEGUN_DROP_SCALE = 2.5f;
	const float GIGATONCANNON_DROP_SCALE = 1.0f;
	const float BATTLESHIPGUN_DROP_SCALE = 2.5f;

	//大きくなる速さ
	const float ADD_MACHINEGUN_SCALE = 0.05f;
	const float ADD_GIGATONCANNON_SCALE = 0.02f;
	const float ADD_BATTLESHIPGUN_SCALE = 0.05f;

	//回転量
	const float MODEL_ROT_AMOUNT = 2.0f;

	//反転するまでの時間
	const int REVERSAL_COUNT = 90;

	//アイテムを拾える距離
	const float CAN_GET_DISTANCE = 100.0f;
}

Drop_item::Drop_item() 
{
	
}

Drop_item::~Drop_item() 
{
	
}

bool Drop_item::Start()
{

	//クラスを探す
	m_game = FindGO<Game>("game");
	m_player = FindGO<Player>("player");
	m_gameCamera = FindGO<GameCamera>("gamecamera");
	m_customizeUI = FindGO<Customize_UI_ver2>("customize_ui_ver2");


	//ドロップアイテムの初期化
	InitDropItem();


	return true;
}

void Drop_item::InitDropItem()
{

	//メモリの確保(make_unique関数内部でnewしている)
	m_dropItemModel = std::make_unique<ModelRender>();


	//落とした武器によって初期化情報を変更する
	if (m_dropKinds == MACHINEGUN_NUM)
	{
		m_dropItemModel->Init("Assets/modelData/machine_gun_drop.tkm");
	}
	else if (m_dropKinds == GIGATONCANNON_NUM)
	{
		m_dropItemModel->Init("Assets/modelData/GIgaton_cannon.tkm");
	}
	else if (m_dropKinds == BATTLESHIPGUN_NUM)
	{
		m_dropItemModel->Init("Assets/modelData/battleship_gun_Drop.tkm");
	}
		
	m_dropItemModel->SetScale(m_modelSize);	
	m_dropItemModel->Update();
}

void Drop_item::Update()
{

	//メインゲーム中のみ実行
	if (m_player->GetGameState() != MAIN_GAME_NUM)
	{
		return;
	}


	//サイズの処理
	CalcModelScale();


	//動きの処理
	Float();


	//アイテムの取得処理
	ExecuteGetItem();


	//時間が経過すると
	if (m_deleteCount <= 0)
	{
		//削除処理
		ExecuteDelete();
	}


	//時間経過
	m_deleteCount--;

}

void Drop_item::ExecuteGetItem()
{
	//プレイヤーとアイテムの距離を計算する
	Vector3 diff = m_player->GetPlayerPosition() - m_position;

	if (diff.Length() < CAN_GET_DISTANCE)
	{
		SoundSource* m_SE = NewGO<SoundSource>(0);			//一回再生すると終わりなのでインスタンスを保持させない為にここでNewGOする
		m_SE->Init(enByuSE);								//初期化
		m_SE->SetVolume(1.0f * m_game->GetSEVol());			//音量調整
		m_SE->Play(false);


		//拾った武器の種類を教えてやる
		m_customizeUI->SetDropItem(m_dropKinds);


		//カスタム画面のセットアップを行う
		m_customizeUI->SetUp();


		//全ての初期化
		m_customizeUI->TranceSetUp();


		//プレイヤーのステート変更(カスタム画面へ)
		m_player->SetGameState(CUSTOMIZE_NUM);


		//削除処理
		ExecuteDelete();
	}
}

void Drop_item::CalcModelScale()
{	
	//落とした武器によって大きさを変える
	if (m_dropKinds == MACHINEGUN_NUM)		//マシンガン
	{
		//だんだん大きくする
		m_modelSize += ADD_MACHINEGUN_SCALE;

		//ある程度の大きさになったらストップ
		m_modelSize = min(m_modelSize, MACHINEGUN_DROP_SCALE);
		
	}
	else if (m_dropKinds == GIGATONCANNON_NUM)	//ギガトンキャノン
	{
		//だんだん大きくする
		m_modelSize += ADD_GIGATONCANNON_SCALE;

		//ある程度の大きさになったらストップ
		m_modelSize = min(m_modelSize, GIGATONCANNON_DROP_SCALE);
		
	}
	else if (m_dropKinds == BATTLESHIPGUN_NUM)	//戦艦砲
	{
		//だんだん大きくする
		m_modelSize += ADD_BATTLESHIPGUN_SCALE;

		//ある程度の大きさになったらストップ
		m_modelSize = min(m_modelSize, BATTLESHIPGUN_DROP_SCALE);
		
	}

	//更新
	m_dropItemModel->SetScale(m_modelSize);
	m_dropItemModel->Update();
}

void Drop_item::Float() 
{
	//一定のカウントごとに
	if (m_floatCount > REVERSAL_COUNT)
	{
		//移動方向の反転
		m_floatLevel *= -1;

		//カウントリセット
		m_floatCount = 0;
	}

	//移動
	m_position.y += m_floatLevel;

	//回転
	m_rotation.AddRotationDegY(MODEL_ROT_AMOUNT);

	//更新
	m_dropItemModel->SetPosition(m_position);
	m_dropItemModel->SetRotation(m_rotation);
	m_dropItemModel->Update();
	
	//カウントアップ
	m_floatCount++;
}

void Drop_item::ExecuteDelete()
{
	//自分自身の削除
	DeleteGO(this);
	
	//リストから消す
	m_game->RemoveDropItemFromList(this);	
}

void Drop_item::Render(RenderContext& rc) 
{
	//描画
	m_dropItemModel->Draw(rc);
}