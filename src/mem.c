#include "syscalls.h"
#include "mem.h"

/* for malloc, these are the appropriate mmap settings */
#define EZ_PROT (EZ_SYS_MMAP_PROT_READ | EZ_SYS_MMAP_PROT_WRITE)
#define EZ_FLAGS (EZ_SYS_MMAP_MAP_PRIVATE | EZ_SYS_MMAP_MAP_ANONYMOUS)

/* these arrays hold ptr/len info for malloc
 * we can always malloc/realloc more space if we need it */
#define EZ_MALLOC_INIT_SIZE 10
unsigned int EZ_MALLOC_TABLE_SIZE = 0;
void **ez_malloc_ptr;
unsigned int *ez_malloc_len;

void
ez_malloc_grow_table(int len)
{
  /* expand the global mapping table size to (len) */
  void **new_ptr = ez_sys_mmap(EZ_NULL, len * sizeof(void *),
                               EZ_PROT, EZ_FLAGS, -1, 0);
  unsigned int *new_len = ez_sys_mmap(EZ_NULL, len * sizeof(int),
                                      EZ_PROT, EZ_FLAGS, -1, 0);

  /* clear newly allocated memory */
  unsigned int i;
  for (i = 0; i < EZ_MALLOC_TABLE_SIZE; i++) {
    new_ptr[i] = EZ_NULL;
    new_len[i] = 0;
  }

  /* copy over old data into new arrays */
  ez_memcpy(new_ptr, ez_malloc_ptr, EZ_MALLOC_TABLE_SIZE * sizeof(void *));
  ez_memcpy(new_len, ez_malloc_len, EZ_MALLOC_TABLE_SIZE * sizeof(int));

  /* unless that was the original global table, we should free
   * the previous table */
  if (EZ_MALLOC_TABLE_SIZE > 0) {
    ez_sys_munmap(ez_malloc_ptr, EZ_MALLOC_TABLE_SIZE * sizeof(void *));
    ez_sys_munmap(ez_malloc_len, EZ_MALLOC_TABLE_SIZE * sizeof(int));
  }

  ez_malloc_ptr = new_ptr;
  ez_malloc_len = new_len;
  EZ_MALLOC_TABLE_SIZE = len;
}

void*
ez_malloc(int size)
{
  /* this is an ugly implementation with an mmap/munmap syscall
   * for everything; once I get this working, I'll probably write
   * a more sophisticated version */

  /* if size is zero, the Standard says to return NULL */
  if (size == 0)
    return EZ_NULL;

  /* if this is the first run of malloc, initialize the global
   * mapping arrays */
  if (EZ_MALLOC_TABLE_SIZE == 0)
    ez_malloc_grow_table(EZ_MALLOC_INIT_SIZE);

  /* get first available index in global mapping array */
  int index = -1;
  unsigned int i;
  for (i = EZ_MALLOC_TABLE_SIZE; i > 0; i--) {
    if (ez_malloc_ptr[i - 1] == EZ_NULL) {
      index = i - 1;
    }
  }
  
  /* if the global arrays are running low, we should expand them
   * we will malloc a new array with double the space */
  if (EZ_MALLOC_TABLE_SIZE - index < 3)
    ez_malloc_grow_table(EZ_MALLOC_TABLE_SIZE * 2);
  
  void *ptr = ez_sys_mmap(EZ_NULL, size, EZ_PROT, EZ_FLAGS, -1, 0);
  ez_malloc_ptr[index] = ptr;
  ez_malloc_len[index] = size;
  return ptr;
}

void*
ez_calloc(int len, int mem_size)
{
  unsigned int total_size = len * mem_size;
  void *ptr = ez_malloc(total_size);
  
  /* clear allocated memory */
  ez_memset(ptr, 0, total_size);

  return ptr;
}

void
ez_free(void *ptr)
{
  if (ptr == EZ_NULL)
    return;

  /* find index of *ptr in global mapping table */
  unsigned int index = 0;
  unsigned int i;
  for (i = 0; i < EZ_MALLOC_TABLE_SIZE; i++) {
    if (ez_malloc_ptr[i] == ptr) {
      index = i;
      break;
    }
  }

  /* de-allocate the memory */
  ez_sys_munmap(ptr, ez_malloc_len[index]);

  /* shift all the elements in the global mapping table down */
  for (i = index + 1; i < EZ_MALLOC_TABLE_SIZE; i++) {
    ez_malloc_ptr[i - 1] = ez_malloc_ptr[i];
    ez_malloc_len[i - 1] = ez_malloc_len[i];
  }
  ez_malloc_ptr[EZ_MALLOC_TABLE_SIZE - 1] = EZ_NULL;
  ez_malloc_len[EZ_MALLOC_TABLE_SIZE - 1] = 0;
}

void*
ez_memset(const void *buf, char c, unsigned int len)
{
  char *str = (char *)buf;
  unsigned int i;
  for (i = 0; i < len; i++) {
    str[i] = c;
  }
  return (void *)str;
}

void*
ez_memcpy(void *dst, const void *src, unsigned int len)
{
  char *dst_str = (char *)dst;
  char *src_str = (char *)src;
  unsigned int i;
  for (i = 0; i < len; i++) {
    dst_str[i] = src_str[i];
  }
  return dst;
}

