#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"

#include "threads/vaddr.h"

static void syscall_handler (struct intr_frame *);

void check_valid_pointer (const void *vaddr);
void exit (int status);

void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
syscall_handler (struct intr_frame *f UNUSED) 
{
	check_valid_pointer ((const void *)(f->esp));

 	switch (*(int *)(f->esp))
 	{
 		/*
 		case SYS_HALT:

  			break;
  		*/
  		case SYS_EXIT:
  			check_valid_pointer ((const void *)(f->esp + 4));
  			exit (*(const char *)(f->esp + 4));
  			break;
  		/*
  		case SYS_EXEC:

  			break;
  		case SYS_WAIT:

  			break;
  		case SYS_CREATE:

  			break;
  		case SYS_REVOVE:

  			break;
  		case SYS_OPEN:

  			break;
  		case SYS_FILESIZE:

  			break;
  		case SYS_FILESIZE:

  			break;
  		case SYS_READ:

  			break;
  		case SYS_WRITE:

  			break;
  		case SYS_SEEK:

  			break;
  		case SYS_TELL:

  			break;
  		case SYS_CLOSE:

  			break;
  		*/
 	 	default:
			printf ("system call!\n");
  			thread_exit ();
 	}
}

void
check_valid_pointer (const void *vaddr)
{
	if (!is_user_vaddr (vaddr))
		exit(-1);
}

void
exit (int status)
{
	struct thread *curr = thread_current ();

	printf ("%s: exit(%d)\n", curr->name, status);
	thread_exit ();
}