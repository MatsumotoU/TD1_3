#pragma once

class SceneTransition{
public:
	void Init();
	void Update();
	void Draw();

	void SetIsTransition(int setIsTransition);
	int GetIsTransition();
	int GetIsTransitionClosed();

private:
	int transitionTime;

	int isTransition;
	int isTransitionClosed;

};

