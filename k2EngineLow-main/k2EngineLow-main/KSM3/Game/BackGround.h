#pragma once
class BackGround : public IGameObject
{
public:
    BackGround();
    ~BackGround();


    bool Start();
    void Update();
    void Render(RenderContext& rc);

    ModelRender modelRender;
    PhysicsStaticObject physicsStaticObject;//�ÓI�����I�u�W�F�N�g�B
};

