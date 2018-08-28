/* ezlibc/syscalls.h

syscall wrappers */

#ifndef EZ_SYS_
#define EZ_SYS_

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
