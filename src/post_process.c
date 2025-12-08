#include "define.h"
#include "vec3.h"
#include "pixcel.h"


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

static t_color	median_filter(t_pixcel *pixcel_arr, int x, int y)
{
	int dx[9] = {-1,0,1,-1,0,1,-1,0,1};
	int dy[9] = {-1,-1,-1,0,0,0,1,1,1};
	double buf_r[9], buf_g[9], buf_b[9];
	for (int i = 0; i < 9; i++)
	{
		int nx = clamp_int(x + dx[i], 0, WINSIZE_X - 1);
		int ny = clamp_int(y + dy[i], 0, WINSIZE_Y - 1);
		int idx = ny * WINSIZE_X + nx;
		buf_r[i] = pixcel_arr[idx].color.x;
		buf_g[i] = pixcel_arr[idx].color.y;
		buf_b[i] = pixcel_arr[idx].color.z;
	}
	sort9(buf_r);
	sort9(buf_g);
	sort9(buf_b);
	return (construct_color(buf_r[4], buf_g[4], buf_b[4]));
	return (construct_color(buf_r[8], buf_g[8], buf_b[8]));
}

t_color	*post_proccess(t_pixcel *pixcel_arr)
{
	
	t_color	*color_arr = malloc(PIXCELS_NUM * sizeof(t_color));

	for (int y = 0; y < WINSIZE_Y; y++)
	{
		int yy = y * WINSIZE_X;
		for (int x = 0;  x < WINSIZE_X; x++)
		{
			color_arr[yy + x] = median_filter(pixcel_arr, x, y);
			// color_arr[yy + x] = pixcel_arr[yy + x].color;
		}
	}
	free(pixcel_arr);
	return (color_arr);
}
