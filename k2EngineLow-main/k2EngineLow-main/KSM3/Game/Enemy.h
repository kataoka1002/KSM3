#pragma once
class Player;
class Battle_ship_attack;
class Drop_item;

class Enemy:public IGameObject
{
public:
	Enemy();
	~Enemy();

	bool Start();
	void Update();//�X�V����
	void Render(RenderContext& rc);//�`�揈��
	void Move();//�ړ�����
	void PlayerSearch();//���G

	Player* e_player = nullptr;
	Battle_ship_attack* e_battle_ship_attack;
	Drop_item* drop_item;

	ModelRender enemy_modelRender;//���f�������_�[
	Vector3 enemy_position;//���W
	CharacterController enemy_characterController;//�L�����N�^�[�R���g���[���[
	Quaternion enemy_rotation;//�N�H�[�^�j�I��
	Vector3 enemy_moveSpeed;//�ړ����x
	Vector3 enemy_forward{ 0.0f,0.0f,-1.0f };//�G�l�~�[�̐��ʃx�N�g��

	int enemy_game_state=0;
};

