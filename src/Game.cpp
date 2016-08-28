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

    m_bRunGame = true;
}

/****************************************************************************************************************************************************
control, update and render entities
*/

void CGame::Run()
{
    while(m_bRunGame == true)
    {
        ProcessEvents();

        g_pFramework->Update();
        g_pFramework->Clear();

        int Lines = m_pPlayer->GetDelLines();
        m_pPlayer->Update();

        if (!m_pPlayer->GetForm()->isAlive())
        {
            calcPointsAndLevel(m_pPlayer, m_pPlayer->GetDelLines() - Lines);

            //each level speed of fall increases by + 5
            m_pForm = spawnForm(m_fInitSpeed + 5*m_pPlayer->GetLevel());
            m_pPlayer->passForm(m_pForm);
        }

        //m_pForm->Update()
        m_pForm->Render();

        g_pField->Update();
        g_pField->Render();

        //TO BE REMOVED LATER (a class CMenu is yet to be implemented)
        g_pFramework->RenderMenu(m_pPlayer->GetPoints(), m_pPlayer->GetLevel(), m_pPlayer->GetDelLines());

        g_pFramework->Flip();
	}
}


/****************************************************************************************************************************************************
calculate points and level of passed player depending on deleted lines
*/

void CGame::calcPointsAndLevel(CPlayer * const player, int numDelLines)
{
    switch(numDelLines)
    {
        case 0:
            break;
        case 1:
            player->IncreasePoints(40*player->GetLevel());
            break;
        case 2:
            player->IncreasePoints(100*player->GetLevel());
            break;
        case 3:
            player->IncreasePoints(300*player->GetLevel());
            break;
        case 4:
            player->IncreasePoints(1200*player->GetLevel());
            break;
        }

    if (player->GetDelLines()/10 == player->GetLevel())
    {
        player->IncreaseLevel();
    }

    player->IncreasePoints(player->GetForm()->GetNumFastDown());

}

/****************************************************************************************************************************************************
quit the game
*/

void CGame::Quit()
{
    //TEST:
    cout << m_pPlayer->GetPoints() << endl;

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
                m_bRunGame = false;
            } break;
        case (SDL_KEYDOWN):
            {
                if (Event.key.keysym.sym == SDLK_ESCAPE)
                {
                    m_bRunGame = false;
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
    CForm* newForm;
    switch(static_cast<Form>(rand()%7))
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
