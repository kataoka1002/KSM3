#pragma once
class Left_arm_weapons;
class Player;

class Left_arm_UI :public IGameObject
{
public:
	Left_arm_UI();
	~Left_arm_UI();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	SpriteRender l_a_w_hp_render[5];

	Left_arm_weapons* left_arm_weapons;
	Player* player;
};

