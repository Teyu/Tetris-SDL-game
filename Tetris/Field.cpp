#include "Field.h"

/****************************************************************************************************************************************************
Konstruktor
*/

CField::CField()
{
}

/****************************************************************************************************************************************************
Initialisierung
*/

void CField::Init(int size)
{
	//Initialisiere Membervariablen:
	m_size = size; //Höhe eines Blocks
	m_screenW = 10*m_size;
	m_screenH = 20*m_size;
	m_Lines = 0;

	//Initialisiere m_field (zu Anfang liegen noch keine Blöcke)
	for (int i=0; i < m_screenW/m_size ; i++)
	{
		for (int j=0; j < m_screenH/m_size; j++)
		{
			m_field[i][j] = false;
		}
	}
}

/****************************************************************************************************************************************************
rendert das Feld
*/

void CField::Render()
{
	for (int i=0; i < m_screenW/m_size ; i++)
	{
		for (int j=0; j < m_screenH/m_size; j++)
		{
			if (m_field[i][j] == true)
			{
				m_fieldSprites[i][j].Render();
			}
		}
	}

}

void CField::Update(int Level)
{
	//Wenn eine Reihe voll ist, lösche diese: Hier würde eine Klasseninterne arrayvariable für die Reihen Sinn machen!
	int LineCounter = 0;
	int LineAmount = 0;

	for (int j =  0; j < m_screenH/m_size; j++)
	{
		for (int k = 0; k < m_screenW/m_size; k++)
		{
			if (m_field[k][(m_screenH/m_size - j) - 1] == true)
				LineCounter++;
		}
		if (LineCounter == (m_screenW/m_size))
		{
			EraseLine((m_screenH/m_size - j) - 1);
			m_Lines++;
			LineAmount++;
		}
		LineCounter = 0;
	}

	//Der Spieler bekommt Punkte, abhängig von der Anzahl gelöschter Reihen und dem Level:
	if (LineAmount == 1)
		g_pPlayer->IncreasePoints(40*(Level+1));
	if (LineAmount == 2)
		g_pPlayer->IncreasePoints(100*(Level+1));
	if (LineAmount == 3)
		g_pPlayer->IncreasePoints(300*(Level+1));
	if (LineAmount == 4)
		g_pPlayer->IncreasePoints(1200*(Level+1));

}

bool CField::IsBlock( int XPix, int YPix)
{ 
	//legale Übergabeparameter?
	/*if (XPix < 0)
	{
		cout << "Tried to attempt Field-Position. XPix Position negative!" << endl;
	} else if (XPix >= m_screenW/m_size)
	{
		cout <<  "Tried to attempt Field-Position. XPix Position larger than screen!" << endl;
	}

	if (YPix < 0)
	{
		cout << "Tried to attempt Field-Position. YPix Position negative!" << endl;
	} else if (YPix >= m_screenH/m_size)
	{
		cout <<  "Tried to attempt Field-Position. YPix larger than screen!" << endl;
	}*/

	//TEST:
	try{
		if (XPix < 0)
		{
			throw "Tried to attempt Field-Position. XPix Position negative!";
		} else if (XPix > m_screenW/m_size)
		{
			throw  "Tried to attempt Field-Position. XPix Position larger than screen!";
		}

		if (YPix < 0)
		{
			throw "Tried to attempt Field-Position. YPix Position negative!";
		} else if (YPix > m_screenH/m_size)
		{
			throw "Tried to attempt Field-Position. YPix larger than screen!";
		}
	}catch(char* msg){
		cerr << msg << endl;
		//Programm beenden:

		g_pFramework->Quit();
		exit(1);
	}

	return m_field[XPix][YPix];
}

/****************************************************************************************************************************************************
Nimmt die übergebene Form ins Blockfeld auf
*/

void CField::IncludeForm(CSprite FormPos)
{
	int i = FormPos.GetRect().x/m_size;
	int j = (m_screenH - FormPos.GetRect().y)/m_size - 1;

	//Zuerst muss das Bild geladen werde, denn hierbei wird die Position mit Defaultwerten initialisiert
	m_fieldSprites[i][j].Load(FormPos.GetImageFile());
	//Dann setze die Position von Rect:
	m_fieldSprites[i][j].SetPos(FormPos.GetRect().x, FormPos.GetRect().y);

	//Zuletzt setze die entsprechende Position im Feld auf true
	m_field[i][j] = true;

	//Wenn eine Reihe voll ist, lösche diese: Hier würde eine Klasseninterne arrayvariable für die Reihen Sinn machen!
	//PROBLEM:
	//Die Reihe wird auch gelöscht, wenn der Rest der Form noch gar nicht "includet" wurde. 
	//Dieser wird dann nachträglich hinzugefügt, und befindet sich dann an der falschen Position
	/*int LineCounter = 0;
	for (int k = 0; k < m_screenW/m_size; k++)
	{
		if (m_field[k][j] == true)
			LineCounter++;
	}
	if (LineCounter == (m_screenW/m_size))
		EraseLine(j);*/

	//TEST
	/*
	for (int j = m_screenH/m_size - 1; j >= 0; j--)
	{
		for (int i = 0; i < m_screenW/m_size; i++)
		{
			cout << m_field[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;*/

	//blöderweise klappt es nicht ein Sprite in eine Membervariable zu kopieren :-/
}

void CField::EraseLine(int Line)
{
	//Lösche die Reihe:
	/*for (int i = 0; i < m_screenW/m_size; i++)
	{
		m_field[i][Line] = false;
	}*/

	//Lasse die oberen Reihen nachfallen:
	for (int i = 0; i < m_screenW/m_size; i++)
	{		
		for (int j = Line; j < m_screenH/m_size - 1; j++)
		{
			//Der untere bekommt den Wert vom oberen:
			m_field[i][j] = m_field[i][j+1];
			if (m_field[i][j] == true)
			{
				SDL_Rect tmp = m_fieldSprites[i][j+1].GetRect();
				m_fieldSprites[i][j].Load(m_fieldSprites[i][j+1].GetImageFile());
				m_fieldSprites[i][j].SetPos(tmp.x, tmp.y + m_size);
			}
		}
		m_field[i][m_screenH/m_size -1] = false; //ganz oben ist nach dem löschen nie eine linie
	}

	//TEST:
	/*for (int j = m_screenH/m_size - 1; j >= 0; j--)
	{
		for (int i = 0; i < m_screenW/m_size; i++)
		{
			cout << m_field[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;*/
}