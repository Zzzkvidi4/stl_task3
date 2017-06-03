#include "stdafx.h"
#include "SetUserStatusCommand.h"

SetUserStatusCommand::SetUserStatusCommand(std::string title): Command(title) {}

void SetUserStatusCommand::Execute(){
	RuntimeInfo* runtime_info = RuntimeInfo::getInstance();
	runtime_info->setUserStatus();
}

SetUserStatusCommand::~SetUserStatusCommand() {}
