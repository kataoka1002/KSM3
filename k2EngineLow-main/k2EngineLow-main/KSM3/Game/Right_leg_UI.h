#pragma once
class Right_leg_weapons;
class Player;

class Right_leg_UI :public IGameObject
{

	public:
	Right_leg_UI();
	~Right_leg_UI();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	SpriteRender r_l_w_hp_render[5];
	Right_leg_weapons* right_leg_weapons;
	Player* player;
};

