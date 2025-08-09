#pragma once
#include "Personage.h"

class Thomas : public Personage
{
public:
	Thomas();
	~Thomas();

	bool handleInput() override;
private:

};
