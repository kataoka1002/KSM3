#pragma once
class Enemy;
class Player;
class Boss;
class Customize_UI_ver2;
class Core_weapons;
class Fade;
class Drop_item;

class Result:public IGameObject
{
public:
	Result();
	~Result();
	bool Start();
	void Update();
	void Enemy_count();
	void Set_count();
	void Font();
	void Rank();
	void Render(RenderContext& rc);

	int set=0;					//装備した数
	int enemy_count = 0;		//敵を倒した数
	int set_score = 0;			//装備した数に応じたスコア
	int enemy_count_score = 0;	//敵を倒した数に応じたスコア
	int total_score = 0;		//トータルスコア
	int rank = 0;				//ランク

	float draw_time = 0.0f;	//リザルト画面に遷移して表示するまでの時間

	bool m_isWaitFadeout = false;
	bool time_count = false;

	SpriteRender result_SpriteRender;		//リザルトのスプライトレンダー
	SpriteRender Mozi_render[6];			//文字のスプライトレンダー
	SpriteRender Weapon_set_render[6];		//武器をセットした数
	SpriteRender Boss_time_render;			//ボスの倒した時間
	SpriteRender Enemy_count_render[31];	//敵を倒した数
	SpriteRender rank_render[5];			//ランク

	FontRender font_render[5];				//フォント
	FontRender Boss_time_font;				//ボス戦の経過時間
	FontRender Score_font;					//トータルスコア
	FontRender Time_font;					//時間

	Enemy* enemy;
	Player* player;
	Boss* boss;
	Customize_UI_ver2* customize_UI_ver2;
	Fade* m_fade = nullptr;
	Core_weapons* core_weapons;
	Drop_item* drop_item;
};

