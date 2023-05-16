#include "stdafx.h"
#include "Drop_item.h"
#include "Left_arm_weapons.h"
#include "Player.h"
#include "Customize_UI.h"
#include "Customize_UI_ver2.h"
#include "GameCamera.h"
#include "Game.h"
#include <vector>       // ヘッダファイルインクルード
using namespace std;

Drop_item::Drop_item() 
{
	
}

Drop_item::~Drop_item() 
{
	
}

bool Drop_item::Start()
{
	drop_player = FindGO<Player>("player");
	customize_UI_ver2 = FindGO<Customize_UI_ver2>("customize_ui_ver2");
	m_gameCamera = FindGO<GameCamera>("gamecamera");
	m_game = FindGO<Game>("game");

	Set_Drop_item();

	return true;
}

void Drop_item::Set_Drop_item()
{
	//落とした武器によって初期化情報を変更する
	if (drop_kinds == 2)
	{
		Drop_item_Render.Init("Assets/modelData/machine_gun_drop.tkm");
		Drop_item_Render.SetScale(modelSize);	//最初は小さめに設定
	}
	else if (drop_kinds == 4)
	{
		Drop_item_Render.Init("Assets/modelData/GIgaton_cannon.tkm");
		Drop_item_Render.SetScale(modelSize);	//最初は小さめに設定
	}
	else if (drop_kinds == 6)
	{
		Drop_item_Render.Init("Assets/modelData/battleship_gun_Drop.tkm");
		Drop_item_Render.SetScale(modelSize);	//最初は小さめに設定
	}
}

void Drop_item::Update() 
{
	if (drop_player->game_state == 0) 
	{
		//サイズの処理
		SetSize();

		//動きの処理
		Float();

		//取得処理
		Vector3 diff = drop_player->player_position - Drop_position;
		
		if (diff.Length() < 100.0f) 
		{
			SoundSource* m_SE = NewGO<SoundSource>(0);			//一回再生すると終わりなのでインスタンスを保持させない為にここでNewGOする
			m_SE->Init(enByuSE);								//初期化
			m_SE->SetVolume(1.0f * m_game->SEvol);				//音量調整
			m_SE->Play(false);

			GetState = true;
			
			//アイテムを拾ったらカスタマイズ画面に飛ぶ
			//拾った武器の種類を教えてやる
			customize_UI_ver2->custom_kinds = drop_kinds;
			//カスタム画面のセットアップを行う
			customize_UI_ver2->Setup();
			
			//全ての初期化
			customize_UI_ver2->trance_setup();
			//プレイヤーのステート変更(カスタム画面へ)
			drop_player->game_state = 3;
			
			DeleteGO(this);
		}

		if (m_deleteCount <= 0)
		{
			DeleteGO(this);
		}
		m_deleteCount--;
	}
}

void Drop_item::SetSize()
{	
	//落とした武器によって大きさを変える
	if (drop_kinds == 2)		//マシンガン
	{
		//だんだん大きくする
		modelSize += 0.05;

		//ある程度の大きさになったらストップ
		if (modelSize >= 2.5f)
		{
			modelSize = 2.5f;
		}
	}
	else if (drop_kinds == 4)	//ギガトンキャノン
	{
		//だんだん大きくする
		modelSize += 0.02;

		//ある程度の大きさになったらストップ
		if (modelSize >= 1.0f)
		{
			modelSize = 1.0f;
		}
	}
	else if (drop_kinds == 6)	//戦艦砲
	{
		//だんだん大きくする
		modelSize += 0.05;
		//ある程度の大きさになったらストップ
		if (modelSize >= 2.5f)
		{
			modelSize = 2.5f;
		}
	}

	//更新
	Drop_item_Render.SetScale(modelSize);
}

void Drop_item::Float() 
{
	float_counter += 1;
	if (float_counter % 90 == 0) 
	{
		float_level*=-1;
	}
	Drop_position.y += float_level;
	Drop_rotation.AddRotationDegY(2.0f);
	//アイテムの状態を更新
	Drop_item_Render.SetPosition(Drop_position);
	Drop_item_Render.SetRotation(Drop_rotation);
	Drop_item_Render.Update();
}

void Drop_item::Render(RenderContext& rc) 
{
	Drop_item_Render.Draw(rc);
}