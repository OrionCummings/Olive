#pragma once
#ifndef H_HELPERS
#define H_HELPERS

#include <raylib.h>

static inline Color ColorDim(const Color C, float Factor){
    if (Factor < 0.0f || Factor > 1.0f) return C;
    Color R = C;
    R.a = C.a * Factor;
    return R;
}

static inline bool IsVector2Zero(const Vector2 V) {
    return (V.x == 0.0f && V.y == 0.0f);
}

#endif