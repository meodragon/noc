#include <rca.h>
#include <common_knowledge.h>

#include <sys/time.h>

#include <time.h>
#include <stdlib.h>

/*
 * arg: rca_replicated_state_machine
 */
void *
rca_run(void* machine_ptr)
{
    rca_replicated_state_machine* machine = (rca_replicated_state_machine*)machine_ptr;
    for (;;) {

        switch (machine->state) {
            case FOLLOWER: {
                pthread_mutex_lock(&machine->lock);

                const struct timespec abstime = noc_add_timespec_ms(500);
                int error = pthread_cond_timedwait(&machine->elect, &machine->lock, &abstime);
                if (!error) {

                } else if (error == ETIMEDOUT) {
                    machine->current_term++;
                    machine->state = CANDIDATE;
                } else {
                    printf("pthread cond timedwait %d\n", error);
                    exit(EXIT_FAILURE);
                }
                pthread_mutex_unlock(&machine->lock);
                break;
            }
            case CANDIDATE: {
                break;
            }
            case LEADER: {
                break;
            }
        }
    }
}

void *
rca_apply(rca_replicated_state_machine* machine)
{
    for (;;) {
        if (machine->commit_index > machine->last_applied) {
            int err = rca_log_append(last_applied);
            if (err) {
                printf("rca log append %d\n", last_applied);
                machine->suspend = true;
                break;
            }
            machine->last_applied++;
        }
    }
}

/*
 * Local log append
 *
 * RETURNS
 * 0 err if success, otherwise:
 *
 */
int
rca_log_append(int last_applied)
{

}
