#pragma once
class Player;
class Right_arm_weapons;
class Right_leg_weapons;
class Left_arm_weapons;
class Left_leg_weapons;
class Shoulder_weapons;

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


	SpriteRender m_HPSprite;
	SpriteRender m_HPBackSprite;
	SpriteRender m_rightArmHPSprite;
	SpriteRender m_rightLegHPSprite;
	SpriteRender m_leftArmHPSprite;
	SpriteRender m_leftLegHPSprite;
	SpriteRender m_shoulderHPSprite;

	float m_sizeX = 1.0f;
	float UI_START_COLLAR_G = 1.0f;
	float UI_START_COLLAR_R = 0.0f;
};

