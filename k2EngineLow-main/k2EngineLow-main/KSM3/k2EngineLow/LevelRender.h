#pragma once
#include "level3D/TklFile.h"

namespace nsK2EngineLow {

	struct LevelObjectData2 {
		Vector3 position;		//���W
		Quaternion rotation;	//��]
		Vector3 scale;			//�g�嗦
		const wchar_t* name;	//���O
		int number = 0;
		
		//�����œn�����I�u�W�F�N�g���̃I�u�W�F�N�g�����ׂ�B
		//���O�������ꍇ��true��Ԃ��܂��B
		bool EqualObjectName(const wchar_t* objName)//���ׂ閼�O�B
		{
			return wcscmp(objName, name) == 0;
		}
		//���O���O����v���邩���ׂ�B
		bool ForwardMatchName(const wchar_t* n)
		{
			auto len = wcslen(n);
			auto namelen = wcslen(name);
			if (len > namelen) {
				//���O�������B�s��v�B
				return false;
			}
			return wcsncmp(n, name, len) == 0;
		}
	};

	class LevelRender : public Noncopyable{
	private:

	public:
		~LevelRender();

		//����������
		void Init(const char* filePath, std::function<bool(LevelObjectData2& objData)> hookFunc);

	private:
		//tkl�t�@�C���̍s���ύX����
		void MatrixTklToLevel();

	private:
		using BonePtr = std::unique_ptr<Bone>;								//�{�[��Ptr�B
		std::vector<BonePtr> m_bonelist;									//�{�[���̃��X�g�B
		std::unique_ptr<Matrix[]> m_matrixlist;								//�s��̃��X�g�B
		TklFile m_tklFile;
	};
}

