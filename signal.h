#pragma once

namespace Signal {

enum class Color {
	kRed = 0,
	kYellow,
	kGreen,
};

class Signal {
private:
	int num = 20;
	Color currentColor;
	bool isLooping = false;
	void setColor(bool canAcross);
public:
	Color getCurrentColor();
	void startSwitchLoop();
	void stopSwitchLoop();
};

} // namespace signal