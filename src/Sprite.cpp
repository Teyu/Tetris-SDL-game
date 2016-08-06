#include "Sprite.h"

/****************************************************************************************************************************************************
constructor
*/

CSprite::CSprite()
{
	m_pScreen = g_pFramework->GetScreen();
	m_pImage = NULL;
}

/****************************************************************************************************************************************************
destructor
*/

CSprite::~CSprite()
{
	SDL_FreeSurface (m_pImage);
}

/****************************************************************************************************************************************************
load an image file
*/

void CSprite::Load( const string sFilename)
{
	m_sImageFile = sFilename;

	m_pImage = SDL_LoadBMP( sFilename.c_str() );

	if (m_pImage == NULL)
	{
		cout << "Fehler beim Laden von: " << sFilename.c_str();
		cout << endl;
		cout << "Fehlermeldung: " << SDL_GetError() << endl;

		g_pFramework->Quit();
		exit(1);
	}

	m_Rect.x = -1; //this way an exception will be thrown if position hasn't been set 
	m_Rect.y = -1;
	m_Rect.w = m_pImage->w;
	m_Rect.h = m_pImage->h;
}

/****************************************************************************************************************************************************
set the position
*/

void CSprite::SetPos( float fXPos, float fYPos)
{
//TODO: thow error only in debug version 
	/*try{ 
		if (fXPos< 0)
		{
			throw "Tried to set Sprite Position. fXPos Position negative!" ;
		}else if (fXPos >= 300 )//g_pFramework->GetScreenWidth()
		{
			throw "Tried to set Sprite Position. fXPos larger than screen!";
		}
		if (fYPos < 0)
		{
			throw "Tried to set Sprite Position. fYPos Position negative!";
		}else if (fYPos > g_pFramework->GetScreenHeight())
		{
			throw "Tried to set Sprite Position. fYPos larger than screen!";
		}
	}catch(char* msg){
		cerr << msg << endl;
		
		g_pFramework->Quit();
		exit(1);
	}	*/

	//sprite moves only when next integer is exceeded. This way its easier to control the speed of movement 
	m_Rect.x = static_cast<int>(fXPos);
	m_Rect.y = static_cast<int>(fYPos);
}

/****************************************************************************************************************************************************
render 
*/

void CSprite::Render()
{
	try{
		if ((m_Rect.x < 0) || (m_Rect.y < 0))
		{
            throw "could not render sprite, invalid position";
		}
	}catch(char* msg){
		cerr << msg << endl;
		
		g_pFramework->Quit();
		exit(1);
	}	

	SDL_BlitSurface(m_pImage, NULL, m_pScreen, &m_Rect);
}
