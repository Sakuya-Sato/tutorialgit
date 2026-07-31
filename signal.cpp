#include "signal.h"

#include <iostream>
#include <thread>
#include <string>

namespace signal {

void Signal::setColor(bool canAcross) {
	if (canAcross) {  // 横断できる場合
		switch (this->currentColor) {
		case Color::kRed:
		case Color::kYellow:
			std::this_thread::sleep_for(std::chrono::seconds(3));
			this->currentColor = Color::kGreen;
			std::cout << "青色になりました" << std::endl;
		case Color::kGreen:
			break;
		default:
			this->currentColor = Color::kGreen;
		}
	}
	else {  // 横断できない場合
		switch (this->currentColor) {
		case Color::kGreen:
			std::this_thread::sleep_for(std::chrono::seconds(3));
			this->currentColor = Color::kYellow;
			std::cout << "黄色 -> ";
		case Color::kYellow:
			std::this_thread::sleep_for(std::chrono::seconds(1));
			this->currentColor = Color::kRed;
			std::cout << "赤色になりました" << std::endl;
		case Color::kRed:
			break;
		default:
			this->currentColor = Color::kRed;
		}
	}
}

Color Signal::getCurrentColor() {
	return this->currentColor;
}

void Signal::startSwitchLoop() {
	this->isLooping = true;
	std::cout << "信号を動かします" << std::endl;
	std::thread t([this]() {
		while (this->isLooping) {
			std::thread green(&Signal::setColor, this, true);
			green.join();

			if (!this->isLooping) {
				break;
			}
			std::thread red(&Signal::setColor, this, false);
			red.join();

		}
	});
	t.detach();


	/*
		問題
			ここに、startSwitchLoop() が呼び出しされてから
			stopSwitchLoop() が呼び出されるまでの間、
			信号を切り替え続ける処理を記載してください。

			必ず setColor() を利用して、次のように切り替えてください。

			青信号に変える -> 変わるまで待つ
				-> 赤信号に変える -> 変わるまで待つ
					-> 青信号に変える -> ...

		ヒント
			メンバ関数を別スレッドで呼びたい場合、
			第1引数には & クラス名 :: メンバ関数名 を、
			第2引数には this 渡す
			std::thread test(&Signal::stopSwitchLoop, this);
			test.join();
	*/
}

void Signal::stopSwitchLoop() {
	this->isLooping = false;
	std::cout << "信号を止めます" << std::endl;
}

}  // namespace signal