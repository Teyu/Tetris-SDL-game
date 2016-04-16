#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "Singleton.h"
#include <iostream>
using namespace std;

#define g_pTimer CTimer::Get()

class CTimer : public TSingleton<CTimer>
{
public:
	CTimer ();
	void Update ();
	float GetElapsed () { return m_fElapsed;}

private:
	float m_fElapsed; //vergangene Zeit seit dem letzten Frame
	float m_fCurTime; //aktualle Zeit
	float m_fLastTime; //Zeit des letzten Frames
};

#endif