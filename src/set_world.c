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
	// 柱
	add_htl(&world.objects, gen_cylinder(construct_vec(2, 0, -4), normalize(construct_vec(0, 1, 0)), 0.3, 1, gen_lambertian(construct_color(0.9, 0.9, 0.9))));
	add_htl(&world.objects, gen_cylinder(construct_vec(-2, 0, -4), normalize(construct_vec(0, 1, 0)), 0.3, 1, gen_lambertian(construct_color(0.9, 0.9, 0.9))));
	// 壁
	add_htl(&world.objects, gen_plane(construct_vec(0, 0, -5), normalize(construct_vec(0, 0, 1)), gen_lambertian(construct_color(0.7, 0.7, 0.7))));
	add_htl(&world.objects, gen_plane(construct_vec(3, 0, 0), normalize(construct_vec(-1, 0, 0)), gen_lambertian(construct_color(0.7, 0.2, 0.2))));
	add_htl(&world.objects, gen_plane(construct_vec(-3, 0, 0), normalize(construct_vec(1, 0, 0)), gen_lambertian(construct_color(0.2, 0.7, 0.2))));
	// 地面
	add_htl(&world.objects, gen_plane(construct_vec(0, -2, -3), construct_vec(0, 1, 0), gen_lambertian(construct_color(0.3, 0.3, 0.3))));
	// もの
	add_htl(&world.objects, gen_sphere(construct_vec(0, 0, -3), 0.5, gen_lambertian(construct_color(0.5, 0.1, 0.1)))); // gen_lambertian(construct_color(0.5, 0, 0)だと環境光にrの要素がないとき真っ黒担って不自然だった！
	// ライト
	add_htl(&world.objects, gen_sphere(construct_vec(1, 0, -1), 0.5, gen_light(construct_vec(50, 50, 50)))); // lightの色tの強さは大きさ、距離などの複合で決めるらしい。むずかしい(--;)。
	return (world);
}
