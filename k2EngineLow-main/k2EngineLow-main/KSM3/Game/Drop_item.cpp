#include "stdafx.h"
#include "Drop_item.h"
#include "Left_arm_weapons.h"
#include "Player.h"
#include "Customize_UI.h"
#include <vector>       // ヘッダファイルインクルード
using namespace std;

Drop_item::Drop_item() {
	drop_player = FindGO<Player>("player");

	drop_weapons[1] = 1;

	Drop_position = { 200.0f,50.0f,500.0f };

	Set_Drop_item();
}

void Drop_item::Set_Drop_item() {
	for (int i = 0; i < 12; i++) {
		if (drop_weapons[i] == 1) {
			Drop_item_Render.Init("Assets/modelData/battleship_gun_Drop.tkm");
			drop_kinds = i;
		}

}
	
	Drop_item_Render.SetPosition(Drop_position);
}

Drop_item::~Drop_item() {

}

void Drop_item::Update() {
	if (drop_player->game_state == 0) {
		
		Float();
		Drop_item_Render.Update();

		//取得処理
		Vector3 diff = drop_player->player_position - Drop_position;
		
		if (diff.Length() < 100.0f) {
			GetState = true;
			customize_UI = NewGO<Customize_UI>(3, "customize_UI");
		}
	}
}

void Drop_item::Float() {
	float_counter += 1;
	if (float_counter % 90 == 0) {
		float_level*=-1;
	}
	Drop_position.y += float_level;
	Drop_rotation.AddRotationDegY(2.0f);
	Drop_item_Render.SetPosition(Drop_position);
	Drop_item_Render.SetRotation(Drop_rotation);
}

void Drop_item::Render(RenderContext& rc) {
	Drop_item_Render.Draw(rc);
}