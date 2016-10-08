#ifndef FIELD_H
#define FIELD_H

#include "Sprite.h"
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

    CSprite * m_field[width][height];

    void EraseLine(unsigned Line);
    int m_DelLines;
};

#include "../src/Field.inl"

#endif
