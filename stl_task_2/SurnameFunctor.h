#pragma once
#include "BaseFunctor.h"
#include "Bill.h"

class SurnameFunctor : public BaseFunctor<Bill>
{
private:
	bool isInitialized = false;
    std::string surname;
public:
    SurnameFunctor();
    bool operator()(Bill bill);
    void Initialize();
	std::string GetStringValue();
	bool Initialize(std::string value);
    Bill GetValue();
    ~SurnameFunctor();
};

