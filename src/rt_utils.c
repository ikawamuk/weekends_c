#include <stdint.h>
#include "rt_utils.h"

static uint64_t	random_uint64(void)
{
	static uint64_t x = 0x629d97afad9281f2; // /bin/bash -c openssl rand -hex 8
	x ^= x << 12;
	x ^= x >> 25;
	x ^= x << 27;
	return (x);
}

double random_double(double min, double max)
{
	uint64_t u = random_uint64() >> 11;
	double v = (double)u * (1.0 / 9007199254740992.0);
	return (min + (max - min) * v);
}

int	random_int(int min, int max)
{
	if (min > max)
		return (min);
	int	range = max - min + 1;
	return (min + (int)(random_double(0.0, 1.0) * range));
}

double clamp(double x, double min, double max)
{
	if (x < min)
		return min;
	if (x > max)
		return max;
	return (x);
}

/*
@brief 正規化された球面法線から球面座標（経度φ・緯度θ）を求め、それらを [0,1]×[0,1] に写像した UV を計算する
*/
void	get_sphere_uv(t_vec3 unit_normal, double *u, double *v)
{
	double	phi = atan2(unit_normal.z, unit_normal.x);
	double	theta = asin(unit_normal.y);
	*u = (1.0 - (phi + M_PI) / (2.0 * M_PI)) * 1.5; // 球では横に長くなりがちなので1.5倍多く分割して補正する。
	*v = (theta + M_PI / 2.0) / M_PI;
	return ;
}

/*
@param offset 交点 - 平面の基準点
2param normal 平面の法線ベクトル
*/
void	get_plane_uv(t_point3 offset, t_vec3 normal, double *u, double *v)
{
	t_vec3	onb[3];
	static const int unit_edge = 50; // 単位平面の辺の長さ。大きいとタイルもでかい。unit_edge / N がタイルの一辺。

	build_onb(onb, normal);
	*u = dot(offset, onb[0]) / unit_edge; // unit_edgeのグリッドでみたu成分
	*v = dot(offset, onb[1]) / unit_edge; // unit_edgeのグリッドでみたv成分
	*u = *u - floor(*u); // 整数部分を切り捨て1グリッド内の位置を取り出す[0, 1]
	*v = *v - floor(*v);
	return ;
}
