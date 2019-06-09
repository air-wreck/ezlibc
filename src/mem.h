/* src/mem.h
 *
 * this file implements various memory-management utilities */

/* we include src/io.h for the definition of EZ_NULL */
#include "io.h"

#ifndef EZ_MEM_
#define EZ_MEM

void*
ez_unsafe_do_malloc(int size);

void*
ez_malloc(int size);

void*
ez_calloc(int len, int mem_size);

void
ez_free(void *ptr);

void*
ez_memset(const void *buf, char c, unsigned int len);

void*
ez_memcpy(void *dst, const void *src, unsigned int len);

#endif
