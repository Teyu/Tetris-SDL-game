#include "Field.h"

/****************************************************************************************************************************************************
constructor
*/

CField::CField(const unsigned fieldW, const unsigned fieldH) : m_fieldW(fieldW), m_fieldH(fieldH)
{
}

/****************************************************************************************************************************************************
initialising
*/

void CField::Init(unsigned const Bsize)
{
    m_Bsize = Bsize;

    //initialising m_field
    m_field.resize(m_fieldW);
    for (size_t i=0; i < m_fieldW ; i++)
        {
            m_field[i].resize(m_fieldH);
            for (size_t j=0; j < m_fieldH; j++)
            {
                m_field[i][j] = nullptr;
            }
        }
}

/****************************************************************************************************************************************************
render lying blocks
*/

void CField::Render()
{
    for (size_t i=0; i < m_fieldW ; i++)
    {
        for (size_t j=0; j < m_fieldH; j++)
        {
            if (m_field[i][j] != nullptr)
            {
                m_field[i][j]->Render();
            }
        }
    }

}

/****************************************************************************************************************************************************
update the field: delete full lines
*/

void CField::Update()
{
    unsigned DelLines = 0;

    for (size_t j =  0; j < m_fieldH; j++)
    {
        for (size_t k = 0; k < m_fieldW; k++)
        {
           if (m_field[k][j] == nullptr)
               goto continue_j;
        }
        EraseLine(j);
        DelLines++;

        continue_j:;
    }

    g_pPlayer->AddDelLines(DelLines);
}

/****************************************************************************************************************************************************
return wether stated position has a block, parameters out of range are allowed : returns false (there is no block)
*/

bool CField::IsBlock( float fXPix, float fYPix)
{
    if ((fXPix < 0.0f) || (fXPix >= m_fieldW*m_Bsize) || (fYPix < 0.0f) || (fYPix >= m_fieldH*m_Bsize))
        return false;

    return (m_field[unsigned(fXPix/m_Bsize)][unsigned(fYPix/m_Bsize)] == nullptr) ? false : true;
}

/****************************************************************************************************************************************************
include block into field of lying blocks
*/

void CField::IncludeBlock(CSprite& Block)
{
    m_field[Block.GetRect().x/m_Bsize][Block.GetRect().y/m_Bsize] = new CSprite(Block);
}

/****************************************************************************************************************************************************
delete a full line of blocks
*/

void CField::EraseLine(unsigned Line)
{
    //overwrite a line with its upper line starting with the regarding line to be deleted
    for (size_t i = 0; i < m_fieldW; i++)
        {
            for (size_t j = Line; j > 1; j--) //y-axis is inverted
            {
                m_field[i][j] = m_field[i][j-1];
                if (m_field[i][j] != nullptr)
                {
                    SDL_Rect tmp = m_field[i][j]->GetRect();
                    m_field[i][j]->SetPos(tmp.x, tmp.y + m_Bsize);
                }
            }
            delete(m_field[i][0]);
            m_field[i][0] = nullptr;
        }
}
