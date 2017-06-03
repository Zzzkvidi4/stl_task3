#pragma once
#include "Command.h"
#include "RuntimeInfo.h"
class SetManagerStatusCommand :
	public Command {
public:
	SetManagerStatusCommand(std::string title);
	void Execute();
	~SetManagerStatusCommand();
};

