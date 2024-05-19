# Libmapvise

Libmapvise (pronounced lib-map-vise) is a cross-platform header-only C library
for seamlessly and nicely mapping anonymous memory and files, and using madvise
if supported by the platform.

The library is designed to not involve runtime overhead if possible, by using
compiler optimizations, while being fully cross platform

## Example usage

Check tests in tests/ directory for simple usage examples

## Library header file dependency

libmapvise does not deliver any dependencies by itself, it is the
responsibility of the source file to deliver all dependencies needed for
libmapvise

Required dependencies are as follows:

### Common dependencies for all platforms

- stdint.h

### Linux specific dependencies

- fcntl.h
- unistd.h
- sys/stat.h
- sys/mman.h
- errno.h

### Windows specific dependencies

- windows.h
- winbase.h
- memoryapi.h
- processthreadsapi.h

### Simple include example

```
[...]
#include <stdint.h>

#ifdef _WIN32
#include <windows.h>
#include <winbase.h>
#include <memoryapi.h>
#include <processthreadsapi.h>
#endif
#ifdef __linux__
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <errno.h>
#endif

#include <libmapvise/libmapvise.h>
[...]
```

## Testing

In Linux, test this library by using

```
cmake -DENABLE_TESTING=ON ..
make
make test
```

For testing for Windows on Linux, use

```
cmake -DENABLE_TESTING=ON -DMINGW_TESTING=ON ..
make
make test
```

Please note that testing for Windows requires MinGW gcc and Wine on Linux

Use `-DHUGEFILE_TESTING=OFF` to disable big files testing which require at least
8 GB of RAM to run, if your computer does not have such resources

## License

This library is licensed under GPLv3 with the Classpath exception, except for
the test cases files which are licensed under Public Domain.

This means, informally, that this library may be linked together in binary form
with other projects which may not be GPL compatible

Please read COPYING for more information, aswell as the notice for each source
file

## Contributions

This library is a work in progress. Feel free to submit any suggestions,
bug reports or pull requests to this repository
