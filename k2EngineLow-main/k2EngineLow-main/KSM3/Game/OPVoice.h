#pragma once
class Game;

class OPVoice : public IGameObject
{
public:
	OPVoice();
	~OPVoice();
	bool Start();
	void Update();
	void ChangeSprite();
	void Render(RenderContext& rc);

	SpriteRender m_voiceSprite;
	SpriteRender m_voiceFrameSprite;

	SoundSource* m_voiceSE = nullptr;
	SoundSource* m_putunSE = nullptr;
	Game* m_game = nullptr;

	float m_frameScaleY = 0.0f;		//スプライトのY方向の大きさ
	int m_spriteChangeCount = 0;	//スプライトが切り替わる(波戦の本数が変わる)間隔のカウント
	int m_voiceSpriteState = 0;		//波戦の本数とステートの数が同じ
	bool m_scaleDown = false;		//スプライトを小さくするかどうか
};

