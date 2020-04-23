# include "ft_malloc.h"
t_block *init_block(t_block *block, t_zone *data,size_t size)
{
	memset(block, 0, sizeof(t_block));
	block->size = size;
	block->free = 0;
	block->next = NULL;
	return (block);
}

t_zone *init_zone(t_zone *zone, size_t size)
{
	memset(zone, 0, sizeof(t_zone));
	zone->size = get_zone_size(size);
	zone->free_size = zone->size - sizeof(t_zone);
	zone->next = NULL;
	zone->type = get_type(size);
	return zone;
}

