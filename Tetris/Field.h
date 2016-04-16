#ifndef FIELD_H
#define FIELD_H

#include "Framework.h"
#include "Player.h"
#include "Sprite.h"
#include <vector>
#include <array>
#include "Singleton.h"
using namespace std;

//HINWEIS AUF BÖSEN FEHLER:
//Dateien dürfen sich nicht gegenseitig includen!

#define g_pField CField::Get() //Zeiger auf einzige Instanz von CFramework, der in jeder einbindenden Datei verwendet werden kann

class CField : public TSingleton<CField>
{
public:
	CField();
	void Init(int size);
	void Render();
	void Update(int Level);
	bool IsBlock( int XPix, int YPix); 
	int GetLines() { return m_Lines;}
	void IncludeForm( CSprite FormPos);

private:
	int m_size;
	int m_screenW;
	int m_screenH;
	bool m_field[300/15][450/15]; //2-dim arrayfeld, array von Vektoren ging nicht..
	CSprite m_fieldSprites[300/15][450/15]; 
	int m_Lines;

	void EraseLine(int Line);
};

#endif