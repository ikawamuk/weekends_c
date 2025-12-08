#include <stdlib.h>
#include "define.h"
#include "vec3.h"
#include "pixcel.h"



/*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ガイド付き＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*/

/* 5x5 guided max filter */
static const double SIGMA_N = 0.12; /* normal 感度 */
static const double SIGMA_A = 0.08; /* albedo 感度 */
static const double SIGMA_L = 0.12; /* luma 感度 */
static const double THRESH   = 1e-6;/* 重み閾値 */

static inline int clamp_int(int v, int lo, int hi) {
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}
static inline double dot_v3(const t_vec3 *a, const t_vec3 *b) {
    return a->x*b->x + a->y*b->y + a->z*b->z;
}
static inline double luma_of(const t_color *c) {
    return 0.2126 * c->x + 0.7152 * c->y + 0.0722 * c->z;
}

/* 5x5 に拡張したガイド付き max filter（pixcel_arr は WINSIZE_X×WINSIZE_Y） */
static t_color max_filter_with_guide(const t_pixcel *pixcel_arr, int x, int y)
{
    /* パスカル係数ベクトル（5要素）を外積して 5x5 カーネルとする */
    const double p[5] = {1.0, 4.0, 6.0, 4.0, 1.0};
    const double Ksum = 256.0; /* (1+4+6+4+1)^2 = 16^2 = 256 */

    int W = WINSIZE_X;
    int H = WINSIZE_Y;
    int idx_c = y * W + x;
    const t_pixcel *pc = &pixcel_arr[idx_c];

    double best_score = -DBL_MAX;
    t_color best_color = pc->color; /* フォールバックは自分自身 */

    double self_luma = luma_of(&pc->color);
    const t_vec3 *n_c = &pc->normal;
    const t_color *a_c = &pc->albedo;

    for (int oy = -2; oy <= 2; ++oy) {
        for (int ox = -2; ox <= 2; ++ox) {
            int sx = clamp_int(x + ox, 0, W - 1);
            int sy = clamp_int(y + oy, 0, H - 1);
            int idx = sy * W + sx;
            const t_pixcel *pn = &pixcel_arr[idx];

            /* 空間重み（p 外積を利用） */
            int ix = ox + 2;
            int iy = oy + 2;
            double ws = (p[ix] * p[iy]) / Ksum; /* 正規化済み */

            /* 法線重み */
            double dotn = dot_v3(n_c, &pn->normal);
            if (dotn < -1.0) dotn = -1.0;
            if (dotn >  1.0) dotn =  1.0;
            double wn = exp( - (1.0 - dotn) / SIGMA_N );

            /* アルベド差（L2） */
            double dr = a_c->x - pn->albedo.x;
            double dg = a_c->y - pn->albedo.y;
            double db = a_c->z - pn->albedo.z;
            double da = sqrt(dr*dr + dg*dg + db*db);
            double wa = exp( - da / SIGMA_A );

            /* 輝度差 */
            double luma_n = luma_of(&pn->color);
            double ll = fabs(self_luma - luma_n);
            double wl = exp( - ll / SIGMA_L );

            double w = ws * wn * wa * wl;
            if (w < THRESH) continue;

            /* スコア定義（明るさ重視の max） */
            double score = luma_n * w;

            if (score > best_score) {
                best_score = score;
                best_color = pn->color;
            }
        }
    }

    return best_color;
}

/*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*/


/*
＝＝＝＝＝＝＝＝＝＝＝＝＝最大値ファイルター＝＝＝＝＝＝＝＝＝＝＝＝

static int clamp_int(int v, int lo, int hi) {
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}

static void sort9(double a[9]) {
    for (int i = 1; i < 9; ++i) {
        double key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            --j;
        }
        a[j + 1] = key;
    }
}

static t_color	max_filter(t_pixcel *pixcel_arr, int x, int y)
{
	int dx[9] = {-1,0,1,-1,0,1,-1,0,1};
	int dy[9] = {-1,-1,-1,0,0,0,1,1,1};
	double buf_r[9], buf_g[9], buf_b[9];
	for (int i = 0; i < 9; i++)
	{
		int nx = clamp_int(x + dx[i], 0, WINSIZE_X - 1);
		int ny = clamp_int(y + dy[i], 0, WINSIZE_Y - 1);
		int idx = ny * WINSIZE_X + nx;
		double w;
		buf_r[i] = pixcel_arr[idx].color.x * w;
		buf_g[i] = pixcel_arr[idx].color.y * w;
		buf_b[i] = pixcel_arr[idx].color.z * w;
	}
	sort9(buf_r);
	sort9(buf_g);
	sort9(buf_b);
	// return (construct_color(buf_r[4], buf_g[4], buf_b[4]));
	return (construct_color(buf_r[8], buf_g[8], buf_b[8]));
}

＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*/


t_color	*post_proccess(t_pixcel *pixcel_arr)
{
	
	t_color	*color_arr = malloc(PIXCELS_NUM * sizeof(t_color));

	for (int y = 0; y < WINSIZE_Y; y++)
	{
		int yy = y * WINSIZE_X;
		for (int x = 0;  x < WINSIZE_X; x++)
		{
			// color_arr[yy + x] = pixcel_arr[yy + x].color;　後処理無し
			color_arr[yy + x] = max_filter_with_guide(pixcel_arr, x, y);
			
		}
	}
	free(pixcel_arr);
	return (color_arr);
}
