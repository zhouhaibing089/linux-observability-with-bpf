bpf_program.o: bpf_program.c
	clang -O2 -target bpf -c bpf_program.c -o bpf_program.o

loader: loader.c
	clang -o loader -l elf \
		${HOME}/workspace/linux-5.4.6/tools/lib/bpf/bpf.o -l elf \
		-I${HOME}/workspace/linux-5.4.6/samples/bpf \
		-I${HOME}/workspace/linux-5.4.6/tools/lib \
		-I${HOME}/workspace/linux-5.4.6/tools/perf \
		-I${HOME}/workspace/linux-5.4.6/tools/include \
		-D HAVE_ATTR_TEST=0 \
		${HOME}/workspace/linux-5.4.6/samples/bpf/bpf_load.c \
		loader.c
