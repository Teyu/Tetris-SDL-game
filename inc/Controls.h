#ifndef CONTROLS_H
#define CONTROLS_H

#include "SDL.h"
#include "TetrisForms.h"

struct KeySettings
{
    uint32_t MoveRight;
    uint32_t MoveLeft;
    uint32_t FastDown;
    uint32_t Rotate;
};

class CControls
{
public:
    void Init (KeySettings keys)
    {
        Keys = keys;
    }

    template<uint32_t width, uint32_t height>
    void ProcessRotate (CForm &form, CField<width, height> &field);
    template<uint32_t width, uint32_t height>
    void ProcessMove (CForm &form, CField<width, height> &field);
    template<uint32_t width, uint32_t height>
    void ProcessFastDown (CForm &form, CField<width, height> &field);

    KeySettings getKeySettings()
    {
        return Keys;
    }

private:
    template<uint32_t width, uint32_t height>
    void ProcessMove (uint32_t KeyID, bool &bKeyLockMove, float &fAutoMoveCount, CForm &form, CField<width, height> &field);

    KeySettings Keys;

    bool bKeyLock_MoveR = false;
    bool bKeyLock_MoveL = false;
    bool bKeyLock_Rotate = false;
    bool bKeyLock_FastDown = false;

    float fAutoMoveCnt_l = 0.0f;
    float fAutoMoveCnt_r = 0.0f;
};

#include "../src/Controls.inl"

#endif
