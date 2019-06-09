/* ezlibc/syscalls.h

syscall wrappers */

#ifndef EZ_SYS_
#define EZ_SYS_

/* TODO: check if these work on other systems
 * TODO: might as well complete the list */
#ifndef _OSX
  #ifndef _x64
    #define EZ_SYS_MMAP_PROT_READ (0x1)
    #define EZ_SYS_MMAP_PROT_WRITE (0x2)
    #define EZ_SYS_MMAP_MAP_ANONYMOUS (0x20)
    #define EZ_SYS_MMAP_MAP_PRIVATE (0x02)

    void*
    ez_sys_mmap(void *addr, unsigned int len, int prot,
                int flags, int fd, int offset);
    
    void ez_sys_munmap(void *addr, unsigned int len);
  #endif
#endif

/* exit process

   parameters:
   int status: exit status */
void
ez_sys_exit(int status);

/* read from stream

   parameters:
   int fd: file descriptor
   char *buf: buffer to read to
   int len: number of bytes to read

   returns:
   int len: number of bytes read */
int
ez_sys_read(int fd, char *buf, int len);

/* write to stream

   parameters:
   int fd: file descriptor
   cont char *msg: buffer to write from
   int len: numbe rof bytes to write

   returns:
   int len: number of bytes written */
int
ez_sys_write(int fd, const char *msg, int len);

#endif
