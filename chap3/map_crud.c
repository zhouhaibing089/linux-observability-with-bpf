#include <errno.h>
#include <linux/bpf.h>
#include <stdio.h>
#include <string.h>
#include <bpf/libbpf.h>

#define SEC(NAME) __attribute__((section(NAME), used))

// bpf_map_def is defined in tools/lib/bpf/libbpf.h. So what we did is:
// add compile flag: -I${HOME}/workspace/linux-5.4.6/tools/lib
// and #include <bpf/libbpf.h>
struct bpf_map_def SEC("maps") my_map = {
  .type        = BPF_MAP_TYPE_HASH,
  .key_size    = sizeof(int),
  .value_size  = sizeof(int),
  .max_entries = 100,
  .map_flags   = BPF_F_NO_PREALLOC,
};

// these two functions are defined in tools/lib/bpf/bpf.c, so this file should
// be linked with tools/lib/bpf/bpf.o, see Makefile.
int bpf_create_map(enum bpf_map_type map_type, int key_size, int value_size,
                   int max_entries, __u32 map_flags);
int bpf_map_update_elem(int fd, const void *key, const void *value,
                        __u64 flags);
int bpf_map_lookup_elem(int fd, const void *key, void *value);
int bpf_map_delete_elem(int fd, const void *key);

int main(int argc, char **argv) {
  // my_map is created with bpf_map_def, we should be able to retrieve its fd
  // with map_data[0].fd
  // Noted, map_data is defined in samples/bpf/bpf_load.c
  // printf("bpf_map_def gives us fd: %d", map_data[0].fd);


  int fd, key, value, result;
  key = 1, value = 1234;

  fd = bpf_create_map(BPF_MAP_TYPE_HASH, sizeof(int), sizeof(int), 100,
                      BPF_F_NO_PREALLOC);
  printf("Map created with fd: %d\n", fd);

  result = bpf_map_update_elem(fd, &key, &value, BPF_ANY);
  if (result == 0) {
    printf("Map updated with new element\n");
  } else {
    printf("Failed to update map with new value: %d %s\n", result,
           strerror(errno));
  }

  // now create an element with the same key
  value = 5678;
  result = bpf_map_update_elem(fd, &key, &value, BPF_NOEXIST);
  if (result == 0) {
    printf("Map updated with new element\n");
  } else {
    printf("Failed to update map with new value: %d %s\n", result,
           strerror(errno));
  }

  // and try to update an element which doesn't exist yet.
  key = 1234;
  value = 5678;
  result = bpf_map_update_elem(fd, &key, &value, BPF_EXIST);
  if (result == 0) {
    printf("Map updated with new element\n");
  } else {
    printf("Failed to update map with new value: %d %s\n", result,
           strerror(errno));
  }

  // read
  key = 1;
  result = bpf_map_lookup_elem(fd, &key, &value);
  if (result == 0) {
    printf("Value read from the map: '%d'\n", value);
  } else {
    printf("Failed to read value from the map: %d %s\n", result,
           strerror(errno));
  }

  // delete
  result = bpf_map_delete_elem(fd, &key);
  if (result == 0) {
    printf("Element deleted from the map\n");
  } else {
    printf("Failed to delete element from the map: %d %s\n", result,
           strerror(errno));
  }
}
