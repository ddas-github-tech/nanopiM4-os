#include "mm.h"
#include "sched.h"
#include "entry.h"
#include "printf.h"

int copy_process(unsigned long fn, unsigned long arg)
{
	preempt_disable();
	struct task_struct *p;

	p = (struct task_struct *) get_free_page();
	if (!p)
		return 1;
	printf("memory address for this task: 0x%0x\r\n", p);
	p->priority = current->priority;
	p->state = TASK_RUNNING;
	p->preempt_count = 1; //disable preemtion until schedule_tail

	p->cpu_context.x19 = fn;
	p->cpu_context.x20 = arg;
	p->cpu_context.pc = (unsigned long)ret_from_fork;
	p->cpu_context.sp = (unsigned long)p + THREAD_SIZE;
	p->vruntime = 0;
	p->id = nr_tasks++;
	enque_rqtask(p);
	// enque_task
	 // task[pid] = p;	
	preempt_enable();
	return 0;
}
