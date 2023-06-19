#include "stdafx.h"
#include "Customize_area.h"
#include "Player.h"

Customize_area::Customize_area() {
	c_area_player = FindGO<Player>("player");

	//ƒƒ‚ƒŠ‚ÌŠm•Û
	customize_area_render = std::make_unique<ModelRender>();
	customize_area_render->Init("Assets/modelData/Customize_area.tkm",false);
	customize_area_render->SetPosition(C_area_position);
	customize_area_render->SetScale(c_area_scale);
	customize_area_render->Update();
}

Customize_area::~Customize_area() {

}

void Customize_area::Render(RenderContext& rc) {
	if (c_area_player->GetGameState() == 3) {
		customize_area_render->Draw(rc);
	}
}