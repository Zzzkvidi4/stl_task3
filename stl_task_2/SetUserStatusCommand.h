#pragma once
#include "Command.h"
#include "RuntimeInfo.h"

class SetUserStatusCommand :
	public Command {
public:
	SetUserStatusCommand(std::string title);
	void Execute();
	~SetUserStatusCommand();
};

