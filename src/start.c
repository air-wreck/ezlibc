/* implements global entry point (_start)

   argc and argv are not supported on OS X
   it also doesn't work on 64-bit Linux yet, but I'm working on that */

#include "start.h"
#include "syscalls.h"

void
ez_exit(int status)
{
  ez_sys_exit(status);
}

/** OS X and BSD **/
#ifdef _OSX
void
_start()  /* argc/argv not supported on OS X */
{
  int status = main();
  ez_exit(status);
}

/** Linux **/
#else
  #ifdef _x64  /** 64-bit, which is buggy **/
    __asm__ (  /* TODO: combine this with x86 */
      ".global _start;"
      ".global main;"
      ".global ez_exit;"
      "_start:;"
      "  movq %rsp, %rax;"
      "  addq $8, %rax;"
      "  pushq %rax;"
      "  pushq 8(%rsp);"
      "  call main;"
      "  addq $16, %rsp;"
      "  pushq %rax;"
      "  call ez_exit;"
    );

  #else  /** 32-bit **/
    __asm__ (
      ".global _start;"
      ".global main;"
      ".global ez_exit;"
      "_start:;"
      "  movl %esp, %eax;"  /* argv */
      "  addl $4, %eax;"
      "  pushl %eax;" 
      "  pushl 4(%esp);"    /* argc */
      "  call main;"
      "  addl $8, %esp;"
      "  pushl %eax;"
      "  call ez_exit;"
    );
  #endif
#endif

