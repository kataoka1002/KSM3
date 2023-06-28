#pragma once
class Enumeration:public IGameObject
{
public:
	enum Custom_Kinds {
		non_select,
		Batteleship_gun
	};

	Enumeration();
	~Enumeration();

	Custom_Kinds m_customKinds;
};

