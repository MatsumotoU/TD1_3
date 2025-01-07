#include "TimeManager.h"

void TimeManager::SetTemporalResolution(float set) {
	temporalResolution = set;
}

int TimeManager::GetTempo(int parSec) {

	if (parSec == 0) {
		return-1;
	}

	return static_cast<int>(frameCount) % static_cast<int>(static_cast<float>(parSec));
}

void TimeManager::Init() {

	frameCount = 0.0f;
	temporalResolution = 1.0f;

}

void TimeManager::Update() {
	frameCount++;
}
