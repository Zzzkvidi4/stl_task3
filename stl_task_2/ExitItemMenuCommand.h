#pragma once
#include "Command.h"
#include "stdafx.h"
#include "RuntimeInfo.h"

class ExitItemMenuCommand :
	public Command {
public:

	ExitItemMenuCommand(std::string title): Command(title) {}

	void Execute() {
		RuntimeInfo* runtime_info = RuntimeInfo::getInstance();
		runtime_info->setItemPosition(-1);
		runtime_info->removeConcreteElement();
		runtime_info->setCommandPosition(-1);
	}

	~ExitItemMenuCommand() {}
};

