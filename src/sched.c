#include "sched.h"
#include "irq.h"
#include "printf.h"
#include "timer.h"

static struct task_struct init_task = INIT_TASK;
struct task_struct *current = &(init_task);
struct task_struct * run_queue[NR_TASKS] = {};
struct task_struct * wait_queue[NR_TASKS] = {};
int nr_tasks = 1;

void preempt_disable(void)
{
	current->preempt_count++;
}

void preempt_enable(void)
{
	current->preempt_count--;
}

struct task_struct * dequeue_rqtask()
{
	struct task_struct * next;
	int i;

	next = run_queue[0];

	/* left shift array by 1 */
	for(i = 0; i < NR_TASKS-1; )
	{
		if(!run_queue[i])
			break;
		run_queue[i] = run_queue[++i];
	}
	run_queue[i] = 0;
	return next;
}

static unsigned int get_rq_insert_index(struct task_struct * task)
{
	unsigned int lower_index, upper_index, middle_index;

	lower_index = 0;
	upper_index = NR_TASKS -1 ;
	printf("upper_index: %d\r\n", upper_index);
	while(lower_index < upper_index)
	{
		middle_index = (upper_index - lower_index)/2;
		//printf("middle_index: %d\r\n", middle_index);
		//printf("middle_item: 0x%0x\r\n", run_queue[middle_index]);
		if(!run_queue[middle_index] || 
		   task->vruntime < run_queue[middle_index]->vruntime)
		{
			upper_index = middle_index - 1;
		}
		else
		{
			lower_index = middle_index + 1;
		}
	};

	printf("lower_index: %d\r\n", lower_index);
	printf("task runtime: %d\r\n", task->vruntime);
	if(run_queue[lower_index] &&
		 (run_queue[lower_index]->vruntime == task->vruntime))
		return lower_index + 1;
	else
		return lower_index;
}

static void insert_in_rq(struct task_struct * task, unsigned int task_index)
{
	struct task_struct *tmp, *next;
	unsigned index;

	tmp = run_queue[task_index];
	printf("new task pointer: 0x%0x\r\n", task);
	run_queue[task_index] = task;

	/* right shift array by 1 */
	for(index = task_index+1; index<NR_TASKS-1; index++)
	{
		next = run_queue[index];
		if(!next)
			break;
		run_queue[index] = tmp;
		tmp = next;		
	}
	run_queue[index] = tmp;
}

void enque_rqtask(struct task_struct * task)
{
	unsigned int index;

	index = get_rq_insert_index(task);
	printf("index for new task: %d\r\n", index);
	insert_in_rq(task, index);
}

/*
Description: This is the core function to schedule the next process from
	     run-queue.
Arguments: next state of the process.
*/
void _schedule(long state)
{
	preempt_disable();
	struct task_struct * p;

	printf("%s: vruntime of the current: %u is  %u\r\n", __func__, current->id, current->vruntime);
	p = dequeue_rqtask();
	printf("%s: next task pointer: 0x%0x\r\n", __func__, p);
	if (state == TASK_WAITING)
		wait_queue[current->id] = current;
	else
		enque_rqtask(current);
	p->state = TASK_RUNNING;
	switch_to(p);
	preempt_enable();
}

/*
Description: This function move the task from wait-queue to run-queue.
Arguments: task_id 
*/
void wakeup_task(unsigned int task_id)
{
	preempt_disable();
	wait_queue[task_id]->state = TASK_READY;
	enque_rqtask(wait_queue[task_id]);
	wait_queue[task_id] = 0;
	preempt_enable();
}

void schedule(void)
{
	printf("%s: vruntime of the current: %u is  %u\r\n", __func__, current->id, current->vruntime);
	if(current->vruntime < MIN_GRANUALITY)
		return;
	if(current->vruntime < MIN_QRUNTIME)
		return;
	_schedule(TASK_RUNNING);
}

void switch_to(struct task_struct * next) 
{
	struct task_struct * prev;

	if (current == next) 
		return;
	next->exec_start_time = jiffies_to_nsec(jiffies);	
	prev = current;
	current = next;
	cpu_switch_to(prev, next);
}

void schedule_tail(void) 
{
	preempt_enable();
}

static unsigned long calc_delta_fair(unsigned long delta, unsigned long prio)
{
	delta -= (prio * delta)/(2 * MAX_PRIO) ;
	return delta;
}

/*
Description: This function update the time stats of current process.
Arguments: None
*/
void update_curr()
{
	unsigned long delta;

//	if(current->vruntime == MAX_RUNTIME)
//		return;
	printf("%s: current jiffies: %u\r\n", __func__, jiffies_to_nsec(jiffies));
	printf("%s: current exec time: %u\r\n", __func__, current->exec_start_time);
	delta = jiffies_to_nsec(jiffies) - current->exec_start_time;
	printf("%s: delta of the current: %u is  %u\r\n", __func__, current->id, delta);
	current->exec_start_time = jiffies_to_nsec(jiffies);
	delta = calc_delta_fair(delta, current->priority);
	printf("%s: fair delta of the current: %u is  %u\r\n", __func__, current->id, delta);
	current->vruntime += delta;		
	printf("%s: vruntime of the current: %u is  %u\r\n", __func__, current->id, current->vruntime);
}

void timer_tick()
{
	update_curr();
	printf("%s: Current preempt count:%d\r\n", __func__, current->preempt_count );
	if (current->preempt_count > 0)
        	return;

	unmask_irq();
	printf("%s: test Current preempt count:%d \r\n", __func__, current->preempt_count );
	schedule();
	mask_irq();
}
