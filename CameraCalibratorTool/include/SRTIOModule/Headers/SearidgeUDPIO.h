#pragma once

#include "SRTIOModule.h"

class CSearidgeUDPIO : public CSRTIOModule
{
public:
    CSearidgeUDPIO();
    ~CSearidgeUDPIO();
    
    IO_STATE	GetState		();

    bool		Send			(std::string msg);
    bool		Start			(std::string& errorMessage);
    void 		Stop			();

private:
};
