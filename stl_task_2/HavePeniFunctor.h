#pragma once
class HavePeniFunctor: public BaseFunctor<Bill>
{
private:
	bool isInitialized = false;
    bool hasPeni = false;
public:
    HavePeniFunctor();
    bool operator()(Bill bill);
    void Initialize();
	std::string GetStringValue();
	bool Initialize(std::string value);
    Bill GetValue();
    ~HavePeniFunctor();
};

