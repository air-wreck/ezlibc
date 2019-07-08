/* implements global entry point (_start)

   OS X testing is generally lagging behind */

/* TODO: apparently, the C99 standard specifies that
 * argv[argc] should return a null pointer, not segfault */

#include "start.h"
#include "syscalls.h"

/** OS X and BSD **/
#ifdef _OSX
__asm__ (
  ".global _start;"
  ".global main;"
  ".global ez_sys_exit;"
  "_start:;"
  "  movl %%esp, %%eax;"  /* argv */
  "  addl $4, %%eax;"
  "  pushl %%eax;"
  "  pushl 4(%%esp);"     /* argc */
  "  call main;"
  "  addl $8, %%esp;"
  "  pushl %%eax;"        /* return status */
  "  call ez_sys_exit;"
)

/** Linux **/
#else
  #ifdef _x64  /** 64-bit **/
    /* not sure why, but a wrapper is needed on x64 */
    void ez_wrap_exit(int status) {
      ez_sys_exit(status);
    }

    __asm__ (
      ".global _start;"
      ".global main;"
      ".global ez_wrap_exit;"
      "_start:;"
      "  movq (%rsp), %rdi;"  /* argc */
      "  movq %rsp, %rsi;"    /* argv */
      "  addq $8, %rsi;"
      "  call main;"
      "  movq %rax, %rdi;"
      "  call ez_wrap_exit;"
    );

  #else  /** 32-bit **/
    __asm__ (
      ".global _start;"
      ".global main;"
      ".global ez_sys_exit;"
      "_start:;"
      "  movl %esp, %eax;"  /* argv */
      "  addl $4, %eax;"
      "  pushl %eax;" 
      "  pushl 4(%esp);"    /* argc */
      "  call main;"
      "  addl $8, %esp;"
      "  pushl %eax;"
      "  call ez_sys_exit;"
    );
  #endif
#endif

