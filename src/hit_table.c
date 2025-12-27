#include "hit_table.h"

/*
@brief オブジェクトのマテリアルをfreeする
*/
void	clear_primitive(t_hit_table *self)
{
	free(self->mat_ptr);
	self->mat_ptr = NULL;
	free(self);
}
