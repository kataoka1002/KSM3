#pragma once
class Right_arm_weapons;
class Player;

class Right_arm_UI:public IGameObject
{
	public:
	Right_arm_UI();
	~Right_arm_UI();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	SpriteRender r_a_w_hp_render[5];
	Right_arm_weapons* right_arm_weapons;
	Player* player;
};

