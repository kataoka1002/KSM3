#include "k2EngineLowPreCompile.h"
#include "RenderingEngine.h"

namespace nsK2EngineLow {

	bool RenderingEngine::Start()
	{
		return true;
	}

	void RenderingEngine::Execute(RenderContext& rc)
	{
		for (auto MobjData : ModelRenderObject) {
			MobjData->OnDraw(rc);
		}
		for(auto SobjData:SpriteRenderObject){
			SobjData->OnDraw(rc);
		}
		for (auto FobjData : FontRenderObject) {
			FobjData->OnDraw(rc);
		}
		ModelRenderObject.clear();
		SpriteRenderObject.clear();
		FontRenderObject.clear();
	}
}