#pragma once
namespace nsK2EngineLow {
	ID3D12Device* g_D3DDevice;
	class ToonMap
	{
	public:
		ToonMap();
		~ToonMap();
		void Init();
		void SetSHaderResourceView();

	private:
		
	};
}

