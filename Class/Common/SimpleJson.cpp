#include "SimpleJson.h"
#include <Novice.h>

SJN::json SJN::LoadJsonData(std::string& fp) {
    SJN::json result;
    
	// jsonデータ読み込み
	std::ifstream ifs;
	ifs.open(fp);

	// ファイル開けない時のエラー
	if (ifs.fail()) {
		std::string message = "Failed open data file for read(" + fp + ")";
		MessageBoxA(nullptr, message.c_str(), "GrobalVariables", 0);
		assert(0);
		return 0;
	}

	ifs >> result;
	ifs.close();

    return result;
}

void SJN::SaveJsonData(const std::string groupName, json saveData) {

	// ファイル生成(階層ごとにやらなきゃダメっぽい？)
	if (!std::filesystem::exists("Resources")) {
		std::filesystem::create_directory("Resources");
	}
	if (!std::filesystem::exists("Resources/GlobalVariables")) {
		std::filesystem::create_directory("Resources/GlobalVariables");
	}

	// jsonデータ生成
	std::string filePath = kDirectoryPath + groupName + ".json";
	std::ofstream ofs;
	ofs.open(filePath);

	// ファイル開けない時のエラー
	if (ofs.fail()) {
		std::string message = "Failed open data file for write.";
		MessageBoxA(nullptr, message.c_str(), "GrobalVariables", 0);
		assert(0);
		return;
	}

	ofs << std::setw(4) << saveData << std::endl;
	ofs.close();
}
