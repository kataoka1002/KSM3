#pragma once
class Player;
class Customize_UI;
class Customize_UI_ver2;
class Left_arm_weapons;
class GameCamera;
class Game;

class Drop_item : public IGameObject
{
public:
	Drop_item();
	~Drop_item();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void Float();
	void InitDropItem();
	void CalcModelScale();
	void ExecuteGetItem();
	void ExecuteDelete();

	/// <summary>
	/// ���W�̐ݒ�
	/// </summary>
	/// <param name="pos">�|�W�V����</param>
	void SetPosition(Vector3 pos)
	{
		m_position = pos;
	}

	/// <summary>
	/// ���W�̑�������
	/// </summary>
	/// <param name="pos">������</param>
	void AddPosition(Vector3 pos)
	{
		m_position += pos;
	}
	void AddPositionX(float pos)
	{
		m_position.x += pos;
	}
	void AddPositionY(float pos)
	{
		m_position.y += pos;
	}
	void AddPositionZ(float pos)
	{
		m_position.z += pos;
	}

	/// <summary>
	/// �A�C�e���̎�ނ�������
	/// </summary>
	/// <param name="kinds">�A�C�e���̎��</param>
	void SetItemKinds(int kinds)
	{
		m_dropKinds = kinds;
	}

private:
	std::unique_ptr<ModelRender> m_dropItemModel;	//�X�}�[�g�|�C���^

	Game* m_game = nullptr;
	Player* m_player = nullptr;
	GameCamera* m_gameCamera = nullptr;
	Customize_UI_ver2* m_customizeUI = nullptr;

	Vector3 m_position = Vector3::Zero;
	Quaternion m_rotation;

	int m_floatCount = 0;
	int m_deleteCount = 1800;	//�A�C�e����������܂ł̎���
	int m_dropKinds = 0;
	float m_floatLevel = 0.25;
	float m_modelSize = 0.01f;
};

