# Initially I saw an error like below:
#
# clang -O2 -target bpf -c bpf_program.c \
          -I/home/haibzhou/workspace/linux-5.4.6/tools/lib \
          -o bpf_program.o
# In file included from bpf_program.c:2:
# In file included from /home/haibzhou/workspace/linux-5.4.6/tools/lib/bpf/libbpf.h:14:
# In file included from /usr/include/stdio.h:27:
# In file included from /usr/include/bits/libc-header-start.h:33:
# In file included from /usr/include/features.h:489:
# /usr/include/gnu/stubs.h:7:11: fatal error: 'gnu/stubs-32.h' file not found
# # include <gnu/stubs-32.h>
#           ^~~~~~~~~~~~~~~~
# 1 error generated.
# make: *** [Makefile:2: bpf_program.o] Error 1
#
# This later on was fixed by:
#
# pacman -Sy lib32-glibc 
bpf_program.o: bpf_program.c
	clang -O2 -target bpf -c bpf_program.c \
		-I${HOME}/workspace/linux-5.4.6/tools/testing/selftests/bpf \
		-o bpf_program.o

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
