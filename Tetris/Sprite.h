//Ein SPRITE ist eine kleine rechteckige Grafik, die man auf dem Bildschirm anzeigen kann

#ifndef SPRITE_H
#define SPRITE_H

#include "Framework.h"

class CSprite
{
public: 
	CSprite();
	~CSprite();

	void Load (const string sFilename);
	
	void SetPos(float fXPos, float fYPos);
	void Render();
	SDL_Rect GetRect() {return m_Rect;}
	string GetImageFile() { return m_sImageFile;} //TEST

private:
	SDL_Surface *m_pScreen;
	SDL_Surface *m_pImage;
	SDL_Rect m_Rect;
	string m_sImageFile;//TEST

};


#endif