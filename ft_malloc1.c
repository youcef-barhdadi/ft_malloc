# include <stdio.h>
# include <sys/mman.h> 
# include <string.h>
# include <errno.h>
# include <unistd.h>

typedef struct s_zone
{
	size_t size;
	size_t free_size;
	int 	type;
	size_t block_count;
	struct s_zone *next;
}t_zone;

typedef struct s_block
{
	int free;
	size_t size;
	struct s_block *next;
}		t_block;

t_zone *g_zone;
// 1 tiny 
// 2 small
//  3 large
//
//
char get_type(size_t size)
{
	if (size < 255 )
		return 1;
	if (size < 2048)
		return 2;
	return 3;


}
t_zone *create_zone(size_t size)
{
	t_zone *data;
	size_t zone_size;

	 zone_size = getpagesize() * 4;

	printf("%d\n", zone_size);
	 data = (t_zone *)mmap(NULL, zone_size , PROT_READ | PROT_WRITE , MAP_PRIVATE | MAP_ANONYMOUS , -1, 0);
	 memset(data, 0, sizeof(t_zone));
	 data->size = zone_size;
	 data->free_size = zone_size - sizeof(t_zone);
	 data->next = NULL;
	 data->type = get_type(size);
	t_block *block = (t_block *)((void *)data + sizeof(t_zone));
	memset(block, 0, sizeof(t_zone));
	block->size = size;
	data->free_size -= (sizeof(t_block) * 2 + size);
	block->free = 0;
	block->next = NULL;
	t_block *next = (t_block *)((void *)block + sizeof(t_block));
	bzero(next, sizeof(t_block));
	next->free = 1;
	next->size = data->free_size;
	block->next = next;


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


	zone = g_zone;
	while (zone)
	{
		if (size < zone->free_size  + sizeof (t_block))
			return zone;
	}
}


void *allocate(size_t size) {
	t_zone *zone;
	if (g_zone == NULL)
	{
		zone = create_zone(size);
		return zone + sizeof(t_zone) + sizeof(t_block);
	}
	zone = find_zone(size);
	t_block *block = (t_block *)((void *)zone + sizeof(t_zone));

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
	printf("%lld szie %d \n", (size_t)next - (size_t)g_zone, sizeof(block));
	bzero(next, sizeof(t_block));
	next->free = 1;
	next->size  = zone->free_size; 
	block->next = next;
	return block + sizeof(t_block);
	
}

void *ft_malloc(size_t size)
{
	if (size <= 0)
		return (NULL);
	return allocate(size);



}


int main(int argc, char **argv)
{

	char *a;
	for (int i = 0; i < 46; i++)
		a= ft_malloc(12);
	t_block *b = (t_block *)((void *)g_zone + sizeof(t_zone));

	while (b)
	{
		printf("%d\n", b->size);
		b= b->next;
	}

	return (0);
}
