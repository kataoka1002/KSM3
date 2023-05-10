#pragma once
class Enemy;
class Player;
class Boss;
class Customize_UI_ver2;
class Core_weapons;
class Shoulder_weapons;
class Right_arm_weapons;
class Right_leg_weapons;
class Left_arm_weapons;
class Left_leg_weapons;
class Fade;
class Drop_item;
class GameCamera;


class Result:public IGameObject
{
public:
	Result();
	~Result();
	bool Start();
	void Update();
	void BackGround();
	void Enemy_count();
	void Set_count();
	void Font();
	void Rank();
	void Score_OFF();
	void Render(RenderContext& rc);

	int set=0;					//装備した数
	int enemy_count = 0;		//敵を倒した数
	int set_score = 0;			//装備した数に応じたスコア
	int enemy_count_score = 0;	//敵を倒した数に応じたスコア
	int total_score = 0;		//トータルスコア
	int rank = 0;				//ランク
	int result_state=0;			//スコア表示　0:ON 1:OFF

	float draw_time = 0.0f;	//リザルト画面に遷移して表示するまでの時間

	bool m_isWaitFadeout = false;
	bool time_count = false;

	ModelRender Player_modelrender;			//プレイヤーのモデルレンダー
	Vector3 Player_position = { 10000.0f,0.0f,0.0f };
	Quaternion Player_rotation;

	ModelRender Box_render;
	Vector3 Box_position = { 10000.0f,0.0f,0.0f };
	Vector3 Box_scale = { 3.0f,3.0f,3.0f };

	ModelRender custom_model_Core;
	Quaternion custom_model_body_rotation;
	Vector3 cw_lp;

	ModelRender custom_model_shoulder;
	Vector3 sw_lp;

	ModelRender custom_model_Right_arm;
	Vector3 raw_lp;

	ModelRender custom_model_Right_leg;
	Vector3 rlw_lp;

	ModelRender custom_model_Left_arm;
	Vector3 law_lp;

	ModelRender custom_model_Left_leg;
	Vector3 llw_lp;

	Vector3 scale2 = { 2.0f, 2.0f, 2.0f };//2倍のscale


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
	Shoulder_weapons* shoulder_weapons;
	Right_arm_weapons* right_arm_weapons;
	Right_leg_weapons* right_leg_weapons;
	Left_arm_weapons* left_arm_weapons;
	Left_leg_weapons* left_leg_weapons;
	Drop_item* drop_item;
	GameCamera* gamecamera;
};

