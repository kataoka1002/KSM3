#pragma once
//�v���C���[�̃J���[�p��map
const std::map<int, const char*> player_custom_color = { // �L�[�ƕ������Ή��������A�z�z����쐬����
	{0, "Assets/modelData/player_Red2.tkm"},
	{1, "Assets/modelData/player_blue2.tkm"},
	{2, "Assets/modelData/player_Green2.tkm"},
	{3, "Assets/modelData/player_Yellow2.tkm"},
	{4, "Assets/modelData/player_Pink2.tkm"},
	{5, "Assets/modelData/player_RAINBOW.tkm"},
	{6, "Assets/modelData/player_Gold.tkm"},
	{7, "Assets/modelData/player_warning.tkm"}
};

const char* getPlayer_custom_color(int key) {
	auto it = player_custom_color.find(key); // �L�[�ɂ���đΉ����镶�����T��
	if (it != player_custom_color.end()) { // �Ή����镶���񂪂���΂����Ԃ�
		return it->second;
	}
	return "Unknown"; // �Ή����镶���񂪂Ȃ���� "Unknown" ��Ԃ�
}