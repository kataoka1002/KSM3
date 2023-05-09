#include "stdafx.h"
#include "Drop_item.h"
#include "Left_arm_weapons.h"
#include "Player.h"
#include "Customize_UI.h"
#include "Customize_UI_ver2.h"
#include "GameCamera.h"
#include <vector>       // ヘッダファイルインクルード
using namespace std;

Drop_item::Drop_item() 
{
	//drop_kinds = 2;

	//drop_weapons[1] = 1;

	//Drop_position = { 200.0f,50.0f,500.0f };

	
}

Drop_item::~Drop_item() 
{
	
}

bool Drop_item::Start()
{
	drop_player = FindGO<Player>("player");
	customize_UI_ver2 = FindGO<Customize_UI_ver2>("customize_ui_ver2");
	m_gameCamera = FindGO<GameCamera>("gamecamera");

	Set_Drop_item();

	return true;
}

void Drop_item::Set_Drop_item()
{
	//落とした武器によって初期化情報を変更する
	if (drop_kinds == 2)
	{
		Drop_item_Render.Init("Assets/modelData/machine_gun_drop.tkm");
	}
	else if (drop_kinds == 6)
	{
		Drop_item_Render.Init("Assets/modelData/battleship_gun_Drop.tkm");
	}

	//Drop_item_Render.SetPosition(Drop_position);
}

void Drop_item::Update() 
{
	if (drop_player->game_state == 0) 
	{
		//動きの処理
		Float();

		//取得処理
		Vector3 diff = drop_player->player_position - Drop_position;
		
		if (diff.Length() < 100.0f) 
		{
			GetState = true;
			
			//アイテムを拾ったらカスタマイズ画面に飛ぶ
			//カスタム画面のセットアップを行う
			customize_UI_ver2->Setup();
			//拾った武器の種類を教えてやる
			customize_UI_ver2->custom_kinds = drop_kinds;
			customize_UI_ver2->trance_setup();
			//プレイヤーのステート変更(カスタム画面へ)
			drop_player->game_state = 3;
			
			DeleteGO(this);
		}
	}
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