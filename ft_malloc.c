# include "ft_malloc.h"





t_zone *create_zone(size_t size)
{
	t_zone *data;
	size_t zone_size;
	 zone_size = get_zone_size(size);
	 data = (t_zone *)mmap(NULL, zone_size , PROT_READ | PROT_WRITE , MAP_PRIVATE | MAP_ANONYMOUS , -1, 0);
	 if (data == MAP_FAILED)
	{
		perror("mmap ");
		return NULL;
	}
	 init_zone(data, size);
	t_block *block = (t_block *)((void *)data + sizeof(t_zone));
	init_block(block,data ,size);
	data->free_size -= (sizeof(t_block) * 2 + size);
	if (data->type != 3)
	{
		t_block *next = (t_block *)((void *)block + sizeof(t_block));
		bzero(next, sizeof(t_block));
		next->free = 1;
		next->size = data->free_size;
		next->prev = block;
		block->next = next;
	}
	if (g_zone == NULL)
		g_zone = data;
	else{
		t_zone *temp = g_zone;
		while (temp->next)
		{
			temp = temp->next;
		}
		temp->next = data;

	}
	return data; 
}




t_zone *find_zone(size_t size)
{
	t_zone *zone;

	int type = get_type(size);
	zone = g_zone;
	if (type == 3)
		return NULL;
	while (zone)
	{
		if (type == zone->type && size < zone->free_size  + sizeof (t_block))
			return zone;
		zone = zone->next;
	}
	return NULL;
}


void *allocate(size_t size) {
	t_zone *zone;
	if (g_zone == NULL)
	{
		zone = create_zone(size);
		zone->count++;
		return (void *)zone + sizeof(t_zone) + sizeof(t_block);
	}
	zone = find_zone(size);
	if (zone == NULL)
	{
	
		zone = create_zone(size);
		zone->count++;
		return zone;
	}
	t_block *block = (t_block *)((void *)zone + sizeof(t_zone));

	/// increment zone count
	
		zone->count++;
	while (block)
	{
	 	
		if (block->size > size && block->free)
			break ;
		block = block->next;
	}

	int last_size = block->size;
	block->size  = size;
	block->free = 0;
	zone->free_size -= size + sizeof (t_block); 
	t_block *next = (t_block *)((void *)block + sizeof(t_block) + size);
	bzero(next, sizeof(t_block));
	next->free = 1;
	next->size  = zone->free_size; 
	next->prev =  block;
	block->next = next;
	return (void *)((void *)block + sizeof(t_block));
	
}

void *ft_malloc(size_t size)
{
	if (size <= 0)
		return (NULL);
	return allocate(size);

}