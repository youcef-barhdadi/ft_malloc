# include "ft_malloc.h"


void zone_tofree(void *ptr, t_block **block, t_zone **zone)
{

	t_zone *z = g_zone;
	t_block *b;
	void *p;
	if (z == NULL)
		return ;
	while (z)
	{
		b = (t_block *)((void*)z + sizeof(t_zone));

		while (b)
		{
			
			p = ((void *)b + sizeof(t_block));
			if (p == ptr)
			{
				*zone = z;
			*block = b;
				return ;
			}
			b = b->next;
		}
	
		z = z->next;
	}

	zone = NULL;
	block = NULL;

}


void	marge_block(t_block *block)
{
	
	t_block *prev;
	t_block *next;

	prev = block->prev;
	next = block->next;
	// first case
	if ( next  && prev  && next->free && prev->free)
	{	
		prev->size = next->size + block->size + ( 2* sizeof(block));
		memset(next, 0, sizeof (t_block));
		memset(block, 0, sizeof (t_block));
	}
	else if (next && next->free)
	{
		block->size = next->size + sizeof(t_zone);
		memset(next, 0, sizeof (t_block));
	}
	else if (prev && prev->free)
	{
	
		prev->size = block->size + ( sizeof(block));
	}


}


void free_empty_zone(t_zone *zone)
{
	printf("count ====>%d", zone->count);
	if (zone->count == 0)
	{
		printf("free works\n");
		munmap((void *)zone, zone->size);	
	}

}

void ft_free(void *ptr)
{
	
	t_block *block;
	t_zone *zone;

	zone_tofree(ptr, &block,&zone);
	zone->count--;
	if (block == NULL)
		return ;
	block->free = 1;
	marge_block(block);
	free_empty_zone(zone);
}


