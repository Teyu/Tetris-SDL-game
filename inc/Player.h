#ifndef PLAYER_H
#define PLAYER_H

#include "Singleton.h"

#define g_pPlayer CPlayer::Get() 

class CPlayer : public TSingleton<CPlayer>
{
public:
	CPlayer() { m_Points = 0;}
	int GetPoints() {return m_Points;}
	void IncreasePoints(unsigned int Points) { m_Points += Points;}
private:
	int m_Points;
};

#endif
