#pragma once
class BackGround : public IGameObject
{
public:
    BackGround();
    ~BackGround();


    bool Start();
    void Update();
    void Render(RenderContext& rc);

    std::unique_ptr<ModelRender> modelRender;
    PhysicsStaticObject physicsStaticObject;//�ÓI�����I�u�W�F�N�g�B
};

