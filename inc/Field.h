#ifndef FIELD_H
#define FIELD_H

#include "Framework.h"
#include "Player.h"
#include "Sprite.h"
#include <vector>
#include <array>
#include "Singleton.h"

using namespace std;

#define g_pField CField::Get(10u, 20u) //pointer to single entity of CField

class CField : public TSingleton<CField>
{
public:
    CField(unsigned const fieldW, unsigned const fieldH);
    void Init(unsigned const Bsize);
	void Render();
    void Update();
    bool IsBlock( float fXPix, float fYPix);
    void IncludeBlock( CSprite& Block);

    unsigned const GetFieldW() {return m_fieldW;}
    unsigned const GetFieldH() {return m_fieldH;}

private:

    unsigned const m_fieldW;
    unsigned const m_fieldH;
    unsigned m_Bsize;

    vector<vector<CSprite*>> m_field;

    void EraseLine(unsigned Line);
};

#endif
