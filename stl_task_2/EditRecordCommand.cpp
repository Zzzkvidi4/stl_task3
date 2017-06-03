#include "stdafx.h"
#include "EditRecordCommand.h"
#include "ContainerUtils.h"
#include "RuntimeInfo.h"

EditRecordCommand::EditRecordCommand(std::string title, TemplateContainer<Bill>* cont): Command(title)
{
	this->cont = cont;
}

void EditRecordCommand::Execute()
{
	int choice;
 	if ((choice = SelectBill()) == 0) {
		return;
	}
	RuntimeInfo* runtime_info = RuntimeInfo::getInstance();
	runtime_info->setConcreteElement(&(*cont)[choice]);
}

int EditRecordCommand::SelectBill() {
	ContainerUtils<Bill>::print_to_console(std::cout, *cont);
	std::cout << "Выберите запись (0 - отмена):" << std::endl;
	int choice = -1;
	getChoice(0, cont->size(), choice);
	return choice;
}

EditRecordCommand::~EditRecordCommand()
{
}
