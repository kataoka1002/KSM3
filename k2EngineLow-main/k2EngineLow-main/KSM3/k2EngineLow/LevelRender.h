#pragma once
#include "level3D/TklFile.h"

namespace nsK2EngineLow {

	struct LevelObjectData2 {
		Vector3 position;		//座標
		Quaternion rotation;	//回転
		Vector3 scale;			//拡大率
		const wchar_t* name;	//名前
		int number = 0;
		
		//引数で渡したオブジェクト名のオブジェクトか調べる。
		//名前が同じ場合にtrueを返します。
		bool EqualObjectName(const wchar_t* objName)//調べる名前。
		{
			return wcscmp(objName, name) == 0;
		}
		//名前が前方一致するか調べる。
		bool ForwardMatchName(const wchar_t* n)
		{
			auto len = wcslen(n);
			auto namelen = wcslen(name);
			if (len > namelen) {
				//名前が長い。不一致。
				return false;
			}
			return wcsncmp(n, name, len) == 0;
		}
	};

	class LevelRender : public Noncopyable{
	private:

	public:
		~LevelRender();

		//初期化処理
		void Init(const char* filePath, std::function<bool(LevelObjectData2& objData)> hookFunc);

	private:
		//tklファイルの行列を変更する
		void MatrixTklToLevel();

	private:
		using BonePtr = std::unique_ptr<Bone>;								//ボーンPtr。
		std::vector<BonePtr> m_bonelist;									//ボーンのリスト。
		std::unique_ptr<Matrix[]> m_matrixlist;								//行列のリスト。
		TklFile m_tklFile;
	};
}

