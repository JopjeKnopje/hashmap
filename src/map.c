#include "map.h"
#include "libft.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int	strlen_largest(const char *s1, const char *s2)
{
	const int	s1_len = ft_strlen(s1);
	const int	s2_len = ft_strlen(s2);
	const int	comp = s1_len < s2_len;

	return ((comp) * s2_len + (!comp) * s1_len);
}

t_map *map_init(size_t (*hash_func)(char *), size_t size)
{
	t_map *map = ft_calloc(1, sizeof(t_map));
	if (!map)
		return (NULL);

	map->buckets = ft_calloc(size, sizeof(t_bucket));

	if (!map->buckets)
		return (NULL);

	map->size = size;
	map->hash_func = hash_func;
	return (map);
}

t_map *map_add(t_map *map, char *key, char *value)
{
	size_t index = map->hash_func(key) % map->size;
	t_bucket *bucket = &map->buckets[index];

	size_t i = 0;
	while (bucket)
	{
		printf("bucket %ld\n", i);
		if (!bucket->next)
			break;
		bucket = bucket->next;
		i++;
	}

	bucket->content = value;
	return map;
}

char *map_get(t_map *map, char *key)
{
	size_t index = map->hash_func(key) % map->size;
	t_bucket *bucket = &map->buckets[index];

	return bucket->content;
}

void map_free(t_map *map)
{
	free(map->buckets);
	free(map);
}
