#pragma once
#include <string>
#define NO_CONTAINER 0
#define CONTAINER_EXISTS 1
#define SUBCONTAINER_EXISTS 2
#define CONCRETE_ELEMENT_EXISTS 3
#define ROLE_USER 0
#define ROLE_MANAGER 1

template<class T>
class RuntimeInfo {
private:
	RuntimeInfo() {};
	static RuntimeInfo* instance = NULL;
	int container_status = NO_CONTAINER;
	int user_status = ROLE_USER;
	TemplateContainer<T>* main_container = NULL;
	TemplateContainer<T>* sub_container = NULL;
	T* concrete_element = NULL;
public:
	~RuntimeInfo() {};

	static RuntimeInfo* getInstance() {
		if (instance == NULL) {
			instance = new RuntimeInfo();
		}
		return instance;
	};

	TemplateContainer<T>* getMainContainer() {
		return main_container;
	}

	void setMainContainer(TemplateContainer<T>* container) {
		main_container->clear();
		main_container = container;
		container_status = CONTAINER_EXISTS;
	}

	TemplateContainer<T>* getSubContainer() {
		return sub_container;
	}

	void setSubContainer(TemplateContainer<T>* container) {
		sub_container->clear();
		sub_container = container;
		container_status = SUBCONTAINER_EXISTS;
	}

	T* getConcreteElement() {
		return concrete_element;
	}

	void setConcreteElement(T* element) {
		concrete_element = element;
		container_status = CONCRETE_ELEMENT_EXISTS;
	}

	int getContainersStatus() {
		return container_status;
	}

	int getUserStatus() {
		return user_status;
	}
};

