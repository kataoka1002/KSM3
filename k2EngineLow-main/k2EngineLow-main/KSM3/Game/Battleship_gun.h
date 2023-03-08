#pragma once

class Player;


class Battleship_gun:public IGameObject
{
public:
	Battleship_gun();
	~Battleship_gun();
	void Update();
	void Render(RenderContext& rc);
	void Move();

	Player* player;

	Vector3 B_G_position;
	CharacterController B_G_characterController;
	Quaternion B_G_rotation;
	Vector3 B_G_moveSpeed;

	Vector3 B_G_Fowrad = { 0.0f, 0.0f, 1.0f };//íŠÍ–C‚Ì³–ÊƒxƒNƒgƒ‹
	float fsin[360], fcos[360];
	int game_state=0;

	ModelRender Battleship_gun_Render;
};

