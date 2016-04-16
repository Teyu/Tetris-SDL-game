#include "Sprite.h"

CSprite::CSprite()
{
	m_pScreen = g_pFramework->GetScreen();
	m_pImage = NULL;
}

CSprite::~CSprite()
{
	//Um die Freigabe des Zeigers auf das Framework kümmert sich bereits die KSDL selbst!! 

	//Der Zeiger muss den reservierten Speicher, auf den er zeigt, wieder frei geben:
	SDL_FreeSurface (m_pImage);
}

void CSprite::Load( const string sFilename)
{
	//TEST:
	m_sImageFile = sFilename;

	//Bitmap laden:
	m_pImage = SDL_LoadBMP( sFilename.c_str() );

	//prüfen, ob alles geklappt hat:
	if (m_pImage == NULL)
	{
		cout << "Fehler beim Laden von: " << sFilename.c_str();
		cout << endl;
		cout << "Fehlermeldung: " << SDL_GetError() << endl;

		g_pFramework->Quit();
		//Spiel beenden:
		exit(1); //Diese Funktion beendet an jeder Stelle das gesamte Programm!
	}

	//Rect initialisieren:
	m_Rect.x = -1; //setze nicht legale Werte als default-Werte um abzufragen, 
	//ob die Position von CSprite gesetzt wurde, und wenn nicht eine Exception zu werfen
	m_Rect.y = -1;
	m_Rect.w = m_pImage->w;
	m_Rect.h = m_pImage->h;
}

void CSprite::SetPos( float fXPos, float fYPos)
{
	//Warum float statt int für die Parameter?
	// -	Die Bewegung des Sprites hängt von der festgelegten Geschwindigkeit ab. Es gibt hierfür zwei Mögichkeiten:
	//		Entweder man verwendet einen Zähler und ändert die Position des Sprites nachdem ein bestimmter Wert erreicht wurde,
	//		oder man steuert die Bewegung dadurch, dass sich das Sprite erst bewegt, wenn die nächste ganze Zahl erreicht wurde.
	//		Ersteres ist umständlicher!

	//TEST:
	//Verwende Fehlerbehandlung, die nicht in der Release-Version ausgeführt wird!
	/*try{ 

		//legale Übergabeparameter?
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
		//Programm beenden:

		g_pFramework->Quit();
		exit(1);
	}	*/

	m_Rect.x = static_cast<int>(fXPos);
	m_Rect.y = static_cast<int>(fYPos);
}

void CSprite::Render()
{
	//TEST:
	try{
		if ((m_Rect.x < 0) || (m_Rect.y < 0)){
			throw "could not render sprite, position has not yet been set";
		}
	}catch(char* msg){
		cerr << msg << endl;
		//Programm beenden:

		g_pFramework->Quit();
		exit(1);
	}	

	//Diese Funktion lädt ein Surface in den Backbuffer, also m_pScreen.
	//Durch den Aufruf der Funktion Flip, wird dieser dann sichtbar!
	// 2.Parameter: Ausschnitt der kopiert werden soll (Dies macht nur bei Animationen für die jew. Animationsphase Sinn)
	// 4.Parameter: Bestimmt die Position auf der ZielSurface
	SDL_BlitSurface(m_pImage, NULL, m_pScreen, &m_Rect);
}