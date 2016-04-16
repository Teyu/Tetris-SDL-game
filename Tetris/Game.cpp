#include "Game.h"

/****************************************************************************************************************************************************
Konstruktor
*/


CGame::CGame()
{

}

/****************************************************************************************************************************************************
Initialisierung
*/


void CGame::Init()
{
	//Initialisiere Zeiger auf Spieler

	//Initialisiere Zeiger auf Form
	//m_pForm = new CForm;

	//Erzeuge eine zufällige Form:
	//Zufallsgenerator: WICHTIG, DIESER SOLLTE NUR EINMAL GENERIERT WERDEN,
	//SONST WIRD IMMER DIE GLEICHE ZUFALLSZAHL ERZEUGT!!!!!!!!!!!!!!!!!

	//TEST:
	time_t t;
	srand( time(&t) );

	m_Level = 0;
	spawnForm();

	//Initialisiere das Feld:
	g_pField->Init(m_pForm->GetSize());

	//Initialisiere zeiger auf das Feld

	//Spiel läuft:
	m_bGameRun = true;

	m_bKeyLock_Move = false;
}

/****************************************************************************************************************************************************
steuert die Instanzen, updatet und rendert sie
*/


void CGame::Run()
{
	while(m_bGameRun == true)
	{
		ProcessEvents();

		g_pFramework->Update();
		g_pFramework->Clear();

		//ProcessFallFaster
		if (g_pFramework->KeyDown(SDLK_DOWN))
		{
			m_pForm->FastDown(true); //Autofire
		}else
		{
			m_pForm->FastDown(false);
		}
			
		//ProcessRotate
		if ((g_pFramework->KeyDown(SDLK_UP)) && (m_bKeyLock_Rotate == false) && (m_FormKind != Square))
		{
			m_pForm->Rotate();

			m_bKeyLock_Rotate = true; //verhindere Autofire
		} 

		//ProcessMove
		if ((g_pFramework->KeyDown(SDLK_RIGHT)) && (m_bKeyLock_Move == true)) //Wird die Taste immer noch gedrückt? Aktiviere Autofire!
		{
			m_pForm->Move(SDLK_RIGHT, true);
		} else if ((g_pFramework->KeyDown(SDLK_LEFT)) && (m_bKeyLock_Move == true))
		{
			m_pForm->Move(SDLK_LEFT, true);
		}

		if (((g_pFramework->KeyDown(SDLK_RIGHT)) || (g_pFramework->KeyDown(SDLK_LEFT))) && (m_bKeyLock_Move == false))
		{
			/**/if (g_pFramework->KeyDown(SDLK_RIGHT))
			{
				m_pForm->Move(SDLK_RIGHT, false);
			} else
			{
				m_pForm->Move(SDLK_LEFT, false);
			}
			m_bKeyLock_Move = true; //verhindere Autofire, beim ersten Drücken!
		}

		//KeyLock lösen, wenn keine Taste gedrückt wird:
		//Wenn dieselbe Variable für Rotate und Move verwendet wird, ginge nicht beides gleichzeitig
		if ((g_pFramework->KeyDown(SDLK_RIGHT) == false) && (g_pFramework->KeyDown(SDLK_LEFT) == false))
		{
			m_bKeyLock_Move = false;
		}
		if (g_pFramework->KeyDown(SDLK_UP) == false)
		{
			m_bKeyLock_Rotate = false;
		}
		
		//bool newForm = false;

		//ProcessFall
		if (m_pForm->Fall() == false)
		{
			spawnForm();
		}

		g_pField->Update(m_Level);
		if (g_pField->GetLines()/10 == (m_Level + 1))
		{
			m_Level++; //Erhöhe das Level, wenn 10 Reihen gelöscht wurden
		}

		m_pForm->Render();
		g_pFramework->Flip();
	}
}

/****************************************************************************************************************************************************
beendet das Spiel
*/


void CGame::Quit()
{
	//Zeiger freigeben (delete) und auf NULL setzen
	delete(m_pForm);
	m_pForm = NULL;

	//TEST:
	cout << g_pPlayer->GetPoints() << endl;
}

/****************************************************************************************************************************************************
prüft ob eine Taste zum beenden des Spiels gedrückt wurde 
*/

void CGame::ProcessEvents()
{
	SDL_Event Event;
		if (SDL_PollEvent ( &Event))
		{
			switch(Event.type)
			{
			case (SDL_QUIT):
				{
					m_bGameRun = false;
				} break;
			case (SDL_KEYDOWN):
				{
					if (Event.key.keysym.sym == SDLK_ESCAPE)
					{
						m_bGameRun = false;
					}
				}break;
			}
		}
}

void CGame::spawnForm() //nicht zweimal hintereinander die gleiche Form?
{
	//spawne neue Form:
	m_FormKind = static_cast<Form>(rand()%7);

	//TEST
	//m_FormKind = S;

			switch(m_FormKind)
			{
			case Bar:
				m_pForm = new CBar; 
				break;
			case Square:
				m_pForm = new CSquare;
				break;
			case L:
				m_pForm = new CL;
				break;
			case J:
				m_pForm = new CJ;
				break;
			case Z:
				m_pForm = new CZ;
				break;
			case S:
				m_pForm = new CS;
				break;
			case T:
				m_pForm = new CT;
				break;
			}

			//Startgeschw. 30
			//Jedes Level + 5
			m_pForm->Init(30.0f + 5*m_Level);
}