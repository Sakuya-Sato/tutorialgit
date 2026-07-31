#include <iostream>
#include <thread>

#include "signal.h"

int main() {
	char input;
	std::cout << "横断歩道を渡りたい時に \"a\" と入力してください"
		<< std::endl << std::endl;

	signal::Signal pedSign;
	pedSign.startSwitchLoop();

	std::cin >> input;

	signal::Color color = pedSign.getCurrentColor();
	switch (color) {
	case signal::Color::kRed:
		std::cout << "渡れませんでした" << std::endl;
		break;
	case signal::Color::kYellow:
		std::cout << "なんとか渡れました" << std::endl;
		break;
	case signal::Color::kGreen:
		std::cout << "渡れました" << std::endl;
		break;
	default:
		std::cout << "エラー" << std::endl;
		break;
	}

	std::cout << std::endl;  // 改行
	pedSign.stopSwitchLoop();

	return 0;
}