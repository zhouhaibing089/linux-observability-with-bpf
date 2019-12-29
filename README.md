linux-observability-with-bpf
============================

Code written while reading Linux Observability with BPF. Runs on Archlinux with
kernel v5.4.6.

## Setup

We need the kernel source to compile those programs:

```console
$ mkdir ${HOME}/workspace
$ curl -L -o ${HOME}/workspace/linux-5.4.6.tar.xz \
    "https://cdn.kernel.org/pub/linux/kernel/v5.x/linux-5.4.6.tar.xz"
$ cd ${HOME}/workspace
$ tar xf linux-5.4.6.tar.xz
$ cd linux-5.4.6
$ cp /usr/lib/modules/$(uname -r)/build/.config .
$ make oldconfig
```
