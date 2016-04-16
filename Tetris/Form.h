#ifndef FORM_H
#define FORM_H

#include "Sprite.h"
#include "Player.h"
#include "Framework.h"
#include "Timer.h"
#include "Field.h"
#include <array>
using namespace std;

class CForm 
{
public:
	CForm();
	~CForm();
	void Render();
	void Init(float fTempo); 
	virtual void Reset(); //to be overwritten
	bool Fall();
	void Rotate();
	void FastDown(bool bStart);
	void Move(int Dir, bool KeyHold);
	int GetSize() { return m_size;}

protected:
	float m_fXPos;
	float m_fYPos;
	int m_RotPoint;
	int m_size;
	int m_screenW;
	int m_screenH;
	bool m_bIsFallingFast;
	int m_FastFallingPoints;
	float m_AutoMove; 
	CSprite m_Pos[4]; 

private:
	void Move(float dx, float dy);

	float m_fTempo;
	float m_fFastTempo;

};

#endif
