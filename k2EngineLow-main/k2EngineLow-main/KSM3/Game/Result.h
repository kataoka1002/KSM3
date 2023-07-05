#pragma once
class Player;
class GameCamera;
using namespace std;

class Result :public IGameObject
{
public:
	Result();
	~Result();
	bool Start();
	void Update();
	void BackGround();
	void EnemyCount();
	void BackSet();
	void FontSet();
	void Render(RenderContext& rc);

	/// <summary>
	/// ���ʂ̃Z�b�g
	/// </summary>
	/// <param name="bgm">BGM�̉���</param>
	/// <param name="se">SE�̉���</param>
	void SetVolume(float bgm, float se)
	{
		m_BGMVolume = bgm;
		m_SEVolume = se;
	}

	/// <summary>
	/// �^�C�����Z�b�g
	/// </summary>
	/// <param name="min">��</param>
	/// <param name="sec">�b</param>
	void SetTime(float min, float sec)
	{
		m_minute = min;
		m_seconds = sec;
	}

private:
	Player* m_player = nullptr;
	GameCamera* m_gameCamera = nullptr;
	SoundSource* m_sound = nullptr;

	ModelRender m_playerModel;
	ModelRender m_boxModel;
	ModelRender m_coreModel;
	ModelRender m_shoulderModel;
	ModelRender m_rightArmModel;
	ModelRender m_rightLeg;
	ModelRender m_leftArm;
	ModelRender m_leftLeg;
	SpriteRender m_timeSprite;
	SpriteRender m_timeColonSprite;
	SpriteRender m_scoreSprite;
	SpriteRender m_scoreCommaSprite;
	SpriteRender m_rankSheetSprite;
	SpriteRender m_rankTimeSprite;
	SpriteRender m_rankScoreSprite;

	Vector3 m_playerPosition = { 10000.0f,0.0f,0.0f };
	Vector3 m_boxPosition = { 10000.0f,0.0f,0.0f };
	Vector3 m_boxScale = { 3.0f,3.0f,3.0f };
	Vector3 m_coreLocalPos;
	Vector3 m_shoulderLocalPos;
	Vector3 m_rightArmLocalPos;
	Vector3 m_rightLegLocalPos;
	Vector3 m_leftArmLocalPos;
	Vector3 m_leftLegLocalPos;
	Vector3 m_machinegunScale = { 2.0f, 2.0f, 2.0f };
	Vector3 m_battleshipgunScale = { 2.0f, 2.0f, 2.0f };//2�{��scale
	Vector3 m_timePosition = { -25.0f,0.0f,0.0f };
	Vector3 m_timePosition0 = { -162.0f,-335.0f,0.0f };//��10�̈�
	Vector3 m_timePosition1 = { -75.0f,-335.0f,0.0f };//��1�̈�
	Vector3 m_timePosition2 = { 0.0f,-335.0f,0.0f };//:
	Vector3 m_timePosition3 = { 75.0f,-335.0f,0.0f };//�b10�̈�
	Vector3 m_timePosition4 = { 162.0f,-335.0f,0.0f };//�b1�̈�
	Vector3 m_scorePosition = { -25.0f,0.0f,0.0f };
	Vector3 m_scorePosition0 = { -200.0f,-335.0f,0.0f };//10000�̈�
	Vector3 m_scorePosition1 = { -105.0f,-335.0f,0.0f };//1000�̈�
	Vector3 m_scorePosition2 = { -30.0f,-335.0f,0.0f };//,
	Vector3 m_scorePosition3 = { 30.0f,-335.0f,0.0f };//100�̈�
	Vector3 m_scorePosition4 = { 125.0f,-335.0f,0.0f };//10�̈�
	Vector3 m_scorePosition5 = { 220.0f,-335.0f,0.0f };//1�̈�
	Vector3 m_rankPosition = { 25.0f,0.0f,0.0f };
	Vector3 m_rankScale = { 2.0f,2.0f,2.0f };
	Vector3 m_rankTimePosition = { -25.0f, 0.0f,0.0f };
	Vector3 m_rankScorePosition = { -225.0f, 0.0f,0.0f };
	Vector4 m_timeColor = { 1.0f,1.0f,1.0f,0.0f };
	Vector4 m_scoreColor = { 1.0f,1.0f,1.0f,0.0f };
	Vector4 m_rankSheetColor = { 1.0f,1.0f,1.0f,0.0f };
	Vector4 m_rankColor = { 1.0f,1.0f,1.0f,0.0f };
	Vector4 m_rankTimeColor = { 1.0f,1.0f,1.0f,0.0f };
	Vector4 m_rankScoreColor = { 1.0f,1.0f,1.0f,0.0f };
	Quaternion m_playerRotation;
	Quaternion m_boxRotation;
	Quaternion m_customModelRotation;

	array<array <SpriteRender, 10>, 4> m_timeNum;
	array<int, 4 > m_timeSet;
	array<array < float, 2>,4> m_timeColonSpriteAlpha;
	array<array <SpriteRender, 10>, 5> m_scoreNum;
	array<int, 5 > m_scoreSet;
	array<array < float, 2>, 5> m_scoreCommaSpriteAlpha;
	array <SpriteRender, 4> m_rankSprite;

	int m_resultState = 0;   //���U���g��ʂ̕ω� 0:�^�C���̕\�� 1:SCORE�̕\�� 2:�����N�̕\��
	int m_count = 1;
	int m_customPoint[2][3] = { {0,0,0},{0,0,0} };	//[0][0]�E�r,[0][1]��,[0][2]���r,[1][0]�E��,[1][2]����	
	int m_minute = 0;
	int m_seconds = 0;
	int m_score = 0;
	int m_total = 0;
	int m_maxScore = 0;
	int m_rankSet = 0;
	float m_SEVolume = 0.0f;
	float m_BGMVolume = 0.0f;

};