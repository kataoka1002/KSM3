#include "stdafx.h"
#include "Battleship_gun.h"
#include "Player.h"

Battleship_gun::Battleship_gun() {
	Battleship_gun_Render.Init("Assets/modelData/battleship_gun_left_arm.tkm");
	B_G_characterController.Init(10.0f, 150.0f, B_G_position);
}

Battleship_gun::~Battleship_gun() {

}

void Battleship_gun::Update() {
	if(game_state==0)
	Move();
}

void Battleship_gun::Move() {
	Battleship_gun_Render.SetPosition(B_G_position);
	Battleship_gun_Render.SetRotation(B_G_rotation);
}

void Battleship_gun::Render(RenderContext& rc) {
	Battleship_gun_Render.Draw(rc);
}
