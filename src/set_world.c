#include "hit_table_list.h"
#include "sphere.h"
#include "lambertian.h"
#include "light.h"
#include "world.h"

t_world	set_world(void)
{
	t_world world;

	world.back_ground = construct_color(0.1, 0.1, 0.2);
	world.objects = construct_htl();
	// 地面
	add_htl(&world.objects, gen_sphere(construct_vec(0, -100.5, -2), 100, gen_lambertian(construct_color(0.5, 0.1, 0.1))));
	// もの
	add_htl(&world.objects, gen_sphere(construct_vec(0, 0, -2), 0.5, gen_lambertian(construct_color(0.5, 0.1, 0.1)))); // gen_lambertian(construct_color(0.5, 0, 0)だと環境光にRの要素がないとき真っ黒担って不自然だった！
	add_htl(&world.objects, gen_sphere(construct_vec(1, 0,-2), 0.5, gen_lambertian(construct_color(0.4, 0.7, 0.8))));
	add_htl(&world.objects, gen_sphere(construct_vec(-1,0,-2), 0.5, gen_lambertian(construct_color(0.02, 0.2, 0.02))));
	// ライト
	add_htl(&world.objects, gen_sphere(construct_vec(0, 10, -20), 0.5, gen_light(construct_vec(50, 50, 50)))); // lightの色tの強さは大きさ、距離などの複合で決めるらしい。むずかしい(--;)。
	return (world);
}
