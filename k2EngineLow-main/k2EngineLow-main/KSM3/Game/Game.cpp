#include "stdafx.h"
#include "Game.h"
#include "BoxMove.h"

bool Game::Start()
{
	m_spriteRender.Init("Assets/modelData/utc_nomal.DDS", 100.0f, 100.0f);
	m_spriteRender.SetPosition({ -600.0f,300.0f,0.0f });

	animationClips[enAnimClip_Idle].Load("Assets/animData/idle.tka");
	animationClips[enAnimClip_Idle].SetLoopFlag(true);

	m_modelRender.Init("Assets/modelData/unityChan.tkm", animationClips, enAnimClip_Num, enModelUpAxisY);

	m_modelRender.SetPosition(0.0f, 0.0f, 0.0f);

	m_levelRender.Init("Assets/level/sample.tkl",
		[&](LevelObjectData2& objData)
		{
			//���O��Box_Move��������B
			if (objData.EqualObjectName(L"Box_Move") == true) {

				auto box = NewGO<BoxMove>(0);
				//�z�u���W�A�X�P�[���A��]���擾����B
				box->m_position = objData.position;
				box->m_scale = objData.scale;
				box->m_rotation = objData.rotation;
				//��ō폜���邽�߂ɁA�{�b�N�X���v�b�V�����Ă����B
				m_boxmoves.push_back(box);

				//true�ɂ���ƁA���x���̕��Ń��f�����ǂݍ��܂�Ȃ��B
				return true;
			}
		});

	Quaternion rot;
	rot.SetRotationDegY(180.0f);
	m_modelRender.SetRotation(rot);
	m_modelRender.SetScale(1.0f);
	m_modelRender.Update();


	//���C�g�͎΂ߏォ�瓖�����Ă���
	directionLight.ligDirection.x = 1.0f;
	directionLight.ligDirection.y = -1.0f;
	directionLight.ligDirection.z = -1.0f;
	//���K��
	directionLight.ligDirection.Normalize();
	//�F�͔�
	directionLight.ligColor.x = 1.0f;
	directionLight.ligColor.y = 1.0f;
	directionLight.ligColor.z = 1.0f;

	return true;
}

Game::Game()
{
	
}

Game::~Game()
{
	//�v�b�V�������{�b�N�X���폜���Ă����B
	for (auto box : m_boxmoves)
	{
		DeleteGO(box);
	}
}

void Game::Update()
{
	wchar_t wcsbuf[256];
	swprintf_s(wcsbuf, 256, L"%d�b�o��!!", int(m_timer));
	//�\������e�L�X�g��ݒ�B
	m_fontRender.SetText(wcsbuf);
	//�t�H���g�̈ʒu��ݒ�B
	m_fontRender.SetPosition(Vector3(-800.0f, 0.0f, 0.0f));
	//�t�H���g�̑傫����ݒ�B
	m_fontRender.SetScale(2.0f);
	//�t�H���g�̐F��ݒ�B
	m_fontRender.SetColor({ 1.0f,0.0f,0.0f,1.0f });
	m_timer += g_gameTime->GetFrameDeltaTime();

	m_modelRender.PlayAnimation(enAnimClip_Idle);

	g_renderingEngine->SetDirectionLight(0, g_vec3Naname, g_vec3One);

	m_modelRender.Update();
	m_spriteRender.Update();
}

void Game::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
	m_spriteRender.Draw(rc);

	m_fontRender.Draw(rc);
}