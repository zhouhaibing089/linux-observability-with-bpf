There is one paragraph talking about this:

> The kernel helpers provide the function bpf_map_update_elem for this purpose.
> This function’s signature is different if you load it from `bpf/bpf_helpers.h`, 
> within the program running on the kernel, than if you load it from
> `tools/lib/bpf/bpf.h`, within the program running in user-space.

We need to figureout where is `bpf/bpf_helpers.h` since it mentions that the
signature takes the map point as its first argument. One obvious guess is inside
[tools/lib/bpf/bpf_helpers.h][1]. At my first glance, there is no function called
`bpf_map_update_ele` at all. However, something interesting is sitting there:

```c
#include "bpf_helper_defs.h"
```

The file is not present, but if we look at [libbpf][2] repository, we can see it
actually [here][3].

```c
/*
 * bpf_map_update_elem
 *
 * 	Add or update the value of the entry associated to *key* in
 * 	*map* with *value*. *flags* is one of:
 *
 * 	**BPF_NOEXIST**
 * 		The entry for *key* must not exist in the map.
 * 	**BPF_EXIST**
 * 		The entry for *key* must already exist in the map.
 * 	**BPF_ANY**
 * 		No condition on the existence of the entry for *key*.
 *
 * 	Flag value **BPF_NOEXIST** cannot be used for maps of types
 * 	**BPF_MAP_TYPE_ARRAY** or **BPF_MAP_TYPE_PERCPU_ARRAY**  (all
 * 	elements always exist), the helper would return an error.
 *
 * Returns
 * 	0 on success, or a negative error in case of failure.
 */
static int (*bpf_map_update_elem)(void *map, const void *key, const void *value, __u64 flags) = (void *) 2;
```

I'm not clear on how does it work, specifically, how does the numer `2` come out?

The userspace path `tools/lib/bpf/bpf.h` is clear though:

```c
LIBBPF_API int bpf_map_update_elem(int fd, const void *key, const void *value,
				   __u64 flags);
```

[1]: https://github.com/torvalds/linux/blob/master/tools/lib/bpf/bpf_helpers.h
[2]: https://github.com/libbpf/libbpf
[3]: https://github.com/libbpf/libbpf/blob/master/src/bpf_helper_defs.h
