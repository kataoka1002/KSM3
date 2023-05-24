#pragma once
//プレイヤーのカラー用のmap
const std::map<int, const char*> player_custom_color = { // キーと文字列を対応させた連想配列を作成する
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
	auto it = player_custom_color.find(key); // キーによって対応する文字列を探す
	if (it != player_custom_color.end()) { // 対応する文字列があればそれを返す
		return it->second;
	}
	return "Unknown"; // 対応する文字列がなければ "Unknown" を返す
}