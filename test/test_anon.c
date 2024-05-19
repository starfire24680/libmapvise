/*
 * 2024 Kurek Damian <starfire24680@gmail.com>
 *
 * This file is a test case for libmapvise
 * The intention of this short program is to test libmapvise's anonymous
 * memory allocation and deallocation
 *
 * This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any
 * means.
 *
 * In jurisdictions that recognize copyright laws, the author or authors
 * of this software dedicate any and all copyright interest in the
 * software to the public domain. We make this dedication for the benefit
 * of the public at large and to the detriment of our heirs and
 * successors. We intend this dedication to be an overt act of
 * relinquishment in perpetuity of all present and future rights to this
 * software under copyright law.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * For more information, please refer to <http://unlicense.org/>
 */

#include <stdio.h>
#include <stdlib.h>
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

int main() {
	size_t size = (1024 * 1024 * 1024);
	struct libmapvise_map ret = libmapvise_mmap_anon(size);
	if (ret.ptr == NULL) {
		fprintf(stderr, "Error while mapping anonymous memory, err %i\n", ret.len);
		return 1;
	}

	libmapvise_madvise(ret.ptr, size, ADVISE_HUGEPAGE | ADVISE_SEQUENTIAL);
	libmapvise_madvise(ret.ptr, size, ADVISE_WILLNEED);

	unsigned char *array = ret.ptr;

	for(int i = 0; i < size; i++) {
		array[i] = i % 256;
	}

	for(int i = 0; i < size; i++) {
		if(array[i] != i % 256) {
			fprintf(stderr, "Error while checking value %i\n", array[i]);
			return 1;
		}
	}

	int val = libmapvise_munmap_anon(&ret);
	if(val != 0) {
		fprintf(stderr, "Error while unmapping anonymous memory, err %i\n", val);
		return 1;
	}

	return 0;
}
