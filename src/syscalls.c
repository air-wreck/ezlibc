/* these are C+asm syscall wrappers

   the implementations are system/architecture dependent; it defaults to
   32-bit x86 Linux; right now, you can specify -D_OSX for OS X + BSD
   ON LINUX ONLY you can specify -D_x64 for 64-bit architectures */

#include "syscalls.h"

#ifdef _x64
  const int ez_arch = 64;
#else
  const int ez_arch = 32;
#endif


/***********************
* OS X and BSD systems *
***********************/
#ifdef _OSX

void
ez_sys_exit(int status)
{
  __asm__ volatile (
    "movl $1, %%eax;"
    "pushl %0;"
    "pushl %%eax;"
    "int $0x80;"
    :: "g" (status)
    : "eax"
  );
}

int
ez_sys_read(int fd, char *buf, int len)
{
  int n_bytes;
  __asm__ (
    "movl $3, %%eax;"
    "pushl %2;"
    "pushl %3;"
    "pushl %1;"
    "pushl %%eax;"
    "int $0x80;"
    "addl $16, %%esp;"
    : "=a" (n_bytes)
    : "g" (fd), "g" (len), "g" (buf)
    : "esp"
  );
  return n_bytes;
}

int
ez_sys_write(int fd, const char *msg, int len)
{
  __asm__ (
    "movl $4, %%eax;"
    "pushl %3;"
    "pushl %2;"
    "pushl %1;"
    "pushl %%eax;"  /* needed to inline the interrupt in BSD */
    "int $0x80;"
    "addl $16, %%esp;"
    : "=a" (len)
    : "g" (fd), "g" (msg), "g" (len)
    : "esp"
  );
  return len;
}


/****************
* Linux systems *
****************/
#else
  #ifdef _x64  /** 64-bit **/
    void
    ez_sys_exit(int status)
    {
      const int syscall_no = 60;
      __asm__ volatile (
        "syscall;"
        :: "a" (syscall_no), "D" (status)
      );
    }

    int
    ez_sys_read(int fd, char *buf, int len)
    {
      const int syscall_no = 0;
      int n_bytes;
      __asm__ (
        "syscall;"
        : "=a" (n_bytes)
        : "a" (syscall_no), "D" (fd), "S" (buf), "d" (len)
      );
      return n_bytes;
    }

    int
    ez_sys_write(int fd, const char *msg, int len)
    {
      const int syscall_no = 1;
      __asm__ (
        "syscall;"
        : "=a" (len)
        : "a" (syscall_no), "D" (fd), "S" (msg), "d" (len)
      );
      return len;
    }

    void*
    ez_sys_mmap(void *addr, unsigned int len, int prot,
                int flags, int fd, int offset)
    {
      const int syscall_no = 9;
      void *ptr;
      __asm__ (
        "pushq %%r10;"  /* save original values of %r10, %r9, %r8 */
        "pushq %%r9;"
        "pushq %%r8;"
        "movq %5, %%r10;"  /* move args into appropriate registers */
        "movq %6, %%r8;"
        "movq %7, %%r9;"
        "syscall;"
        "popq %%r8;"  /* restore register values */
        "popq %%r9;"
        "popq %%r10;"
        : "=a" (ptr)
        : "a" (syscall_no), "D" (addr), "S" (len), "d" (prot),
          "g" (flags), "g" (fd), "g" (offset)
        : "r10", "r9", "r8"
      );
      return ptr;
    }

    int
    ez_sys_munmap(void *addr, unsigned int len)
    {
      const int syscall_no = 11;
      int ret;
      __asm__ (
        "syscall;"
        : "=a" (ret)
        : "a" (syscall_no), "D" (addr), "S" (len)
      );
      return ret;
    }

  #else  /** 32-bit **/
    void
    ez_sys_exit(int status)
    {
      const int syscall_no = 1;
      __asm__ volatile (
        "int $0x80;"
        :: "a" (syscall_no), "b" (status)
      );
    }

    int
    ez_sys_read(int fd, char *buf, int len)
    {
      const int syscall_no = 3;
      int n_bytes;
      __asm__ (
        "int $0x80;"
        : "=a" (n_bytes)
        : "a" (syscall_no), "b" (fd), "c" (buf), "d" (len)
      );
      return n_bytes;
    }

    int
    ez_sys_write(int fd, const char *msg, int len)
    {
      const int syscall_no = 4;
      __asm__ (
        "int $0x80;"
        : "=a" (len)
        : "a" (syscall_no), "b" (fd), "c" (msg), "d" (len)
      );
      return len;
    }

    void*
    ez_sys_mmap(void *addr, unsigned int len, int prot,
                int flags, int fd, int offset)
    {
      struct ez_mmap_arg_struct args;
      args.addr = (unsigned long) addr;
      args.len = len;
      args.prot = prot;
      args.flags = flags;
      args.fd = fd;
      args.offset = offset;
      
      void *ptr;
      const int syscall_no = 90;
      __asm__ (
        "int $0x80;"
        : "=a" (ptr)
        : "a" (syscall_no), "b" (&args)
      );
      return ptr;
    }

    int
    ez_sys_munmap(void *addr, unsigned int len)
    {
      const int syscall_no = 91;
      int ret;
      __asm__ (
        "int $0x80;"
        : "=a" (ret)
        : "a" (syscall_no), "b" (addr), "c" (len)
      );
      return ret;
    }
  #endif
#endif
