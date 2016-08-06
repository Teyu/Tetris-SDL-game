#ifndef SPRITE_H
#define SPRITE_H

#include "Framework.h"

class CSprite
{
public: 
    CSprite();
    CSprite(const CSprite& newSprite) :
        m_pScreen(newSprite.m_pScreen), m_pImage(newSprite.m_pImage), m_Rect(newSprite.m_Rect), m_sImageFile(newSprite.m_sImageFile)
    {}
    ~CSprite();

    void Load (const string sFilename);
	
    void SetPos(float fXPos, float fYPos);
    void Render();
    SDL_Rect GetRect() {return m_Rect;}

private:
    SDL_Surface *m_pScreen;
    SDL_Surface *m_pImage;
    SDL_Rect m_Rect;
    string m_sImageFile;
};


#endif
