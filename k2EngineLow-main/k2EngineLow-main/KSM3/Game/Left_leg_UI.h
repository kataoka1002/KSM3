#pragma once
class Left_leg_weapons;
class Player;

class Left_leg_UI:public IGameObject
{
	public:
	Left_leg_UI();
	~Left_leg_UI();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	SpriteRender l_l_w_hp_render[5];
	Left_leg_weapons* left_leg_weapons;
	Player* player;
};

