#include <linux/bpf.h>
#include <bpf_helpers.h>

SEC("tracepoint/syscalls/sys_enter_execve")
int bpf_prog(void *ctx) {
  char msg[] = "Hello, BPF World!";
  bpf_trace_printk(msg, sizeof(msg));
  return 0;
}

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

char _license[] SEC("license") = "GPL";
