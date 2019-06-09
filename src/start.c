/* implements global entry point (_start)

   OS X testing is generally lagging behind */

#include "start.h"
#include "syscalls.h"

void
ez_exit(int status)
{
  ez_sys_exit(status);
}

/** OS X and BSD **/
#ifdef _OSX
__asm__ (
  ".global _start;"
  ".global main;"
  ".global ez_exit;"
  "_start:;"
  "  movl %%esp, %%eax;"  /* argv */
  "  addl $4, %%eax;"
  "  pushl %%eax;"
  "  pushl 4(%%esp);"     /* argc */
  "  call main;"
  "  addl $8, %%esp;"
  "  pushl %%eax;"        /* return status */
  "  call ez_exit;"
)

/** Linux **/
#else
  #ifdef _x64  /** 64-bit **/
    __asm__ (
      ".global _start;"
      ".global main;"
      ".global ez_exit;"
      "_start:;"
      "  movq (%rsp), %rdi;"  /* argc */
      "  movq %rsp, %rsi;"    /* argv */
      "  addq $8, %rsi;"
      "  call main;"
      "  movq %rax, %rdi;"
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

