#pragma once

class Left_arm_weapons;

class Customize_UI_ver2;



class Player:public IGameObject
{
public:
	Player();
	~Player();
	void Update();									//更新処理
	void Render(RenderContext& rc);					//描画処理
	void Move();									//移動処理
	void ManageState();								//ステート管理
	void pause();									//ポーズ画面
	void MakeEfe();									//エフェクト再生
	


	ModelRender player_modelRender;					//モデルレンダー
	Vector3 player_position;						//座標
	CharacterController characterController;		//キャラクターコントローラー
	Quaternion player_rotation;						//クォータニオン
	Vector3 player_moveSpeed;						//移動速度

	float fsin[360], fcos[360];
	Vector3 playerFowrad = { 0.0f, 0.0f, 1.0f };	//プレイヤーの正面ベクトル


	int game_state=0;								//ゲームがどの状態化の管理(0メインゲーム,1ポーズ画面,2空欄,3カスタマイズ)


	Left_arm_weapons* p_left_arm_weapons = nullptr;
	Customize_UI_ver2* p_customize_ui_ver2;
	
	
	SpriteRender pouse_spriteRender;				//pause画面用のスプライトレンダー

	int game_end_state = 0;							//ゲームの終了判定

	//エフェクト関係
	EffectEmitter* sunabokoriEffect = nullptr;
	int effectCount = 0;

		
	int p_custom_point[2][3] = { {0,0,0},{0,0,0} }; //[0][0]右腕,[0][1]肩,[0][2]左腕,[1][0]右足,[1][2]左足
	 

	float accelerator = 0;
	float brake = 0;
	bool attack_state_la = false;
	bool attack_state_ll = false;
	bool attack_state_rl = false;
	bool attack_state_ra = false;
	bool attack_state_s = false;
	float move_s;

	


	bool enemy_survival = true;
	bool boss_survival = true;
};

