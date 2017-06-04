// stl_task_2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include "RuntimeInfo.h"

/*Результатом должна быть консольная программа с текстовым меню. Программа должна содержать шаблонный класс для управления данными согласно заданию. Для хранения данных необходимо выбрать оптимальный с точки зрения задания контейнер. 
1. Предусмотреть операции добавления, изменения и удаления элемента контейнера. 
2. Реализовать ввод и вывод элементов контейнера с использованием потоковых итераторов на экран и в файл. 
3. Реализовать операции поиска по заданным критериям и выборки подмножества элементов по заданным критериям. Реализовать поиск в двух вариантах: линейный поиск и двоичный поиск на отсортированном контейнере. 
4. Предусмотреть вывод подмножества выборки на экран и в файл. 
Варианты заданий. 
8. Структура записи о коммунальном платеже содержит поля: адрес квартиры,
фамилия владельца, вид платежа, дата платежа, сумма платежа, процент пени,
количество дней просрочки платежа. 
Поиск по номеру дома, квартиры, владельцу, дате, наличии долга. 
Вывод суммы долга в результатах поиска. */

void FillMainMenu(RuntimeInfo* runtime_info, TemplateContainer<Bill>* cont, CommandList* list) {
	list->Clear();
	list->RegisterCommand(new ExitCommand("Выход."));
	list->RegisterCommand(new ReadFromFileCommand<Bill>("Заполнение из файла.", cont));
	if (cont->size() != 0) {
		list->RegisterCommand(new PrintCommand<Bill>("Вывод в консоль.", cont));
		if (runtime_info->getUserStatus() >= ROLE_MANAGER) {
			list->RegisterCommand(new PrintToFileCommand<Bill>("Вывод в файл.", cont));
			list->RegisterCommand(new AddBillCommand("Добавление записи.", cont));
			list->RegisterCommand(new EditRecordCommand("Редактирование записи.", cont));
			list->RegisterCommand(new RemoveCommand("Удаление записи.", cont));
		}
		list->RegisterCommand(new SelectCommand("Выборка записей.", cont));
	}
	if (runtime_info->getUserStatus() == ROLE_MANAGER) {
		list->RegisterCommand(new SetUserStatusCommand("Режим пользователя."));
	} else if (runtime_info->getUserStatus() == ROLE_USER) {
		list->RegisterCommand(new SetManagerStatusCommand("Режим менеджера."));
	}
}

void FillSubMenu(RuntimeInfo* runtime_info, TemplateContainer<Bill>* cont, CommandList* list) {
	list->Clear();
	list->RegisterCommand(new ExitSubMenuCommand("Назад."));
	if (cont->size() != 0) {
		list->RegisterCommand(new PrintCommand<Bill>("Вывести в консоль.", cont));
		if (runtime_info->getUserStatus() >= ROLE_MANAGER) {
			list->RegisterCommand(new PrintToFileCommand<Bill>("Сохранить в файл.", cont));
			list->RegisterCommand(new RemoveCommand("Удалить запись.", cont));
			list->RegisterCommand(new EditRecordCommand("Редактировать запись.", cont));
		}
	}
}

void FillItemMenu(RuntimeInfo* runtime_info, Bill* bill, CommandList* list) {
	list->Clear();
	list->RegisterCommand(new ExitItemMenuCommand("Назад."));
	list->RegisterCommand(new SetStreetCommand("Улица.", *bill));
	list->RegisterCommand(new SetHouseNumberCommand("Номер дома.", *bill));
	list->RegisterCommand(new SetBlockNumberCommand("Номер строения.", *bill));
	list->RegisterCommand(new SetApartmentNumberCommand("Номер квартиры.", *bill));
	list->RegisterCommand(new SetSurnameCommand("Фамилия владельца.", *bill));
	list->RegisterCommand(new SetYearCommand("Год платежа.", *bill));
	list->RegisterCommand(new SetMonthCommand("Месяц платежа.", *bill));
	list->RegisterCommand(new SetDayCommand("День платежа.", *bill));
	list->RegisterCommand(new SetPaymentCommand("Сумма платежа.", *bill));
	list->RegisterCommand(new SetPaymentTypeCommand("Тип платежа.", *bill));
	list->RegisterCommand(new SetPeniCommand("Процент пени.", *bill));
	list->RegisterCommand(new SetDelayDaysNumberCommand("Количество дней просрочки.", *bill));
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
		print_message("Внимание, восстановление не было завершено успешно!");
	} else {
		if (runtime_info->getCommandPosition() != -1) {
			FillMenu(runtime_info, menu);
			try {
				menu->ExecuteCommand(runtime_info->getCommandPosition());
			}
			catch (std::exception e) {
				print_message("Запуск последней команды невозможен. Возможно, файл с информацией был поврежден или последний рабочий файл изменили вручную.");
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
        menu->PrintTitles("Выберите один из пунктов меню:");
        getChoice(0, menu->Size(), choice);
		if (choice != 0) {
			runtime_info->setCommandPosition(choice);
		}
        menu->ExecuteCommand(choice);
    }
	return 0;
}

