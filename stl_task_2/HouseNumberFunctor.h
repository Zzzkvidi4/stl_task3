#pragma once
class HouseNumberFunctor: public BaseFunctor<Bill>
{
private:
    int house_number;
	bool isInitialized = false;
public:
    HouseNumberFunctor();
    bool operator()(Bill bill);
    void Initialize();
	std::string GetStringValue();
	bool Initialize(std::string value);
    Bill GetValue();
    ~HouseNumberFunctor();
};

