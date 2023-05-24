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
using namespace std;

class Result :public IGameObject
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
	void Back_set();
	void Font_set();
	void Rank();
	void Score_OFF();
	void Render(RenderContext& rc);

	int set = 0;					//装備した数
	int enemy_count = 0;		//敵を倒した数
	int set_score = 0;			//装備した数に応じたスコア
	int enemy_count_score = 0;	//敵を倒した数に応じたスコア
	int total_score = 0;		//トータルスコア
	int rank = 0;				//ランク
	int result_state = 0;			//スコア表示　0:ON 1:OFF
	int Neo_result_state = 0;   //リザルト画面の変化 0:タイムの表示 1:SCOREの表示 2:ランクの表示

	float draw_time = 0.0f;	//リザルト画面に遷移して表示するまでの時間
	float SE_volume = 0.0f;
	float BGM_volume = 0.0f;
	int fast_count = 1;

	bool m_isWaitFadeout = false;
	bool time_count = false;

	ModelRender Player_modelrender;			//プレイヤーのモデルレンダー
	Vector3 Player_position = { 10000.0f,0.0f,0.0f };
	Quaternion Player_rotation;

	ModelRender Box_render;
	Quaternion Box_Rotation;
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
	SoundSource* m_SE = nullptr;

	int p_custom_point[2][3] = { {0,0,0},{0,0,0} };	//[0][0]右腕,[0][1]肩,[0][2]左腕,[1][0]右足,[1][2]左足	

	SpriteRender time_Render;
	Vector4 Time_color = { 1.0f,1.0f,1.0f,0.0f };
	Vector3 Time_position = { -25.0f,0.0f,0.0f };

	//SpriteRender Time_Num[4][10];
	array<array <SpriteRender, 10>, 4>Time_Num;
	SpriteRender Time_colon;
	Vector3 Time_0_position = { -162.0f,-335.0f,0.0f };//分10の位
	Vector3 Time_1_position = { -75.0f,-335.0f,0.0f };//分1の位
	Vector3 Time_2_position = { 0.0f,-335.0f,0.0f };//:
	Vector3 Time_3_position = { 75.0f,-335.0f,0.0f };//秒10の位
	Vector3 Time_4_position = { 162.0f,-335.0f,0.0f };//秒1の位

	int minute = 0;
	int sec = 0;
	array<int, 4 >time_set;
	array<array < float, 2>,4>a;

	SpriteRender Score_Render;
	Vector4 Score_color = { 1.0f,1.0f,1.0f,0.0f };
	Vector3 Score_position = { -25.0f,0.0f,0.0f };

	//SpriteRender Score_Num[5][10];
	array<array <SpriteRender, 10>, 5>Score_Num;
	SpriteRender Score_comma;
	Vector3 Score_0_position = { -200.0f,-335.0f,0.0f };//10000の位
	Vector3 Score_1_position = { -105.0f,-335.0f,0.0f };//1000の位
	Vector3 Score_2_position = { -30.0f,-335.0f,0.0f };//,
	Vector3 Score_3_position = { 30.0f,-335.0f,0.0f };//100の位
	Vector3 Score_4_position = { 125.0f,-335.0f,0.0f };//10の位
	Vector3 Score_5_position = { 220.0f,-335.0f,0.0f };//1の位
	int SCORE=0;
	int Total = 0;
	int MAX_SCORE = 0;
	array<int, 5 >score_set;
	array<array < float, 2>, 5>b;

	SpriteRender Rank_sheet;
	Vector4 Rank_Sheet_color = { 1.0f,1.0f,1.0f,0.0f };
	Vector3 Rank_position = { 25.0f,0.0f,0.0f };

	//SpriteRender Rank_Render[4];
	array <SpriteRender, 4>Rank_Render;
	Vector4 Rank_color = { 1.0f,1.0f,1.0f,0.0f };
	Vector3 Rank_Scale = { 2.0f,2.0f,2.0f };
	int Rank_set = 0;

	SpriteRender Rank_Time_Render;
	Vector3 Rank_Time_position = { -25.0f, 0.0f,0.0f };
	Vector4 Rank_Time_color = { 1.0f,1.0f,1.0f,0.0f };

	SpriteRender Rank_Score_Render;
	Vector3 Rank_Score_position = { -225.0f, 0.0f,0.0f };
	Vector4 Rank_Score_color = { 1.0f,1.0f,1.0f,0.0f };
};