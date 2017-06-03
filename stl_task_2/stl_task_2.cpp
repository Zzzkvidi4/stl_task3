// stl_task_2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>

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

void FillMenu(TemplateContainer<Bill>* cont, CommandList* list) {
	list->Clear();
	list->RegisterCommand(new ExitCommand("�����."));
	list->RegisterCommand(new ReadFromFileCommand<Bill>("���������� �� �����.", cont));
	if (cont->size() != 0) {
		list->RegisterCommand(new PrintToFileCommand<Bill>("����� � ����.", cont));
		list->RegisterCommand(new PrintCommand<Bill>("����� � �������.", cont));
	}
	list->RegisterCommand(new AddBillCommand("���������� ������.", cont));
	if (cont->size() != 0) {
		list->RegisterCommand(new EditRecordCommand("�������������� ������.", cont));
		list->RegisterCommand(new RemoveCommand("�������� ������.", cont));
		list->RegisterCommand(new SelectCommand("������� �������.", cont));
	}
}

int main()
{
	setlocale(LC_ALL, "russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	TemplateContainer<Bill>* cont = new TemplateContainer<Bill>();
    CommandList* main_menu = new CommandList();
    int choice = -1;
    while (choice != 0) {
		FillMenu(cont, main_menu);
        main_menu->PrintTitles("�������� ���� �� ������� ����:");
        getChoice(0, main_menu->Size(), choice);
        main_menu->ExecuteCommand(choice);
    }
	return 0;
}

