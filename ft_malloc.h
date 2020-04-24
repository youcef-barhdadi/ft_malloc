# include <stdio.h>
# include <stdlib.h>
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
	struct s_block *prev;
}		t_block;
t_block 	*init_block(t_block *block, t_zone *data,size_t size);
t_zone 		*init_zone(t_zone *zone, size_t size);
unsigned char 	get_type(size_t size);
size_t 		get_zone_size(size_t size);
void		*ft_malloc(size_t size);
void		ft_free(void *ptr);
