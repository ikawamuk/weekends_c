#include "define.h"
#include "hit_table_list.h"
#include "cylinder.h"
#include "plane.h"
#include "sphere.h"
#include "lambertian.h"
#include "light.h"
#include "world.h"
#include "bvh.h"

size_t	count_objects(t_hit_table_list *list)
{
	size_t	n;
	t_hit_table_node	*node;

	n = 0;
	node = list->head;
	while (node)
	{
		node = node->next;
		n++;
	}
	return (n);
}

t_world	set_world(void)
{
	t_world world;

	world.back_ground = construct_color(0, 0, 0);
	world.objects = construct_htl();
	// 床
	add_htl(&world.objects, gen_plane(construct_vec(0, -0.5, 0), construct_vec(0, 1, 0), gen_lambertian(construct_color(0.2, 0.2, 0.4))));
	// もの
	add_htl(&world.objects, gen_sphere(construct_vec(0, 0, -3), 0.5, gen_lambertian(construct_color(0.5, 0.1, 0.1)))); // gen_lambertian(construct_color(0.5, 0, 0)だと環境光にrの要素がないとき真っ黒担って不自然だった！
	// ライト
	add_htl(&world.objects, gen_sphere(construct_vec(0, 3, -2), 0.5, gen_light(construct_vec(90, 90, 90)))); // lightの色tの強さは大きさ、距離などの複合で決めるらしい。むずかしい(--;)。
	size_t	n = count_objects(&world.objects);
	world.bvh_root = (t_hit_table *)construct_bvh_node(&world.objects, 0, n);
	return (world);
}
