#include "MyEasing.h"
#include <math.h>

float Eas::Liner(float transitionRate, float startValue, float endValue) {

	return ((1.0f - transitionRate) * startValue) + (endValue * transitionRate);
}

// イーズイン
float Eas::EaseIn(float transitionRate, float startValue, float endValue) {

	return  (((1.0f - powf(transitionRate, 2.0f)) * startValue) + (endValue * powf(transitionRate, 2.0f)));

}

float Eas::EaseOut(float transitionRate, float startValue, float endValue) {

	return  ((1.0f - powf(1.0f - transitionRate, 10.0f) * startValue) + (endValue * powf(1.0f - transitionRate, 10.0f)));

	//return  (powf((1.0f - transitionRate), 10.0f) * startValue) + (endValue * powf(transitionRate, 10.0f));

}

float Eas::EaseInOut(float transitionRate, float startValue, float endValue) {

	if (transitionRate >= 0.5f) {

		return Eas::EaseIn(transitionRate, endValue + startValue, endValue);

	} else {

		return Eas::EaseOut(transitionRate, startValue, endValue - startValue);

	}
}

void Eas::SimpleEaseIn(float* value, float endValue, float transitionSpeed) {

	*value += (endValue - *value) * transitionSpeed;

	if (fabsf(*value - endValue) <= 0.01f) {
		*value = endValue;
	}
	
}

void Eas::SimpleFadeOut(unsigned int* color) {

	if (*color > 0xFFFFFF00) {
		color -= 0x0000000A;
	}
}
