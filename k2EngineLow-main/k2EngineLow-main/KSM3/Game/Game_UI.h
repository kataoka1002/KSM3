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

	
	SpriteRender player_hp_render[5];	//HP�Q�[�W
	SpriteRender Time_render[1];			//����
	SpriteRender Enemy_count_render[1];				//�G��|������
	SpriteRender boss_hp_render[5];		//�{�XHP�Q�[�W
	SpriteRender player_core_render[5];	//�R�A
	FontRender   m_fontRender;

	float m_time;

    Enemy*enemy;
	Player* u_player;
	Core_weapons* core_weapons;
	Game* game;
};

