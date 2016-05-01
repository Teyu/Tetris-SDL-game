#ifndef PLAYER_H
#define PLAYER_H

#include "Singleton.h"

#define g_pPlayer CPlayer::Get() 

class CPlayer : public TSingleton<CPlayer>
{
public:
    CPlayer() : m_Points(0), m_level(1)
    { }
    unsigned GetPoints() {return m_Points;}
    void IncreasePoints(unsigned Points) { m_Points += Points;}
    //TEST
    void AddDelLines(unsigned Lines)
    {
        //TODO: throw exception if Lines > 4
        m_DelLines += Lines;
        switch(Lines)
        {
                case 0:
                    break;
                case 1:
                    m_Points += 40*(m_level);
                    break;
                case 2:
                    m_Points += 100*(m_level);
                    break;
                case 3:
                    m_Points += 300*(m_level);
                    break;
                case 4:
                    m_Points += 1200*(m_level);
                    break;
        }

        if (m_DelLines/10 == m_level)
        {
            m_level++;
        }
    }
    unsigned GetLevel() {return m_level;}
    //ENDOFTEST

private:
    unsigned m_Points;
    unsigned m_DelLines;
    unsigned m_level;
};

#endif
