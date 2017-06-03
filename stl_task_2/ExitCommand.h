#pragma once
#include "Command.h"
#include "stdafx.h"
#include "RuntimeInfo.h"

class ExitCommand: public Command
{
public:

	ExitCommand(std::string title): Command(title) {
	}

	void Execute() {
		RuntimeInfo* runtime_info = RuntimeInfo::getInstance();
		runtime_info->setExitStatus();
	}

	~ExitCommand() {
	}
};

