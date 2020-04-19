#include <errno.h>
#include <bpf/bpf.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char **argv) {
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
