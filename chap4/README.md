In order to follow the examples mentioned in chapter 4, we need to install bcc
on our environment. Since I'm running Arch, the step for myself is installing it
from AUR. The package is [bcc][1].

At the time of writing, the PKGBUILD is having issues due to incompabilities with
latest clang. bcc has fixed it but we have to manually port it back:

```console
$ mkdir bcc
$ cd bcc
$ curl -L -o bcc.tar.gz https://aur.archlinux.org/cgit/aur.git/snapshot/bcc.tar.gz
$ tar xzf bcc.tar.gz
$ cd bcc
$ makepkg -si
```

The last step would fail with something like:

```console
$ makepkg -si
==> Making package: bcc 0.13.0-1 (Sun 19 Apr 2020 05:33:47 PM PDT)
==> Checking runtime dependencies...
==> Checking buildtime dependencies...
==> Retrieving sources...
  -> Found bcc-0.13.0.tar.gz
==> Validating source files with sha512sums...
    bcc-0.13.0.tar.gz ... Passed
==> Extracting sources...
  -> Extracting bcc-0.13.0.tar.gz with bsdtar
==> Removing existing $pkgdir/ directory...
==> Starting build()...
-- The C compiler identification is GNU 9.3.0
-- The CXX compiler identification is GNU 9.3.0
-- Check for working C compiler: /usr/bin/cc
-- Check for working C compiler: /usr/bin/cc - works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Detecting C compile features
-- Detecting C compile features - done
-- Check for working CXX compiler: /usr/bin/c++
-- Check for working CXX compiler: /usr/bin/c++ - works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Revision is 0.13.0
-- Performing Test HAVE_NO_PIE_FLAG
-- Performing Test HAVE_NO_PIE_FLAG - Success
-- Performing Test HAVE_REALLOCARRAY_SUPPORT
-- Performing Test HAVE_REALLOCARRAY_SUPPORT - Success
-- Found BISON: /usr/bin/bison (found version "3.5.4")
-- Found FLEX: /usr/bin/flex (found version "2.6.4")
-- Found LLVM: /usr/include 10.0.0
-- Found LibElf: /usr/lib/libelf.so
-- Performing Test ELF_GETSHDRSTRNDX
-- Performing Test ELF_GETSHDRSTRNDX - Success
CMake Error at CMakeLists.txt:68 (message):
  Unable to find clang libraries


-- Configuring incomplete, errors occurred!
See also "/home/haibzhou/workspace/bcc/bcc/src/bcc/build/CMakeFiles/CMakeOutput.log".
==> ERROR: A failure occurred in build().
    Aborting...
```

To fix it, we need to apply this [patch][2] to `src/bcc/CMakeLists.txt`, then

```console
$ makepkg -si --holdver -e
```

[1]: https://aur.archlinux.org/pkgbase/bcc/
[2]: https://github.com/iovisor/bcc/commit/1599c2ef8206988d5d
