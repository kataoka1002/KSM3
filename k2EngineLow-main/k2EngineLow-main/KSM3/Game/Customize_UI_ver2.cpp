#include "stdafx.h"
#include "Customize_UI_ver2.h"
#include"Player.h"
#include "Left_arm_weapons.h"
#include"Right_arm_weapons.h"
#include "Drop_item.h"
#include"Customize_area.h"

Customize_UI_ver2::Customize_UI_ver2() {
	custom_player = FindGO<Player>("player");
	custom_player->game_state = 3;

	Setup();
	customize_area = NewGO<Customize_area>(1, "customize_area");
}

void Customize_UI_ver2::Setup() {
	custom_model_body.Init("Assets/modelData/test_player.tkm");
	custom_model_body.SetPosition(custom_model_body_position);
	custom_model_body_rotation.SetRotationDegY(-135.0f);
	custom_model_body.SetRotation(custom_model_body_rotation);
	custom_model_body.Update();
}

Customize_UI_ver2::~Customize_UI_ver2() {
	DeleteGO(customize_area);
	custom_player->game_state = 0;
}

void Customize_UI_ver2::Update() {
	Custom_model_body();
	if (g_pad[0]->IsTrigger(enButtonB)) {
		DeleteGO(this);
	}
}

void Customize_UI_ver2::Custom_model_body() {


	custom_model_body.SetRotation(custom_model_body_rotation);
	custom_model_body.Update();
}

void Customize_UI_ver2::Render(RenderContext& rc) {
	custom_model_body.Draw(rc);
}