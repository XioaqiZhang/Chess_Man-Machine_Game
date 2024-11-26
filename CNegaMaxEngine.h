#ifndef CNEGAMAXENGINE_H
#define CNEGAMAXENGINE_H

#include "CSearchEngine.h"

class CNegaMaxEngine : public CSearchEngine
{
public:
    CNegaMaxEngine();
    virtual ~CNegaMaxEngine();
    virtual void SearchAGoodMove(BYTE position[10][9]);
protected:
    int NegaMax(int depth);
};

#endif // CNEGAMAXENGINE_H
