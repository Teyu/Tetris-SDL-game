#include "Field.h"

/****************************************************************************************************************************************************
constructor
*/

CField::CField()
{
}

/****************************************************************************************************************************************************
initialising
*/

void CField::Init(int size)
{
	m_size = size; //hight of a tetris block
	m_screenW = 10*m_size;
	m_screenH = 20*m_size;
	m_Lines = 0;

	//initialising m_field (at the start of the game no blocks are lying on the field yet)
	for (int i=0; i < m_screenW/m_size ; i++)
	{
		for (int j=0; j < m_screenH/m_size; j++)
		{
			m_field[i][j] = false;
		}
	}
}

/****************************************************************************************************************************************************
render lying blocks
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

/****************************************************************************************************************************************************
update the field
*/

void CField::Update(int Level)
{
	//delete full lines
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

	//the player gains points depending on the amount of deleted lines and the current level
	if (LineAmount == 1)
		g_pPlayer->IncreasePoints(40*(Level+1));
	if (LineAmount == 2)
		g_pPlayer->IncreasePoints(100*(Level+1));
	if (LineAmount == 3)
		g_pPlayer->IncreasePoints(300*(Level+1));
	if (LineAmount == 4)
		g_pPlayer->IncreasePoints(1200*(Level+1));

}

/****************************************************************************************************************************************************
return wether stated position has a block 
*/

bool CField::IsBlock( int XPix, int YPix)
{ 
	//legal parameters?
//TODO: display error message only in debug version
	/*try{
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

		//shutdown
		g_pFramework->Quit();
		exit(1);
	}*/

	return m_field[XPix][YPix];
}

/****************************************************************************************************************************************************
include new form into field of lying blocks
*/

void CField::IncludeForm(CSprite FormPos)
{
	int i = FormPos.GetRect().x/m_size;
	int j = (m_screenH - FormPos.GetRect().y)/m_size - 1;

	//loading an image file initialises the block position with default values 
	m_fieldSprites[i][j].Load(FormPos.GetImageFile());
	//set the block position
	m_fieldSprites[i][j].SetPos(FormPos.GetRect().x, FormPos.GetRect().y);

	m_field[i][j] = true;
}

/****************************************************************************************************************************************************
delete a full line of blocks
*/

void CField::EraseLine(int Line)
{
	//overwrite a line with its upper line starting with the regarding line to be deleted
	for (int i = 0; i < m_screenW/m_size; i++)
	{		
		for (int j = Line; j < m_screenH/m_size - 1; j++)
		{
			m_field[i][j] = m_field[i][j+1];
			if (m_field[i][j] == true)
			{
				SDL_Rect tmp = m_fieldSprites[i][j+1].GetRect();
				m_fieldSprites[i][j].Load(m_fieldSprites[i][j+1].GetImageFile());
				m_fieldSprites[i][j].SetPos(tmp.x, tmp.y + m_size);
			}
		}
		m_field[i][m_screenH/m_size -1] = false;
	}
}
