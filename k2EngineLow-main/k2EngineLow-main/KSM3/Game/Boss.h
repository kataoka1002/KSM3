#pragma once
#define HP 2000.0f

class Player;
class Battle_ship_attack;
class Drop_item;
class Boss_Riser;
class Boss_Shovel;
class Boss_Drill;
class Boss_Cannon;
class Boss_Turbo;
class Result;

class Boss :public IGameObject
{
public:
	Boss();
	~Boss();

	bool Start();
	void Update();//�X�V����
	void Render(RenderContext& rc);//�`�揈��
	void Move();//�ړ�����
	void Damage();
	void PlayerSearch();//���G

	Player* b_player = nullptr;
	Battle_ship_attack* b_battle_ship_attack;
	Drop_item* drop_item;
	Boss_Riser* b_boss_riser;
	Boss_Shovel* b_boss_shovel;
	Boss_Drill* b_boss_drill;
	Boss_Cannon* b_boss_cannon;
	Boss_Turbo* b_boss_turbo;
	Result* result;

	//std::vector<Boss_Riser*>m_riserObject;

	ModelRender boss_modelRender;//���f�������_�[
	Vector3 boss_position;//���W
	CharacterController boss_characterController;//�L�����N�^�[�R���g���[���[
	Quaternion boss_rotation;//�N�H�[�^�j�I��
	Vector3 boss_moveSpeed;//�ړ����x
	Vector3 boss_forward{ 0.0f,0.0f,-1.0f };//�G�l�~�[�̐��ʃx�N�g��
	Vector3 riser_pos;

	bool defeat_state = false;

	int boss_weapons = 1;
	int boss_game_state = 0;
	int attack_state = 0;		//�U�������ǂ������B0���U�������ᖳ���B

	float boss_HP = HP;
};

