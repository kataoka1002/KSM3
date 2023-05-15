#pragma once

class Left_arm_weapons;
class Customize_UI_ver2;
class Result;
class Game;

class Player:public IGameObject
{
public:
	Player();
	~Player();
	bool Start();
	void Update();									//更新処理
	void Render(RenderContext& rc);					//描画処理
	void Move();									//移動処理
	void RunSE();									//ステート管理
	void pause();									//ポーズ画面
	void MakeEfe();									//エフェクト再生
	void MachineGunSE();

	SoundSource* m_machineGunSE = nullptr;			//マシンガンSE
	SoundSource* m_runSE = nullptr;					//足音SE
	SoundSource* m_walkSE = nullptr;				//足音SE
	SoundSource* m_kettei = nullptr;
	ModelRender player_modelRender;					//モデルレンダー
	Vector3 player_position;						//座標
	CharacterController characterController;		//キャラクターコントローラー
	Quaternion player_rotation;						//クォータニオン
	Vector3 player_moveSpeed;						//移動速度

	float fsin[360], fcos[360];
	Vector3 playerFowrad = { 0.0f, 0.0f, 1.0f };	//プレイヤーの正面ベクトル


	int game_state=0;								//ゲームがどの状態化の管理(0メインゲーム,1ポーズ画面,2空欄,3カスタマイズ)

	Result* m_result = nullptr;
	Left_arm_weapons* p_left_arm_weapons = nullptr;
	Customize_UI_ver2* p_customize_ui_ver2 = nullptr;
	Game* m_game = nullptr;


	int game_end_state = 0;							//ゲームの終了判定

	SpriteRender pouse_spriteRender;	//pause画面用のスプライトレンダー

	//エフェクト関係
	EffectEmitter* sunabokoriEffect = nullptr;
	int effectCount = 0;

	int killEnemy = 0;	//敵を殺した数(10になるとウェーブが進む)
						
	
						
						
	int p_custom_point[2][3] = { {0,0,0},{0,0,0} };		//[0][0]右腕,[0][1]肩,[0][2]左腕,[1][0]右足,[1][2]左足
					
	
	
	bool m_cameraMove = false;	//カメラ切り替え中かどうか

	float accelerator = 0;
	float brake = 0;
	float throttle = 0;
	bool attack_state_la = false;
	bool attack_state_ll = false;
	bool attack_state_rl = false;
	bool attack_state_ra = false;
	bool attack_state_s = false;
	float move_s;

	float m_playerHP = 500.0f;		//プレイヤーのHP
	float m_playerHPMax = 500.0f;		//プレイヤーのHPの最大値

	bool enemy_survival = true;
	bool boss_survival = true;
};

