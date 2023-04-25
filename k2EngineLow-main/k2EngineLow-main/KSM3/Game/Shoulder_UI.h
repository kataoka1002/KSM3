#pragma once
class Shoulder_weapons;
class Player;

class Shoulder_UI :public IGameObject
{
	public:
	Shoulder_UI();
	~Shoulder_UI();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	SpriteRender s_w_hp_render[5];
	Shoulder_weapons* shoulder_weapons;
	Player* player;
};