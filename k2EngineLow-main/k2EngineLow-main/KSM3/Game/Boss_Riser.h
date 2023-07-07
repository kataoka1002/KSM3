#pragma once
#define HP 500

class Player;
class Boss;
class Boss_Riser_attack;
class Drop_item;
class Game;

class Boss_Riser :public IGameObject
{
public:
	Boss_Riser();
	~Boss_Riser();

	void Setup();
	void Update();
	void Move();
	void PlayerSearch();
	void Render(RenderContext& rc);

	enum EnAnimation {
		enAnimationClip_Idle,
		enAnimationClip_attack,
		enAnimationClip_Num
	};

	AnimationClip m_animationClip[enAnimationClip_Num];
	EffectEmitter* m_weaponEffect = nullptr;
	Player* m_player;
	Boss* m_boss;
	Boss_Riser_attack* b_boss_weapons;
	Drop_item* m_dropItem;
	Game* m_game;

	//CharacterController boss_riser_characterContller;
	Quaternion m_rotation;
	Vector3 m_position;
	Vector3 iranyatu;
	Vector3 m_forward = { 0.0f,0.0f,1.0f };
	int iran = 0;
	ModelRender boss_Riser_Render;
	SoundSource* m_Dozar_ChargeSE = nullptr;

	//Ç¢ÇÈÅBê‚ëŒÅB
	Vector3 m_localPosition = { 600.0f,300.0f,-100.0f };
	Vector3 m_effectLocalPos = { 0.0f,200.0f,-200.0f };
	bool m_attackState = false;
	bool m_attackOK = false;
	bool notHituyou = false;
	int m_setWeapon = 0;

	int iraniran = 0;
	int m_fastFlag = 0;

	int attack_count = 0;
	float riser_HP=HP;
	float scale = 12.0f;
};