#include "Game.h"

/****************************************************************************************************************************************************
constructor
*/


CGame::CGame()
{

}

/****************************************************************************************************************************************************
initialise
*/


void CGame::Init()
{
	//seed random generator
	time_t t;
	srand( time(&t) );

	m_Level = 0;
	spawnForm();

	g_pField->Init(m_pForm->GetSize());

	m_bGameRun = true;

	m_bKeyLock_Move = false;
}

/****************************************************************************************************************************************************
control, update and render entities
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
			m_pForm->FastDown(true); //autofire
		}else
		{
			m_pForm->FastDown(false);
		}
			
		//ProcessRotate
		if ((g_pFramework->KeyDown(SDLK_UP)) && (m_bKeyLock_Rotate == false) && (m_FormKind != Square))
		{
			m_pForm->Rotate();

			m_bKeyLock_Rotate = true; //lock autofire
		} 

		//ProcessMove
		if ((g_pFramework->KeyDown(SDLK_RIGHT)) && (m_bKeyLock_Move == true)) //autofire
		{
			m_pForm->Move(SDLK_RIGHT, true);
		} else if ((g_pFramework->KeyDown(SDLK_LEFT)) && (m_bKeyLock_Move == true))
		{
			m_pForm->Move(SDLK_LEFT, true);
		}

		if (((g_pFramework->KeyDown(SDLK_RIGHT)) || (g_pFramework->KeyDown(SDLK_LEFT))) && (m_bKeyLock_Move == false))
		{
			if (g_pFramework->KeyDown(SDLK_RIGHT))
			{
				m_pForm->Move(SDLK_RIGHT, false);
			} else
			{
				m_pForm->Move(SDLK_LEFT, false);
			}
			m_bKeyLock_Move = true; //prevent autofire when first pressing move button
		}

		if ((g_pFramework->KeyDown(SDLK_RIGHT) == false) && (g_pFramework->KeyDown(SDLK_LEFT) == false))
		{
			m_bKeyLock_Move = false;
		}
		if (g_pFramework->KeyDown(SDLK_UP) == false)
		{
			m_bKeyLock_Rotate = false;
		}

		//ProcessFall
		if (m_pForm->Fall() == false)
		{
			spawnForm();
		}

		g_pField->Update(m_Level);
		if (g_pField->GetLines()/10 == (m_Level + 1))
		{
			m_Level++; 
		}

		m_pForm->Render();
		g_pFramework->Flip();
	}
}

/****************************************************************************************************************************************************
quit the game
*/


void CGame::Quit()
{
	delete(m_pForm);
	m_pForm = NULL;

	//TEST:
	cout << g_pPlayer->GetPoints() << endl;
}

/****************************************************************************************************************************************************
verify if a button is pressed to quit the game 
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

/****************************************************************************************************************************************************
spawn new form
*/

void CGame::spawnForm() 
{
	m_FormKind = static_cast<Form>(rand()%7);

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

			//start tempo = 30
			//each level + 5
			m_pForm->Init(30.0f + 5*m_Level);
}