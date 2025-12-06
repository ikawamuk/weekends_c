#ifndef DEFINE_H
# define DEFINE_H

#include <float.h>
#include <math.h>

#define ASPECT_RATIO_NUME	16 // 横
#define ASPECT_RATIO_DENO	9 // たて
#define ASPECT_RATIO		(double)ASPECT_RATIO_NUME / (double)ASPECT_RATIO_DENO
#define WINSIZE_X 540
#define WINSIZE_Y ((WINSIZE_X) / (ASPECT_RATIO_NUME) * (ASPECT_RATIO_DENO))
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#define HIT_T_MIN 1e-3

#endif
