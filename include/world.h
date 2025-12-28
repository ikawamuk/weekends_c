#ifndef WORLD_H
# define WORLD_H

#include "vec3.h"
#include "hit_table_list.h"
#include "camera.h"
#include "hit_node.h"

typedef struct s_world
{
	t_color				back_ground;
	double				ambient_ratio;
	t_camera			camera;
	t_hit_table			*node;
	t_hit_table_list	lights;
}	t_world;

#endif
