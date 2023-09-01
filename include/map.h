#ifndef MAP
#define MAP

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>


typedef struct s_bucket {
	char			*value;
	char			*key;
	struct s_bucket	*next;
} t_bucket;

typedef struct s_map {
	t_bucket	*buckets;
	size_t		size;
	size_t		(*hash_func)(char *key);
} t_map;



t_map	*map_init(size_t (*hash_func)(char *), size_t size);
t_map	*map_add(t_map *map, char *key, char *value);
char	*map_get_value(t_map *map, char *key);
void	map_free(t_map *map);

#endif // !MAP
