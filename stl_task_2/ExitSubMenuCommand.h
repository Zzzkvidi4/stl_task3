#pragma once
#include "Command.h"
#include "stdafx.h"

class ExitSubMenuCommand :
	public Command {
public:

	ExitSubMenuCommand(std::string title): Command(title) {}

	void Execute() {
		RuntimeInfo* runtime_info = RuntimeInfo::getInstance();
		runtime_info->setFactoryName("");
		runtime_info->removeSubContainer();
		runtime_info->setCommandPosition(-1);
	}

	~ExitSubMenuCommand() {}
};

