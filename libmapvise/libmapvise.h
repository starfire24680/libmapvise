/*
 * libmapvise header file
 *
 * Copyright (C) 2024 Kurek Damian <starfire24680@gmail.com>
 *
 * This file is part of the libmapvise library
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <https://www.gnu.org/licenses>.
 *
 * Linking this library statically or dynamically with other modules is
 * making a combined work based on this library. Thus, the terms and
 * conditions of the GNU General Public License cover the whole combination.
 *
 * As a special exception, the copyright holders of this library give you
 * permission to link this library with independent modules to produce an
 * executable, regardless of the license terms of these independent modules,
 * and to copy and distribute the resulting executable under terms of your
 * choice, provided that you also meet, for each linked independent module,
 * the terms and conditions of the license of that module. An independent
 * module is a module which is not derived from or based on this library.
 * If you modify this library, you may extend this exception to your version
 * of the library, but you are not obliged to do so. If you do not wish to
 * do so, delete this exception statement from your version.
 */

enum libmapvise_advices {
	ADVISE_NORMAL = 0x1,
	ADVISE_RANDOM = 0x2,
	ADVISE_SEQUENTIAL = 0x4,
	ADVISE_WILLNEED = 0x8,
	ADVISE_DONTNEED = 0x10,
	ADVISE_REMOVE = 0x20,
	ADVISE_DONTFORK = 0x40,
	ADVISE_DOFORK  = 0x80,
	ADVISE_HWPOISON = 0x100,
	ADVISE_MERGEABLE = 0x200,
	ADVISE_UNMERGEABLE = 0x400,
	ADVISE_HUGEPAGE = 0x800,
	ADVISE_NO_HUGEPAGE = 0x1000,
	ADVISE_COLLAPSE = 0x2000,
	ADVISE_DONTDUMP = 0x4000,
	ADVISE_DODUMP  = 0x8000,
	ADVISE_FREE = 0x10000,
	ADVISE_WIPEONFORK = 0x20000,
	ADVISE_KEEPONFORK = 0x40000
};

static inline uint64_t libmapvise_advice_transform(uint64_t *advice) {
	uint64_t new_advice = 0;
#ifndef _WIN32

#ifdef MADV_NORMAL
	if(*advice & ADVISE_NORMAL) {
		*advice ^= ADVISE_NORMAL;
		return MADV_NORMAL;
	}
#endif

#ifdef MADV_RANDOM
	if(*advice & ADVISE_RANDOM) {
		*advice ^= ADVISE_RANDOM;
		return MADV_RANDOM;
	}
#endif

#ifdef MADV_SEQUENTIAL
	if(*advice & ADVISE_SEQUENTIAL) {
		*advice ^= ADVISE_SEQUENTIAL;
		return MADV_SEQUENTIAL;
	}
#endif

#ifdef MADV_WILLNEED
	if(*advice & ADVISE_WILLNEED) {
		*advice ^= ADVISE_WILLNEED;
		return MADV_WILLNEED;
	}
#endif

#ifdef MADV_DONTNEED
	if(*advice & ADVISE_DONTNEED) {
		*advice ^= ADVISE_DONTNEED;
		return MADV_DONTNEED;
	}
#endif

#ifdef MADV_REMOVE
	if(*advice & ADVISE_REMOVE) {
		*advice ^= ADVISE_REMOVE;
		return MADV_REMOVE;
	}
#endif

#ifdef MADV_DONTFORK
	if(*advice & ADVISE_DONTFORK) {
		*advice ^= ADVISE_DONTFORK;
		return MADV_DONTFORK;
	}
#endif

#ifdef MADV_DOFORK
	if(*advice & ADVISE_DOFORK) {
		*advice ^= ADVISE_DOFORK;
		return MADV_DOFORK;
	}
#endif

#ifdef MADV_HWPOISON
	if(*advice & ADVISE_HWPOISON) {
		*advice ^= ADVISE_HWPOISON;
		return MADV_HWPOISON;
	}
#endif

#ifdef MADV_MERGEABLE
	if(*advice & ADVISE_MERGEABLE) {
		*advice ^= ADVISE_MERGEABLE;
		return MADV_MERGEABLE;
	}
#endif

#ifdef MADV_UNMERGEABLE
	if(*advice & ADVISE_UNMERGEABLE) {
		*advice ^= ADVISE_UNMERGEABLE;
		return MADV_UNMERGEABLE;
	}
#endif

#ifdef MADV_HUGEPAGE
	if(*advice & ADVISE_HUGEPAGE) {
		*advice ^= ADVISE_HUGEPAGE;
		return MADV_HUGEPAGE;
	}
#endif

#ifdef MADV_NO_HUGEPAGE
	if(*advice & ADVISE_NO_HUGEPAGE) {
		*advice ^= ADVISE_NO_HUGEPAGE;
		return MADV_NOHUGEPAGE;
	}
#endif

#ifdef MADV_COLLAPSE
	if(*advice & ADVISE_COLLAPSE) {
		*advice ^= ADVISE_COLLAPSE;
		return MADV_COLLAPSE;
	}
#endif

#ifdef MADV_DONTDUMP
	if(*advice & ADVISE_DONTDUMP) {
		*advice ^= ADVISE_DONTDUMP;
		return MADV_DONTDUMP;
	}
#endif

#ifdef MADV_DODUMP
	if(*advice & ADVISE_DODUMP) {
		*advice ^= ADVISE_DODUMP;
		return MADV_DODUMP;
	}
#endif

#ifdef MADV_FREE
	if(*advice & ADVISE_FREE) {
		*advice ^= ADVISE_FREE;
		return MADV_FREE;
	}
#endif

#ifdef MADV_WIPEONFORK
	if(*advice & ADVISE_WIPEONFORK) {
		*advice ^= ADVISE_WIPEONFORK;
		return MADV_WIPEONFORK;
	}
#endif

#ifdef MADV_KEEPONFORK
	if(*advice & ADVISE_KEEPONFORK) {
		*advice ^= ADVISE_KEEPONFORK;
		return MADV_KEEPONFORK;
	}
#endif

#endif
}

struct libmapvise_map {
	void *ptr;
	size_t len;
};

static inline int libmapvise_munmap_anon(struct libmapvise_map *file) {
#ifdef _WIN32
	int ret = VirtualFree(file->ptr, 0, MEM_RELEASE);
	if(ret == 0) {
		return GetLastError();
	}
	return 0;
#else
	int ret = munmap(file->ptr, file->len);
	if(ret) {
		return errno;
	}
	return 0;
#endif
}

static inline struct libmapvise_map libmapvise_mmap_anon(size_t size) {
	struct libmapvise_map out;
	out.len = size;
#ifdef _WIN32
	LPVOID ptr = VirtualAlloc(NULL, size, MEM_COMMIT, PAGE_READWRITE);
	if(ptr == NULL) {
		out.ptr = NULL;
		out.len = GetLastError();
		return out;
	}
	out.ptr = ptr;
	return out;
#else
	void* ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if(ptr == MAP_FAILED) {
		out.ptr = NULL;
		out.len = errno;
		return out;
	}
	out.ptr = ptr;
	return out;
#endif
}

#ifdef _WIN32
static inline uint64_t libmapvise_mmap_file_advise_convert(uint64_t advice) {
	uint64_t new_advice = FILE_ATTRIBUTE_NORMAL;

	if(new_advice & ADVISE_RANDOM) {
		new_advice |= FILE_FLAG_RANDOM_ACCESS;
	}
	if(new_advice & ADVISE_SEQUENTIAL) {
		new_advice |= FILE_FLAG_SEQUENTIAL_SCAN;
	}

	return new_advice;
}
#endif

static inline int libmapvise_munmap_file(struct libmapvise_map *file) {
#ifdef _WIN32
	return UnmapViewOfFile(file->ptr);
#else
	return munmap(file->ptr, file->len);
#endif
}
static inline int libmapvise_munmap_file_iserr(int err) {
#ifdef _WIN32
	return err == 0;
#else
	return err != 0;
#endif
}

static inline int libmapvise_madvise(void *ptr, size_t len, uint64_t advice) {
#ifdef _WIN32
	if(advice & ADVISE_WILLNEED) {
		WIN32_MEMORY_RANGE_ENTRY entry[1];
		entry[0].VirtualAddress = ptr;
		entry[0].NumberOfBytes = len;
		int ret = PrefetchVirtualMemory(GetCurrentProcess(), 1, entry, 0);
		if(ret) {
			return 0;
		}
		else {
			return -1;
		}
	}

	if(advice & ADVISE_DONTNEED || advice & ADVISE_FREE) {
		return DiscardVirtualMemory(ptr, len);
	}

	return 0;
#else
	while(advice) {
		uint64_t new_advice = libmapvise_advice_transform(&advice);
		int ret = madvise(ptr, len, new_advice);
	}

#endif
}

static inline struct libmapvise_map libmapvise_mmap_file(const char *file, uint64_t advice) {
	struct libmapvise_map out;
	out.ptr = NULL;
#ifdef _WIN32
	HANDLE hFile;
	uint64_t new_advice = libmapvise_mmap_file_advise_convert(advice);
	hFile = CreateFileA(file,
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		new_advice,
		NULL);

	if (hFile == INVALID_HANDLE_VALUE) {
		out.len = GetLastError();
		return out;
	}

	LARGE_INTEGER size;
	GetFileSizeEx(hFile, &size);
	out.len = size.QuadPart;

	HANDLE hMapFile;
	hMapFile = CreateFileMapping(
		hFile,
		NULL,
		PAGE_READWRITE,
		0,
		0,
		NULL);

	if (hMapFile == NULL) {
		out.len = GetLastError();
		CloseHandle(hFile);
		return out;
	}

	LPVOID mapView;
	mapView = MapViewOfFile(
		hMapFile,
		FILE_MAP_READ | FILE_MAP_WRITE,
		0,
		0,
		0);

	if (mapView == NULL) {
		out.len = GetLastError();
		CloseHandle(hMapFile);
		CloseHandle(hFile);
		return out;
	}

	CloseHandle(hFile);
	CloseHandle(hMapFile);

	out.ptr = mapView;

	return out;
#else
	int fd = open(file, O_RDWR);
	if(fd == -1) {
		out.len = errno;
		return out;
	}
	struct stat fileStat;
	if (fstat(fd, &fileStat) == -1) {
		out.len = errno;
		close(fd);
		return out;
	}

	size_t len = fileStat.st_size;

	void* mappedData = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (mappedData == MAP_FAILED) {
		close(fd);
		out.len = errno;
		return out;
	}

	out.len = len;

	close(fd);
	out.ptr = mappedData;
	if(advice) {
		libmapvise_madvise(mappedData, len, advice);
	}
	return out;

#endif
}
