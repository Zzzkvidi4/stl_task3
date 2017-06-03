#include "stdafx.h"
#include "SetManagerStatusCommand.h"


SetManagerStatusCommand::SetManagerStatusCommand(std::string title): Command(title) {}

void SetManagerStatusCommand::Execute() {
	RuntimeInfo* runtime_info = RuntimeInfo::getInstance();
	runtime_info->setManagerStatus();
}


SetManagerStatusCommand::~SetManagerStatusCommand() {}
