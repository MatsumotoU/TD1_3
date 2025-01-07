#pragma once
#include <string>
#include <vector>

class MyFileIO {
public:

	/// <summary>
	/// ファイルのパスを保存する関数
	/// </summary>
	/// <param name="setFilePath">入出力をしたいファイルのパス</param>
	void LoadFilePath(std::string setFilePath);

	/// <summary>
	/// ファイルのデータ読み込み用関数
	/// </summary>
	/// <param name="setFilePath">ファイルのパス</param>
	void LoadData();

	void LoadArr2DData();

	void LoadDollAnim();

	/// <summary>
	/// カンマ区切りのファイルデータを返す
	/// </summary>
	/// <returns>std::vector<std::string>型で返すデータ</returns>
	std::vector<std::string> GetData();

	std::vector<std::vector<int>> GetArr2DData();

	std::vector <std::vector<std::vector<float>>> GetDollData();

	/// <summary>
	/// ファイルのデータ書き込み用関数
	/// </summary>
	/// <param name="setData">std::vector<std::string>型で保存したいデータ</param>
	void SaveData(std::vector<std::string> setData);

	void Save2DArr(std::vector<std::vector<int>> setData);

	void SaveMotionData(std::vector<std::vector<std::vector<float>>> setMotionData);

	/// <summary>
	/// 要素数と要素確認用
	/// </summary>
	void DrawDara();

	void DrawArrData();

private:

	std::string filePath;
	std::string fileData;
	std::string fileConmaData;
	std::string saveData;
	std::string saveSumData;

	std::vector<std::string> data;
	std::vector<std::vector<int>> arr2DData;
	std::vector <std::vector<std::vector<float>>> motion;
};

