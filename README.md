# realpath(3) raises an error unexpectedly in some CircleCI environments

## Quick overview

- The version 2.33 of [the GNU C Library](https://www.gnu.org/software/libc/), a.k.a. glibc, has some compatiblity issues with older Linux kernels.
  - For instance, a call of [`realpath(3)`](https://www.man7.org/linux/man-pages/man3/realpath.3.html) for a path `/some_dir_name/` (_be aware of the trailing `/`_) returns a peculiar `EPERM` error if glibc 2.33 and an older Linux kernel are in use.
- Some Docker images from cutting-edge Linux distributions use glibc 2.33.
  - The distros include [Arch Linux](https://archlinux.org/packages/core/x86_64/glibc/), [Fedora 34](https://src.fedoraproject.org/rpms/glibc) and [Ubuntu 21.04](https://packages.ubuntu.com/hirsute/libc6).
- All of CircleCI's `docker` executors and some of CircleCI's `machine` executors use Linux kernel 4.15, which is _a bit_ old.

Hence, CircleCI users would see an unexpected error, derived from error in `realpath(3)`, when those cutting-edge Docker images are in use for `docker` executors on CircleCI.

## Notable impact

Due to this nature, `pacman -Sy` does not work on CircleCI's `docker` executors, unless the command is called along with a `-b /var/lib/pacman` (_ending without `/`_) command line argument.
