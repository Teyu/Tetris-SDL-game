#ifndef BAR_H
#define BAR_H

#include "Form.h"

class CBar: public CForm
{
public:
    virtual void ResetPos(); //to be overwritten
    virtual ~CBar();
};

#endif
