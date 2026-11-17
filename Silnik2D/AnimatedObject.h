#pragma once
#include "GameObject.h"

class AnimatedObject : public virtual GameObject
{
public:
    virtual ~AnimatedObject() = default;

    virtual void animate() = 0;
};