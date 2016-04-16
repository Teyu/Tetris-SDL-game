#ifndef GAME_H
#define GAME_H

#include "Framework.h"
#include "Bar.h"
#include "Square.h"
#include "L.h"
#include "J.h"
#include "Z.h"
#include "S.h"
#include "T.h"
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

	//Zeiger auf Spieler
	//Zeiger auf eine Form
	CForm *m_pForm; //WICHTIG: Ohne Zeiger könnte man nicht realisieren in m_Form eine bel. abgel. Klasse von CForm zu speichern!!!
	enum Form{Bar, Square, L, J, Z, S, T}; 
	Form m_FormKind;
	bool m_bGameRun;
	bool m_bKeyLock_Move;
	bool m_bKeyLock_Rotate;
	int m_Level;
};

#endif