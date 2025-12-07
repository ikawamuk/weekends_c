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
#define MAX_DEPTH 100
#define RR_START_DEPTH 5
#define SAMPLES_PER_PIXCEL 300
#define LIVE_PROBABILITY_MIN 0.05


#endif
