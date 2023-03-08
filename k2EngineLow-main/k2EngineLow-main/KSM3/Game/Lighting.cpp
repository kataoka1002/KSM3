#include "stdafx.h"
#include "Lighting.h"

Lighting::Lighting() {
	Light_Direction.Normalize();
	g_renderingEngine->SetDirectionLight(Light_Direction, Light_Color);
}

Lighting::~Lighting() {

}

void Lighting::Update()
{

}

