#ifndef CONTROLS_H
#define CONTROLS_H

#include "SDL.h"
#include "TetrisForms.h"

struct KeySettings
{
    uint MoveRight;
    uint MoveLeft;
    uint FastDown;
    uint Rotate;
};

class CControls
{
public:
    void Init(KeySettings keys)
    {
        Keys = keys;
    }

    template<uint width, uint height>
    void ProcessRotate(CForm &form, CField<width, height> &field);
    template<uint width, uint height>
    void ProcessMove(CForm &form, CField<width, height> &field);
    template<uint width, uint height>
    void ProcessFastDown(CForm &form, CField<width, height> &field);

    KeySettings getKeySettings() { return Keys;}

private:
    template<uint width, uint height>
    void ProcessMove(uint KeyID, bool &bKeyLockMove, float &fAutoMoveCount, CForm &form, CField<width, height> &field);

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
