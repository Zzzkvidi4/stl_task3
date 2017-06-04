// stl_task_2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include "RuntimeInfo.h"

/*����������� ������ ���� ���������� ��������� � ��������� ����. ��������� ������ ��������� ��������� ����� ��� ���������� ������� �������� �������. ��� �������� ������ ���������� ������� ����������� � ����� ������ ������� ���������. 
1. ������������� �������� ����������, ��������� � �������� �������� ����������. 
2. ����������� ���� � ����� ��������� ���������� � �������������� ��������� ���������� �� ����� � � ����. 
3. ����������� �������� ������ �� �������� ��������� � ������� ������������ ��������� �� �������� ���������. ����������� ����� � ���� ���������: �������� ����� � �������� ����� �� ��������������� ����������. 
4. ������������� ����� ������������ ������� �� ����� � � ����. 
�������� �������. 
8. ��������� ������ � ������������ ������� �������� ����: ����� ��������,
������� ���������, ��� �������, ���� �������, ����� �������, ������� ����,
���������� ���� ��������� �������. 
����� �� ������ ����, ��������, ���������, ����, ������� �����. 
����� ����� ����� � ����������� ������. */

void FillMainMenu(RuntimeInfo* runtime_info, TemplateContainer<Bill>* cont, CommandList* list) {
	list->Clear();
	list->RegisterCommand(new ExitCommand("�����."));
	list->RegisterCommand(new ReadFromFileCommand<Bill>("���������� �� �����.", cont));
	if (cont->size() != 0) {
		list->RegisterCommand(new PrintCommand<Bill>("����� � �������.", cont));
		if (runtime_info->getUserStatus() >= ROLE_MANAGER) {
			list->RegisterCommand(new PrintToFileCommand<Bill>("����� � ����.", cont));
			list->RegisterCommand(new AddBillCommand("���������� ������.", cont));
			list->RegisterCommand(new EditRecordCommand("�������������� ������.", cont));
			list->RegisterCommand(new RemoveCommand("�������� ������.", cont));
		}
		list->RegisterCommand(new SelectCommand("������� �������.", cont));
	}
	if (runtime_info->getUserStatus() == ROLE_MANAGER) {
		list->RegisterCommand(new SetUserStatusCommand("����� ������������."));
	} else if (runtime_info->getUserStatus() == ROLE_USER) {
		list->RegisterCommand(new SetManagerStatusCommand("����� ���������."));
	}
}

void FillSubMenu(RuntimeInfo* runtime_info, TemplateContainer<Bill>* cont, CommandList* list) {
	list->Clear();
	list->RegisterCommand(new ExitSubMenuCommand("�����."));
	if (cont->size() != 0) {
		list->RegisterCommand(new PrintCommand<Bill>("������� � �������.", cont));
		if (runtime_info->getUserStatus() >= ROLE_MANAGER) {
			list->RegisterCommand(new PrintToFileCommand<Bill>("��������� � ����.", cont));
			list->RegisterCommand(new RemoveCommand("������� ������.", cont));
			list->RegisterCommand(new EditRecordCommand("������������� ������.", cont));
		}
	}
}

void FillItemMenu(RuntimeInfo* runtime_info, Bill* bill, CommandList* list) {
	list->Clear();
	list->RegisterCommand(new ExitItemMenuCommand("�����."));
	list->RegisterCommand(new SetStreetCommand("�����.", *bill));
	list->RegisterCommand(new SetHouseNumberCommand("����� ����.", *bill));
	list->RegisterCommand(new SetBlockNumberCommand("����� ��������.", *bill));
	list->RegisterCommand(new SetApartmentNumberCommand("����� ��������.", *bill));
	list->RegisterCommand(new SetSurnameCommand("������� ���������.", *bill));
	list->RegisterCommand(new SetYearCommand("��� �������.", *bill));
	list->RegisterCommand(new SetMonthCommand("����� �������.", *bill));
	list->RegisterCommand(new SetDayCommand("���� �������.", *bill));
	list->RegisterCommand(new SetPaymentCommand("����� �������.", *bill));
	list->RegisterCommand(new SetPaymentTypeCommand("��� �������.", *bill));
	list->RegisterCommand(new SetPeniCommand("������� ����.", *bill));
	list->RegisterCommand(new SetDelayDaysNumberCommand("���������� ���� ���������.", *bill));
}

void FillMenu(RuntimeInfo* runtime_info, CommandList* list) {
	switch (runtime_info->getContainersStatus()) {
		case CONTAINER_EXISTS: {
			FillMainMenu(runtime_info, runtime_info->getMainContainer(), list);
			break;
		}
		case SUBCONTAINER_EXISTS: {
			FillSubMenu(runtime_info, runtime_info->getSubContainer(), list);
			break;
		}
		case CONCRETE_ELEMENT_EXISTS: {
			FillItemMenu(runtime_info, runtime_info->getConcreteElement(), list);
			break;
		}
		case NO_CONTAINER: {
			FillMainMenu(runtime_info, runtime_info->getMainContainer(), list);
			break;
		}
	}
}

int main()
{
	setlocale(LC_ALL, "russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	TemplateContainer<Bill>* cont = new TemplateContainer<Bill>();
    CommandList* menu = new CommandList();
	RuntimeInfo* runtime_info = RuntimeInfo::getInstance();
	if (!runtime_info->recoverInfo()) {
		print_message("��������, �������������� �� ���� ��������� �������!");
	} else {
		if (runtime_info->getCommandPosition() != -1) {
			FillMenu(runtime_info, menu);
			try {
				menu->ExecuteCommand(runtime_info->getCommandPosition());
			}
			catch (std::exception e) {
				print_message("������ ��������� ������� ����������. ��������, ���� � ����������� ��� ��������� ��� ��������� ������� ���� �������� �������.");
			}
		}
	}
    int choice = -1;
    while (runtime_info->getProgramStatus() != PROGRAM_EXIT) {
		FillMenu(runtime_info, menu);
		runtime_info->setCommandPosition(-1);
		if (runtime_info->getContainersStatus() == CONCRETE_ELEMENT_EXISTS) {
			std::cout << *(runtime_info->getConcreteElement()) << std::endl;
		}
        menu->PrintTitles("�������� ���� �� ������� ����:");
        getChoice(0, menu->Size(), choice);
		if (choice != 0) {
			runtime_info->setCommandPosition(choice);
		}
        menu->ExecuteCommand(choice);
    }
	return 0;
}

