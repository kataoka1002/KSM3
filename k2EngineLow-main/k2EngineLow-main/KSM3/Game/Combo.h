#pragma once
class Player;

class Combo : public IGameObject, Noncopyable
{
public:
	Combo();
	~Combo();
	bool Start();
	void Update();
	void ComboUpdate();
	void SpriteInit(const char* effectFilePath, int place);
	void Render(RenderContext& rc);

private:
	Player* m_player = nullptr;

	SpriteRender m_comboSprite;
    SpriteRender m_combo10Sprite;
    SpriteRender m_killSprite;

    Vector3 m_numScale = Vector3::Zero;             //�R���{���̑傫��

	int m_combo = 0;                        //�R���{��
    int m_comboResetCount = 0;              
};

