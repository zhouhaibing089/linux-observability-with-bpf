from bcc import BPF

bpf_source = """
int trace_go_main(struct pt_regs *ctx) {
    
}
"""
