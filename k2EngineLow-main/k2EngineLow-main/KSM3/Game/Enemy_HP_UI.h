#pragma once
class Enemy_Near;
class Enemy;
class Enemy_Far;
class Player;
class Game;
class GameCamera;

class Enemy_HP_UI : public IGameObject
{
public:
	Enemy_HP_UI();
	~Enemy_HP_UI();
	bool Start();
	void Update();
	void CalcPosition();
	void CalcScale();
	Vector3 SendHPBer(Vector3 size, Vector3 scale);	//�摜�̈ړ��ʂ����߂�
	void Render(RenderContext& rc);
	template <class T>

	/// <summary>
	/// ��苗���ȓ�&�J�����̎���ɓ����Ă���Ȃ�̗͕\��
	/// </summary>
	/// <param name="enemy">�G�l�~�[�̃N���X</param>
	/// <returns>true : �`�悷��Afalse : �`�悵�Ȃ�</returns>
	bool CalcAngle(T enemy);

	/// <summary>
	/// �ߋ����G�l�~�[���Z�b�g
	/// </summary>
	/// <param name="pointa">�|�C���^</param>
	void SetEnemyNear(Enemy_Near* pointa)
	{
		m_enemyNear = pointa;
	}

	/// <summary>
	/// �G�l�~�[���Z�b�g
	/// </summary>
	/// <param name="pointa">�|�C���^</param>
	void SetEnemy(Enemy* pointa)
	{
		m_enemy = pointa;
	}

	/// <summary>
	/// �������G�l�~�[���Z�b�g
	/// </summary>
	/// <param name="pointa">�|�C���^</param>
	void SetEnemyFar(Enemy_Far* pointa)
	{
		m_enemyFar = pointa;
	}

private:
	Enemy_Near* m_enemyNear = nullptr;
	Enemy* m_enemy = nullptr;
	Enemy_Far* m_enemyFar = nullptr;
	Player* m_player = nullptr;
	Game* m_game = nullptr;
	GameCamera* m_camera = nullptr;

	SpriteRender m_HPSprite;
	SpriteRender m_HPFrameSprite;

	Vector2 m_position = Vector2::Zero;
	Vector3 m_scale = {1.0f,1.0f,0.0f};
};

