#ifndef DEFINE_H
# define DEFINE_H

#include <float.h>
#include <math.h>

#define ASPECT_RATIO_NUME	4 // 横
#define ASPECT_RATIO_DENO	3 // たて
#define ASPECT_RATIO		(double)ASPECT_RATIO_NUME / (double)ASPECT_RATIO_DENO
#define WINSIZE_X 1200 // 640
#define WINSIZE_Y 900 // 480
#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif
#define HIT_T_MIN 1e-3
#define MAX_DEPTH 100
#define RR_START_DEPTH 10 // ロシアンルーレットを始める深さ。
#define SAMPLES_PER_PIXCEL 50 // アンチエイリアシングのサンプル数、pdfの功で結構少なくてもいい感じ
#define LIVE_PROBABILITY_MIN 0.05
#define TILE_SIZE 20 // 一つのマップを縦横それぞれなん分割するか。多いほど細かい。せいぜい8~30が適正なので固定値で良い
#define LIGHT_RADIUS 1.0
#define LENS_RADIUS 0.0 // 0.0なら焦点ボケ無し。~1.0
#define FOCUS_DIST 1.0 // 1.0ならもともとと同じ。目標物体との距離
#define LIGHT_STRENGTH 6000000000

#include <stdbool.h>
extern bool	is_phong;
// ひとまずグローバル変数でis_phongかを管理
// ./weekend test.rt p
// のように２つ目の引数を持たせたときphong modeになる

#endif
