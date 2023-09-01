#include "map.h"
#include "libft.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/_types/_va_list.h>

int	strlen_largest(const char *s1, const char *s2)
{
	const int	s1_len = ft_strlen(s1);
	const int	s2_len = ft_strlen(s2);
	const int	comp = s1_len < s2_len;

	return ((comp) * s2_len + (!comp) * s1_len);
}

static t_bucket *bucket_add()
{
	t_bucket *bucket = ft_calloc(1, sizeof(t_bucket));
	if (!bucket)
		return (NULL);
	return (bucket);
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

	// Check if we have key in bucket that matches with the key passed.
	// 		if true:	overwrite that value with new value.
	// 
	// 		else:		we have a collision, so we add another bucket to the next ptr.
	//					Essentially adding a node to the linked list

	while (bucket)
	{
		// If we match key add a new bucket.
		if (!bucket->next || !ft_strncmp(bucket->key, key, strlen_largest(bucket->key, key)))
		{
			assert(bucket->next == NULL && "bucket->next has to be zero!");
			bucket->next = bucket_add();
			bucket->key = key;
			bucket->value = value;
			break;
		}
		bucket = bucket->next;
	}
	return map;
}

char *map_get_value(t_map *map, char *key)
{
	size_t index = map->hash_func(key) % map->size;
	t_bucket *bucket = &map->buckets[index];

	while (bucket)
	{
		if (bucket->key && !ft_strncmp(bucket->key, key, strlen_largest(bucket->key, key)))
		{
			return bucket->value;
		}

		bucket = bucket->next;
	}
	return NULL;
}

void map_free(t_map *map)
{
	// size_t i = 0;
	// while (i < map->size)
	// {
	// 	free(&map->buckets[i]);
	// 	i++;
	// }
	free(map);
}
