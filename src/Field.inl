
/****************************************************************************************************************************************************
constructor
*/
template<uint width, uint height>
CField<width,height>::CField()
{
}

/****************************************************************************************************************************************************
initialising
*/

template<uint width, uint height>
void CField<width,height>::Init(unsigned const Bsize)
{
    m_Bsize = Bsize;
    m_DelLines = 0;

    //initialising m_field
    for (size_t i=0; i < width ; i++)
    {
        for (size_t j=0; j < height; j++)
        {
            m_field[i][j] = nullptr;
        }
    }
}

/****************************************************************************************************************************************************
render lying blocks
*/

template<uint width, uint height>
void CField<width,height>::Render()
{
    for (size_t i=0; i < width ; i++)
    {
        for (size_t j=0; j < height; j++)
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

template<uint width, uint height>
void CField<width,height>::Update()
{
    //unsigned DelLines = 0;

    for (size_t j =  0; j < height; j++)
    {
        for (size_t k = 0; k < width; k++)
        {
           if (m_field[k][j] == nullptr)
               goto continue_j;
        }
        EraseLine(j);
        m_DelLines++;

        continue_j:;
    }
}

/****************************************************************************************************************************************************
return wether stated position has a block, parameters out of range are allowed : returns false (there is no block)
*/

template<uint width, uint height>
bool CField<width,height>::IsBlock( float fXPix, float fYPix)
{
    if ((fXPix < 0.0f) || (fXPix >= width*m_Bsize) || (fYPix < 0.0f) || (fYPix >= height*m_Bsize))
        return false;

    return (m_field[static_cast<uint>(fXPix/m_Bsize)][static_cast<uint>(fYPix/m_Bsize)] != nullptr);
}

/****************************************************************************************************************************************************
include block into field of lying blocks
*/

template<uint width, uint height>
void CField<width,height>::IncludeBlock(CSprite& Block)
{
    m_field[Block.GetRect().x/m_Bsize][Block.GetRect().y/m_Bsize] = new CSprite(Block);
}

/****************************************************************************************************************************************************
delete a full line of blocks
*/

template<uint width, uint height>
void CField<width,height>::EraseLine(unsigned Line)
{
    //overwrite a line with its upper line starting with the regarding line to be deleted
    for (size_t i = 0; i < width; i++)
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
