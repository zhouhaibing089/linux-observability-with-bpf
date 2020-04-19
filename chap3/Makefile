map_crud: map_crud.c
	clang -o map_crud ${HOME}/workspace/linux-5.4.6/tools/lib/bpf/bpf.o \
		-I${HOME}/workspace/linux-5.4.6/tools/lib \
		map_crud.c

pin_fd: pin_fd.c
	clang -o pin_fd ${HOME}/workspace/linux-5.4.6/tools/lib/bpf/libbpf.so \
		-I${HOME}/workspace/linux-5.4.6/tools/lib \
		pin_fd.c

get_fd: get_fd.c
	clang -o get_fd ${HOME}/workspace/linux-5.4.6/tools/lib/bpf/libbpf.so \
		-I${HOME}/workspace/linux-5.4.6/tools/lib \
		get_fd.c

clean:
	rm -f map_crud pin_fd get_fd
