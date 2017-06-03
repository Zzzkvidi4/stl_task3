#include "stdafx.h"
#include "EditRecordCommand.h"
#include "ContainerUtils.h"

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
	Bill& bill = (*cont)[choice];
	CommandList* record_list = new CommandList();
	record_list->RegisterCommand(new ExitCommand("�����."));
	record_list->RegisterCommand(new SetStreetCommand("�����.", bill));
	record_list->RegisterCommand(new SetHouseNumberCommand("����� ����.", bill));
	record_list->RegisterCommand(new SetBlockNumberCommand("����� ��������.", bill));
	record_list->RegisterCommand(new SetApartmentNumberCommand("����� ��������.", bill));
	record_list->RegisterCommand(new SetSurnameCommand("������� ���������.", bill));
	record_list->RegisterCommand(new SetYearCommand("��� �������.", bill));
	record_list->RegisterCommand(new SetMonthCommand("����� �������.", bill));
	record_list->RegisterCommand(new SetDayCommand("���� �������.", bill));
	record_list->RegisterCommand(new SetPaymentCommand("����� �������.", bill));
	record_list->RegisterCommand(new SetPaymentTypeCommand("��� �������.", bill));
	record_list->RegisterCommand(new SetPeniCommand("������� ����.", bill));
	record_list->RegisterCommand(new SetDelayDaysNumberCommand("���������� ���� ���������.", bill));
	choice = -1;
	while (choice != 0) {
		std::cout << bill << std::endl;
		record_list->PrintTitles("�������� ���� �� ������� ���� ���������:");
		getChoice(0, record_list->Size(), choice);
		record_list->ExecuteCommand(choice);
	}
}

int EditRecordCommand::SelectBill() {
	ContainerUtils<Bill>::print_to_console(std::cout, *cont);
	std::cout << "�������� ������ (0 - ������):" << std::endl;
	int choice = -1;
	getChoice(0, cont->size(), choice);
	return choice;
}

EditRecordCommand::~EditRecordCommand()
{
}
