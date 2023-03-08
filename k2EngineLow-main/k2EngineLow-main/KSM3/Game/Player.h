#pragma once
class Player:public IGameObject
{
public:
	Player();
	~Player();
	void Update();    //更新処理
	void Render(RenderContext& rc);  //描画処理
	void Move();   //移動処理
	void Rotation();  //回転処理
	void ManageState();  //ステート管理
	void pause();//ポーズ画面

	ModelRender player_modelRender;  //モデルレンダー
	Vector3 player_position;  //座標
	CharacterController characterController;  //キャラクターコントローラー
	Quaternion player_rotation;  //クォータニオン
	Quaternion move_rotation;
	Vector3 player_moveSpeed;   //移動速度

	float fsin[360], fcos[360];
	Vector3 playerFowrad = { 0.0f, 0.0f, 1.0f };//プレイヤーの正面ベクトル

	int game_state=0;//ゲームがどの状態化の管理

	SpriteRender pouse_spriteRender;//pause画面用のスプライトレンダー

	int game_end_state = 0;//ゲームの終了判定

};

