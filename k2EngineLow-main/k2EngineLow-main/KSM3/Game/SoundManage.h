#pragma once
class Game;
class Player;

class SoundManage : public IGameObject, Noncopyable
{
public:
	SoundManage();
	~SoundManage();
	bool Start();
	void Update();
	void SetUp();

private:
	Game* m_game = nullptr;
	Player* m_player = nullptr;
	SoundSource* m_gameBGM = nullptr;			//ゲームBGM
	SoundSource* m_customizeBGM = nullptr;		//カスタマイズ画面BGM
	SoundSource* m_bossBGM = nullptr;			//ボスBGM

};

