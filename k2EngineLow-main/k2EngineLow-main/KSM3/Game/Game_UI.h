#pragma once
class Core_weapons;
class Enemy;
class Player;
class Game;

class Game_UI :public IGameObject
{
public:
	Game_UI();
	~Game_UI();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	
	SpriteRender player_hp_render[5];	//HPゲージ
	SpriteRender Time_render[1];			//時間
	SpriteRender Enemy_count_render[1];				//敵を倒した数
	SpriteRender boss_hp_render[5];		//ボスHPゲージ
	SpriteRender player_core_render[5];	//コア
	FontRender   m_fontRender;

	float m_time;

    Enemy*enemy;
	Player* u_player;
	Core_weapons* core_weapons;
	Game* game;
};

