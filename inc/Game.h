#ifndef GAME_H
#define GAME_H

#include "Framework.h"
#include "Form.h"
#include <ctime>
#include <cstdlib>

class CGame
{
public:
	CGame();

	void Init();
	void Run();
	void Quit();

private:
	void ProcessEvents();
	void spawnForm();

	CForm *m_pForm; 
	enum Form{Bar, Square, L, J, Z, S, T}; 
	Form m_FormKind;

	bool m_bGameRun;
	bool m_bKeyLock_Move;
	bool m_bKeyLock_Rotate;
    bool m_bKeyLock_Fall;

    float m_fAutoMoveCount_l;
    float m_fAutoMoveCount_r;
    const float buffer = 0.25f;
};

#endif
