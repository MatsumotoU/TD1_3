#pragma once
class TimeManager
{
public:

	//	シングルトン
	static TimeManager* GetInstance() {
		static TimeManager instance;
		return &instance;
	}

	float temporalResolution;
	float frameCount;

	void SetTemporalResolution(float set);

	int GetTempo(int parSec);

	void Init();
	void Update();

private:

	TimeManager() = default;
	~TimeManager() = default;

	// * おまじない * //
	// コピーコンストラクタを削除
	TimeManager(const TimeManager&) = delete;

	// コピー代入演算子を削除
	TimeManager& operator=(const TimeManager&) = delete;

};

