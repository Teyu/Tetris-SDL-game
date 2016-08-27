#include "Game.h"

/****************************************************************************************************************************************************
constructor
*/

CGame::CGame()
{}

/****************************************************************************************************************************************************
initialise
*/

void CGame::Init(float fInitSpeed)
{
	//seed random generator
	time_t t;
	srand( time(&t) );

    m_fInitSpeed = fInitSpeed;

    m_pPlayer = new CPlayer();

    m_pForm = spawnForm(m_fInitSpeed);
    m_pPlayer->passForm(m_pForm);

    g_pField->Init(m_pForm->GetSize());

    m_bGameRun = true;
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

        int Lines = m_pPlayer->GetDelLines();
        m_pPlayer->Update();

        if (!m_pPlayer->GetForm()->isAlive())
        {
            Lines = m_pPlayer->GetDelLines() - Lines;
            switch(Lines)
            {
                case 0:
                    break;
                case 1:
                    m_pPlayer->IncreasePoints(40*m_pPlayer->GetLevel());
                    break;
                case 2:
                    m_pPlayer->IncreasePoints(100*m_pPlayer->GetLevel());
                    break;
                case 3:
                    m_pPlayer->IncreasePoints(300*m_pPlayer->GetLevel());
                    break;
                case 4:
                    m_pPlayer->IncreasePoints(1200*m_pPlayer->GetLevel());
                    break;
                }

            if (m_pPlayer->GetDelLines()/10 == m_pPlayer->GetLevel())
            {
                m_pPlayer->IncreaseLevel();
            }

            m_pPlayer->IncreasePoints(m_pPlayer->GetForm()->GetNumFastDown());

            //each level speed of fall increases by + 5
            m_pForm = spawnForm(m_fInitSpeed + 5*m_pPlayer->GetLevel());
            m_pPlayer->passForm(m_pForm);
        }

        m_pForm->Render();

        g_pField->Update();
        g_pField->Render();

        //TO BE REMOVED LATER (a class CMenu is yet to be implemented)
        g_pFramework->RenderMenu(m_pPlayer->GetPoints(), m_pPlayer->GetLevel(), m_pPlayer->GetDelLines());

        g_pFramework->Flip();
	}
}

/****************************************************************************************************************************************************
quit the game
*/

void CGame::Quit()
{
    //TEST:
    cout << "Points: " << m_pPlayer->GetPoints() << endl;

    delete(m_pForm);
    m_pForm = NULL;

    delete(m_pPlayer);
    m_pPlayer = NULL;
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

CForm* CGame::spawnForm(float fSpeedOfFall)
{
    m_TetrisForm = static_cast<Form>(rand()%7);
    CForm* newForm;

            switch(m_TetrisForm)
			{
			case Bar:
                newForm = new CBar;
				break;
			case Square:
                newForm = new CSquare;
				break;
			case L:
                newForm = new CL;
				break;
			case J:
                newForm = new CJ;
				break;
			case Z:
                newForm = new CZ;
				break;
			case S:
                newForm = new CS;
				break;
			case T:
                newForm = new CT;
				break;
			}

    newForm->Init(fSpeedOfFall);

    return newForm;
}
