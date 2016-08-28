#ifndef FIELD_H
#define FIELD_H

#include "Sprite.h"
#include <vector>
#include <array>

using namespace std;

template<uint width, uint height>
class CField
{
public:
    CField();
    void Init(unsigned const Bsize);
    void Render();
    void Update();
    bool IsBlock( float fXPix, float fYPix);
    void IncludeBlock( CSprite& Block);

    int GetDelLines() {return m_DelLines;}

private:
    unsigned m_Bsize;

    vector<vector<CSprite*>> m_field; //TODO: use array/map or so and instantiate with template arguments

    void EraseLine(unsigned Line);
    int m_DelLines;
};

#include "../src/Field.inl"

#endif
