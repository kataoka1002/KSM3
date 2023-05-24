#pragma once
//数字の読み込み用のmap
const std::map<int, const char*> strings = { // キーと文字列を対応させた連想配列を作成する
	{0, "Assets/sprite/0.DDS"},
	{1, "Assets/sprite/1.DDS"},
	{2, "Assets/sprite/2.DDS"},
	{3, "Assets/sprite/3.DDS"},
	{4, "Assets/sprite/4.DDS"},
	{5, "Assets/sprite/5.DDS"},
	{6, "Assets/sprite/6.DDS"},
	{7, "Assets/sprite/7.DDS"},
	{8, "Assets/sprite/8.DDS"},
	{9, "Assets/sprite/9.DDS"}
};

const char* getString(int key) {
	auto it = strings.find(key); // キーによって対応する文字列を探す
	if (it != strings.end()) { // 対応する文字列があればそれを返す
		return it->second;
	}
	return "Unknown"; // 対応する文字列がなければ "Unknown" を返す
}


//ランク用
const std::map<int, const char*> Rank_font = { // キーと文字列を対応させた連想配列を作成する
	{0, "Assets/sprite/C.DDS"},
	{1, "Assets/sprite/B.DDS"},
	{2, "Assets/sprite/A.DDS"},
	{3, "Assets/sprite/S.DDS"}
};

const char* getRank(int key) {
	auto it = Rank_font.find(key); // キーによって対応する文字列を探す
	if (it != Rank_font.end()) { // 対応する文字列があればそれを返す
		return it->second;
	}
	return "Unknown"; // 対応する文字列がなければ "Unknown" を返す
}

//プレイヤーのカラー用のmap
const std::map<int, const char*> player_result_color = { // キーと文字列を対応させた連想配列を作成する
	{0, "Assets/modelData/player_Red2.tkm"},
	{1, "Assets/modelData/player_blue2.tkm"},
	{2, "Assets/modelData/player_Green2.tkm"},
	{3, "Assets/modelData/player_Yellow2.tkm"},
	{4, "Assets/modelData/player_Pink2.tkm"},
	{5, "Assets/modelData/player_RAINBOW.tkm"},
	{6, "Assets/modelData/player_Gold.tkm"},
	{7, "Assets/modelData/player_warning.tkm"}
};

const char* getPlayer_result_color(int key) {
	auto it = player_result_color.find(key); // キーによって対応する文字列を探す
	if (it != player_result_color.end()) { // 対応する文字列があればそれを返す
		return it->second;
	}
	return "Unknown"; // 対応する文字列がなければ "Unknown" を返す
}