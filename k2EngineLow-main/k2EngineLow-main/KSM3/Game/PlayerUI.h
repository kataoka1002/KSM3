#pragma once
class Player;
class Right_arm_weapons;
class Right_leg_weapons;
class Left_arm_weapons;
class Left_leg_weapons;
class Shoulder_weapons;
class Wave;

class PlayerUI:public IGameObject
{
public:
	PlayerUI();
	~PlayerUI();
	bool Start();
	void Update();
	Vector4 Damage(float nowHP,float maxHP);
	void WeaponUISetUp(int num);
	void Render(RenderContext& rc);

	Player* m_player = nullptr;
	Right_arm_weapons* m_rightArm = nullptr;
	Right_leg_weapons* m_rightLeg = nullptr;
	Left_arm_weapons* m_leftArm = nullptr;
	Left_leg_weapons* m_leftLeg = nullptr;
	Shoulder_weapons* m_shoulder = nullptr;
	Wave* m_wave = nullptr;

	SpriteRender m_redFrameSprite;
	SpriteRender m_HPSprite;
	SpriteRender m_HPBackSprite;
	SpriteRender m_rightArmHPSprite;
	SpriteRender m_rightLegHPSprite;
	SpriteRender m_leftArmHPSprite;
	SpriteRender m_leftLegHPSprite;
	SpriteRender m_shoulderHPSprite;
	SpriteRender m_enemyKillSprite;
	SpriteRender m_L1Sprite;
	SpriteRender m_R2Sprite;
	

	FontRender m_killEnemyAmount;

	float m_sizeX = 1.0f;
	float UI_START_COLLAR_G = 1.0f;
	float UI_START_COLLAR_R = 0.0f;
	float m_redFrame_A = 0.0f;
	float m_killSpritePosX = 1000.0f;		//キル数の枠のポジション
	float m_HPSpriteX = 1000.0f;			//HPのポジション
	float m_HPwakuSpriteX = 1000.0f;		//HPの枠のポジション
	float m_killSpriteTargetPos = 600.0f;	//キル数の枠のターゲットポジション
	float m_HPSpriteTargetPos = 610.0f;		//HPのターゲットポジション
	float m_HPwakuSpriteTargetPos = 730.0f;	//HPの枠のターゲットポジション
	float m_L1SpritePosX = -1100.0f;
	float m_L1SpriteTargetPos = -650.0f;
	float m_R2SpritePosX = -1100.0f;
	float m_R2SpriteTargetPos = -470.0f;
	float m_killFontPos = 1000.0f;
	float m_killFontTargetPos = 580.0f;
	bool m_setUI = false;					//UIが全てセットできたか
	bool setA = false;
	bool setB = false;
	bool setC = false;
	bool setD = false;
	bool setE = false;
	bool setF = false;
};

