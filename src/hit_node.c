/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:36:43 by khanadat          #+#    #+#             */
/*   Updated: 2026/01/12 18:02:00 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hit_node.h"

static bool	hit_bvh(const void *s, const t_ray ray, t_hit_record *rec, t_range range);
void		clear_bvh(t_hit_table *self);
t_hit_node	construct_hit_node(t_hit_table *lhs, t_hit_table *rhs);

t_hit_table	*gen_hit_node(t_hit_table *lhs, t_hit_table *rhs)
{
	t_hit_node	*node;

	if (!lhs && !rhs)
		return (NULL);
	if (!lhs)
		return (rhs);
	if (!rhs)
		return (lhs);
	node = ft_calloc(1, sizeof(t_hit_node));
	if (!node)
		return (NULL);
	*node = construct_hit_node(lhs, rhs);
	return ((t_hit_table *)node);
}

t_hit_node	construct_hit_node(t_hit_table *lhs, t_hit_table *rhs)
{
	t_hit_node	node;

	ft_bzero(&node, sizeof(t_hit_node));
	// 下部のノードのどちらもaabbをもつときだけaabbを持つ。
	if (lhs->have_aabb && rhs->have_aabb)
	{
		node.hit_table.have_aabb = true;
		node.hit_table.aabb = surrounding_box(lhs->aabb, rhs->aabb);
	}
	node.hit_table.hit = hit_bvh;
	node.hit_table.clear = clear_bvh;
	node.lhs = lhs;
	node.rhs = rhs;
	return (node);
}

/*
@brief bvh木構造をレイとの交差判定を行う
*/
static bool	hit_bvh(const void *s, const t_ray ray, t_hit_record *rec, t_range range)
{
	const t_hit_node	*self;
	bool				hit_left;
	bool				hit_right;

	self = (const t_hit_node *)s;
	if (self == NULL)
		return (false);
	// まずboxにヒットしないものをfalseとする
	if (self->hit_table.have_aabb \
		&& self->hit_table.aabb.hit(&self->hit_table.aabb, ray, range) == false)
		return (false);
	hit_left = self->lhs->hit(self->lhs, ray, rec, range);
	// 左側に当たった時はrangeを更新
	if (hit_left)
		range.max = rec->t;
	hit_right = self->rhs->hit(self->rhs, ray, rec, range);
	return (hit_left || hit_right);
}

void	clear_bvh(t_hit_table *self)
{
	t_hit_node	*node;

	if (!self)
		return ;
	node = (t_hit_node *)self;
	if (node->lhs)
	{
		node->lhs->clear(node->lhs);
		node->lhs = NULL;
	}
	if (node->rhs)
	{
		node->rhs->clear(node->rhs);
		node->rhs = NULL;
	}
	free(node);
}
