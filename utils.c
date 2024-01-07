#include "utils.h"

float Lerp(float start, float end, float t) {
    return start + t * (end - start);
}

