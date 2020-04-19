## Compiling

If you see the following error:

```console
$ clang -O2 -target bpf -c bpf_program.c \
        -I/home/haibzhou/workspace/linux-5.4.6/tools/lib \
        -o bpf_program.o
In file included from bpf_program.c:2:
In file included from /home/haibzhou/workspace/linux-5.4.6/tools/lib/bpf/libbpf.h:14:
In file included from /usr/include/stdio.h:27:
In file included from /usr/include/bits/libc-header-start.h:33:
In file included from /usr/include/features.h:489:
/usr/include/gnu/stubs.h:7:11: fatal error: 'gnu/stubs-32.h' file not found
# include <gnu/stubs-32.h>
          ^~~~~~~~~~~~~~~~
1 error generated.
make: *** [Makefile:2: bpf_program.o] Error 1
```

Try installing the following package:

```console
$ sudo pacman -Sy lib32-glibc
```

## Running

You may see this when you try it initially:

```console
$ make loader
$ ./loader
bpf_load_program() err=1
The kernel didn't load the BPF program
```

The errno `1` means operation is not permitted, you should try with `sudo`.

```console
$ make loader
$ sudo ./loader
```

