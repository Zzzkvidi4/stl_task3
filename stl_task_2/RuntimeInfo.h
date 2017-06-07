#pragma once
#include <string>
#include "TemplateContainer.h"
#include "ContainerUtils.h"

#define NO_CONTAINER 0
#define CONTAINER_EXISTS 1
#define SUBCONTAINER_EXISTS 2
#define CONCRETE_ELEMENT_EXISTS 3
#define ROLE_USER 0
#define ROLE_MANAGER 1
#define PROGRAM_RUNNING 0
#define PROGRAM_LAUNCHING 1
#define PROGRAM_EXIT 2

class RuntimeInfo {
private:
	RuntimeInfo() {};
	const std::string runtime_info_file_name = "runtime_info.dat";
	static RuntimeInfo* instance;
	int container_status = NO_CONTAINER;
	int user_status = ROLE_USER;	//!
	int program_status = PROGRAM_RUNNING;
	TemplateContainer<Bill>* main_container = new TemplateContainer<Bill>();
	TemplateContainer<Bill>* sub_container = new TemplateContainer<Bill>();
	Bill* concrete_element = new Bill;
	std::string file_name = ""; //!
	std::string factory_name = ""; //!
	std::string query_value = ""; //!
	int item_position = -1; //!
	int command_position = -1; //!


public:
	~RuntimeInfo() {};

	static RuntimeInfo* getInstance() {
		if (instance == NULL) {
			instance = new RuntimeInfo();
		}
		return instance;
	};

	void synchronizeContainers() {
		std::ofstream fout(file_name);
		ContainerUtils<Bill>::print_to_file(fout, *main_container + *sub_container);
	}

	void setFileName(std::string filename) {
		this->file_name = filename;
		saveInfo();
	}

	std::string getFileName() {
		return file_name;
	}

	void setFactoryName(std::string factory_name) {
		this->factory_name = factory_name;
		saveInfo();
	}

	std::string getFactoryName() {
		return factory_name;
	}

	void setQueryValue(std::string query_value) {
		this->query_value = query_value;
		saveInfo();
	}

	std::string getQueryValue() {
		return query_value;
	}

	void setItemPosition(int item_position) {
		this->item_position = item_position;
		saveInfo();
	}

	int getItemPosition() {
		return item_position;
	}

	void setCommandPosition(int command_position);

	int getCommandPosition();

	TemplateContainer<Bill>* getMainContainer() {
		return main_container;
	}

	void setMainContainer(TemplateContainer<Bill>* container) {
		if (main_container != NULL) {
			main_container->clear();
		}
		main_container = container;
		container_status = CONTAINER_EXISTS;
	}

	TemplateContainer<Bill>* getSubContainer() {
		return sub_container;
	}

	void setSubContainer(TemplateContainer<Bill>* container) {
		if (sub_container != NULL) {
			sub_container->clear();
		}
		sub_container = container;
		container_status = SUBCONTAINER_EXISTS;
	}

	Bill* getConcreteElement() {
		return concrete_element;
	}

	void setConcreteElement(Bill* element) {
		concrete_element = element;
		container_status = CONCRETE_ELEMENT_EXISTS;
	}

	void removeMainContainer() {
		main_container->clear();
		container_status = NO_CONTAINER;
	}

	void removeSubContainer() {
		if (sub_container->size() != 0) {
			main_container->PushBack(sub_container);
			sub_container->clear();
		}
		container_status = CONTAINER_EXISTS;
	}

	void removeConcreteElement() {
		concrete_element = NULL;
		if (sub_container->size() != 0) {
			container_status = SUBCONTAINER_EXISTS;
		} else if (main_container->size() != 0) {
			container_status = CONTAINER_EXISTS;
		}
	}

	void removeLastItem() {
		switch (container_status) {
			case CONCRETE_ELEMENT_EXISTS: {
				removeConcreteElement();
				break;
			}
			case SUBCONTAINER_EXISTS: {
				removeSubContainer();
				break;
			}
			case CONTAINER_EXISTS: {
				removeMainContainer();
				break;
			}
			default: {
				break;
			}
		}
	}

	int getContainersStatus() {
		return container_status;
	}

	int getUserStatus() {
		return user_status;
	}

	void setManagerStatus() {
		user_status = ROLE_MANAGER;
		saveInfo();
	}

	void setUserStatus() {
		user_status = ROLE_USER;
		saveInfo();
	}

	int getProgramStatus() {
		return program_status;
	}

	void setExitStatus() {
		program_status = PROGRAM_EXIT;
	}

	bool recoverInfo();

	void saveInfo();

	friend std::ostream& operator<<(std::ostream& out, RuntimeInfo& info);

	friend std::istream& operator>>(std::istream& in, RuntimeInfo& info);
};

