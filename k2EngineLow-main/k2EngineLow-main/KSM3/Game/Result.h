#pragma once
class Enemy;
class Player;
class Boss;
class Customize_UI_ver2;
class Core_weapons;
class Fade;
class Drop_item;

class Result:public IGameObject
{
public:
	Result();
	~Result();
	bool Start();
	void Update();
	void Enemy_count();
	void Set_count();
	void Font();
	void Rank();
	void Render(RenderContext& rc);

	int set=0;					//����������
	int enemy_count = 0;		//�G��|������
	int set_score = 0;			//�����������ɉ������X�R�A
	int enemy_count_score = 0;	//�G��|�������ɉ������X�R�A
	int total_score = 0;		//�g�[�^���X�R�A
	int rank = 0;				//�����N

	float draw_time = 0.0f;	//���U���g��ʂɑJ�ڂ��ĕ\������܂ł̎���

	bool m_isWaitFadeout = false;
	bool time_count = false;

	SpriteRender result_SpriteRender;		//���U���g�̃X�v���C�g�����_�[
	SpriteRender Mozi_render[6];			//�����̃X�v���C�g�����_�[
	SpriteRender Weapon_set_render[6];		//������Z�b�g������
	SpriteRender Boss_time_render;			//�{�X�̓|��������
	SpriteRender Enemy_count_render[31];	//�G��|������
	SpriteRender rank_render[5];			//�����N

	FontRender font_render[5];				//�t�H���g
	FontRender Boss_time_font;				//�{�X��̌o�ߎ���
	FontRender Score_font;					//�g�[�^���X�R�A
	FontRender Time_font;					//����

	Enemy* enemy;
	Player* player;
	Boss* boss;
	Customize_UI_ver2* customize_UI_ver2;
	Fade* m_fade = nullptr;
	Core_weapons* core_weapons;
	Drop_item* drop_item;
};

