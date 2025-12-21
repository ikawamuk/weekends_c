#ifndef DEFINE_H
# define DEFINE_H

#include <float.h>
#include <math.h>

#define ASPECT_RATIO_NUME	4 // 横
#define ASPECT_RATIO_DENO	3 // たて
#define ASPECT_RATIO		(double)ASPECT_RATIO_NUME / (double)ASPECT_RATIO_DENO
#define WINSIZE_X 640 // 640
#define WINSIZE_Y 480 // 480
#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif
#define HIT_T_MIN 1e-3
#define MAX_DEPTH 25
#define RR_START_DEPTH 3 // ロシアンルーレットを始める深さ。
#define SAMPLES_PER_PIXCEL 100 // ここ上げればきれいになるけど遅くなる
#define LIVE_PROBABILITY_MIN 0.05
#define LIGHT_RADIUS 1.0


#endif
