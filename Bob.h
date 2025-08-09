#pragma once
#include "Personage.h"

class Bob : public Personage
{
public:
	Bob();
	~Bob();

	bool handleInput() override;
private:

};
