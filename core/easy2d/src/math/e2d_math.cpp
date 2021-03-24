#include "e2d_math.h"

/* Easy2D */
using namespace Easy2D;

/* MATH */
const float Math::PI = 3.1415926535f;
const float Math::PI2 = 6.2831853071796f;
const float Math::PIOVER180 = 0.0174532925f;
const float Math::G180OVERPI = 57.2957795130f;
void  Math::seedRandom(unsigned int seed)
{
    if (!seed)
        seed = (unsigned int)std::time(NULL);
    srand(seed);
}

float Math::random()
{
    return (float)rand() / (float)RAND_MAX;
}

float Math::randomRange(float min, float max)
{
    return ((float)rand() / (float)RAND_MAX) * (max - min) + min;
}
