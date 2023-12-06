#pragma once

namespace HMath
{
    inline float Lerp(float a, float b, float f)
    {
        return a + f * (b - a);
    }  
}
