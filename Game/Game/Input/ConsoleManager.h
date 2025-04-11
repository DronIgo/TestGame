#pragma once

#include <string>
#include <thread>
#include "Utility/Singleton.h"

class ConsoleManager : public Singleton<ConsoleManager> {
private:
	std::thread* readThread;
	bool shouldClose = false;
	void messageLoop();

public:
	void init();


};