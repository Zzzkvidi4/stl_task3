#pragma once
#include "Command.h"
#include "stdafx.h"

class ExitSubMenuCommand :
	public Command {
public:

	ExitSubMenuCommand(std::string title): Command(title) {}

	void Execute() {
		RuntimeInfo* runtime_info = RuntimeInfo::getInstance();
		runtime_info->removeLastItem();
	}

	~ExitSubMenuCommand() {}
};

