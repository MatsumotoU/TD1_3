#include "MyFileIO.h"

#include <cassert>
#include <sstream>
#include <fstream>
#include <iostream>

#include<Novice.h>

void MyFileIO::LoadFilePath(std::string setFilePath) {

	// ファイル読み込み
	std::ifstream ifs(setFilePath);

	// 読み込み失敗処理
	assert(ifs);

	// ファイルパス保存
	filePath = setFilePath;

}

void MyFileIO::LoadData() {

	// ファイル読み込み
	std::ifstream ifs(filePath);

	// 読み込み失敗処理
	assert(ifs);

	data.clear();

	// データ末尾まで繰り返し
	while (std::getline(ifs, fileData)) {

		std::istringstream iStream(fileData);

		// カンマ区切りで繰り返し
		while (std::getline(iStream, fileConmaData, ',')) {

			data.push_back(fileConmaData);
		}
	}
}

void MyFileIO::LoadArr2DData() {

	// ファイル読み込み
	std::ifstream ifs(filePath);

	// 読み込み失敗処理
	assert(ifs);

	arr2DData.clear();

	int countY = 0;

	// データ末尾まで繰り返し
	while (std::getline(ifs, fileData)) {

		std::istringstream iStream(fileData);

		arr2DData.push_back(std::vector<int>());

		// カンマ区切りで繰り返し
		while (std::getline(iStream, fileConmaData, ',')) {

			arr2DData[countY].push_back(std::stoi(fileConmaData));
		}
		countY++;
	}
}

void MyFileIO::LoadDollAnim() {

	// ファイル読み込み
	std::ifstream ifs(filePath);

	// 読み込み失敗処理
	assert(ifs);

	motion.clear();

	int countF = 0;
	int countObj = 0;

	for (int i = 0; i < 11;  i++) {
		motion.push_back(std::vector<std::vector<float>>());
		motion[i].push_back(std::vector<float>());
	}

	// データ末尾まで繰り返し
	while (std::getline(ifs, fileData)) {
		
		std::istringstream iStream(fileData);

		// カンマ区切りで繰り返し
		while (std::getline(iStream, fileConmaData, ',')) {

			motion[countObj % 11][countF].push_back(std::stof(fileConmaData));
			Novice::ConsolePrintf("object = %d Frame = %d Add = %.1f\n", countObj % 11, countF, std::stof(fileConmaData));
		}

		if (countObj % 11 == 10) {

			for (int i = 0; i < 11; i++) {
				
				motion[i].push_back(std::vector<float>());
			}

			Novice::ConsolePrintf("\nAdd Frame!\n\n");

			countF++;
		}

		countObj++;
	}

	for (int i = 0; i < 11; i++) {
		
		motion[i].pop_back();
	}
}

void MyFileIO::SaveData(std::vector<std::string> setData) {

	// ファイル読み込み
	std::ofstream ofs(filePath, std::ios::trunc);

	// 読み込み失敗処理
	assert(ofs);

	// データ初期化
	saveSumData.clear();

	for (int i = 0; i < setData.size(); i++) {
		saveSumData += setData[i] + ',';
	}

	ofs << saveSumData << std::endl;

}

void MyFileIO::Save2DArr(std::vector<std::vector<int>> setData) {

	// ファイル読み込み
	std::ofstream ofs(filePath, std::ios::trunc);

	// 読み込み失敗処理
	assert(ofs);

	for (int y = 0; y < setData.size(); y++) {

		for (int x = 0; x < setData[y].size(); x++) {

			ofs << setData[setData.size() - (y + 1)][x];
			if (x + 1 < setData[y].size()) {
				ofs << ",";
			}
			
		}
		ofs << std::endl;
	}
}

void MyFileIO::SaveMotionData(std::vector<std::vector<std::vector<float>>> setMotionData) {

	// ファイル読み込み
	std::ofstream ofs(filePath, std::ios::trunc);

	// 読み込み失敗処理
	assert(ofs);

	for (int f = 0; f < setMotionData[0].size(); f++) {
		for (int o = 0; o < setMotionData.size(); o++) {



			for (int v = 0; v < setMotionData[o][f].size(); v++) {

				ofs << setMotionData[o][f][v];
				Novice::ConsolePrintf("%.1f\n", setMotionData[o][f][v]);

				if (v < setMotionData[o][f].size() - 1) {
					ofs << ',';
					Novice::ConsolePrintf(",\n");
				}
			}

			Novice::ConsolePrintf("|Enter|\n");
			ofs << std::endl;
		}
	}
}

void MyFileIO::DrawDara() {

	for (int i = 0; i < data.size(); i++) {
		printf("data(%d) :%s\n", i, data[i].c_str());
	}
	printf("\n");
}

void MyFileIO::DrawArrData() {

	for (int y = 0; y < arr2DData.size(); y++) {

		for (int x = 0; x < arr2DData[0].size(); x++) {

			Novice::ConsolePrintf("%d", arr2DData[y][x]);
		}
		Novice::ConsolePrintf("\n");
	}
}

std::vector<std::string> MyFileIO::GetData() {
	return data;
}

std::vector<std::vector<int>> MyFileIO::GetArr2DData() {
	return arr2DData;
}

std::vector<std::vector<std::vector<float>>> MyFileIO::GetDollData() {

	return motion;
}




