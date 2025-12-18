#include "define.h"
#include "hit_table_list.h"
#include "cylinder.h"
#include "plane.h"
#include "sphere.h"
#include "lambertian.h"
#include "light.h"
#include "world.h"

t_world	set_world(void)
{
	t_world world;

	world.back_ground = construct_color(0, 0, 0);
	world.objects = construct_htl();
	// 床
	add_htl(&world.objects, gen_plane(construct_vec(0, 0, 0), construct_vec(0, 1, 0), gen_lambertian(construct_color(0.2, 0.4, 0.2))));
	// 背景
	add_htl(&world.objects, gen_plane(construct_vec(0, 0, -5), construct_vec(0, 0, 1), gen_lambertian(construct_color(0.2, 0.2, 0.2))));
	// もの
	add_htl(&world.objects, gen_sphere(construct_vec(0, 0.5, -3), 0.5, gen_lambertian(construct_color(0.5, 0.1, 0.1)))); // gen_lambertian(construct_color(0.5, 0, 0)だと環境光にrの要素がないとき真っ黒担って不自然だった！
	add_htl(&world.objects, gen_sphere(construct_vec(1, 0.5, -3), 0.5, gen_lambertian(construct_color(0.2, 0.5, 0.1))));
	// ライト
	t_sphere	*light = gen_sphere(construct_vec(0, 20, 5), 0.05, gen_light(construct_vec(1, 1, 1)));
	add_htl(&world.objects, light);
	world.light_p = (t_hit_table *)light;
	return (world);
}
