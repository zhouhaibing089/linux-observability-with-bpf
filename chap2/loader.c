#include "bpf_load.h"
#include <stdio.h>

int main(int argc, char **argv) {
  if (load_bpf_file("bpf_program.o") != 0) {
    printf("The kernel didn't load the BPF program\n");
    return -1;
  }

  // since we created a map in our bpf program, we can get its fd via map_data
  printf("fd of my_map is: %d", map_data[0].fd);

  read_trace_pipe();

  return 0;
}
