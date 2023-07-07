#pragma once

class Player;
class Boss;
class Game;

class Boss_Saber : public IGameObject
{
public:
	Boss_Saber();
	~Boss_Saber();
	bool Start();
	void Setup();
	void Update();
	void Move();
	void Render(RenderContext& rc);

	Vector3 GetPosirion()
	{
		return m_position;
	}

	Quaternion GetRotation()
	{
		return m_rotation;
	}

	void ApplyDamage(float damage)
	{
		m_HP -= damage;
	}

	/// <summary>
	/// セイバーの大きさ減少
	/// </summary>
	/// <param name="amount">減少量</param>
	void DecreaseScale(float amount)
	{
		m_scale -= amount;
	}

	/// <summary>
	/// セイバーの大きさを設定
	/// </summary>
	void SetSaberScale()
	{
		m_saberModel.SetScale(m_scale);
	}


private:
	Player* m_player = nullptr;
	Boss* m_boss = nullptr;
	Game* m_game = nullptr;

	ModelRender m_saberModel;
	CharacterController m_enemyCharacterController;	//エネミーキャラコン
	Quaternion m_rotation;
	Vector3 m_position = Vector3::Zero;
	Vector3 m_forward = { 0.0f,0.0f,1.0f };
	Vector3 m_localPosition = { 00.0f,00.0f,-1450.0f };
	float m_HP = 500.0f;
	float m_scale = 15.0f;
};

