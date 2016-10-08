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

    m_fSpeed = fInitSpeed;

    CControls controls;
    controls.Init({SDLK_RIGHT, SDLK_LEFT, SDLK_DOWN, SDLK_UP});

    m_pPlayer = new CPlayer();
    m_pPlayer->Init(controls);

    spawnForm();
    m_pPlayer->passForm(m_pForm);

    m_pField = new CField<g_fieldWidth,g_fieldHeight>();
    m_pField->Init(m_pForm->GetSize());

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
        m_pPlayer->Update(m_pField);

        if (!m_pPlayer->GetForm()->isAlive())
        {
            calcPointsAndLevel(m_pPlayer, m_pPlayer->GetDelLines() - Lines);

            spawnForm();
            m_pPlayer->passForm(m_pForm);
        }

        m_pForm->Render();

        m_pField->Update();
        m_pField->Render();

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

        //each level speed of fall increases by + 5
        m_fSpeed += 5*m_pPlayer->GetLevel();
    }

    player->IncreasePoints(player->GetForm()->GetNumBlocksFastDown());

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

    delete(m_pField);
    m_pField = NULL;
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

void CGame::spawnForm()
{
    m_pForm = CForm::create(static_cast<Form>(rand()%7));

    //form starts at the upper range in the middle
    m_pForm->Init(m_fSpeed, g_fieldWidth/2, 1u);
}
