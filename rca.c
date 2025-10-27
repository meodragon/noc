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
        if (machine->suspend) {
            printf("rca %d run suspend\n", machine->id);
            break;
        }

        switch (machine->state) {
            case FOLLOWER: {
                pthread_mutex_lock(&machine->lock);

                const struct timespec abstime = noc_add_timespec_ms(500);
                int error = pthread_cond_timedwait(&machine->elect, &machine->lock, &abstime);
                if (error == ETIMEDOUT) {
                    machine->current_term++;
                    machine->state = CANDIDATE;
                    rca_persist(machine);
                } else if (error) {
                    printf("pthread cond timedwait %d\n", error);
                    machine->suspend = true;
                    //exit(EXIT_FAILURE);
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
        if (machine->suspend) {
            printf("rca %d apply: suspend\n", machine->id);
            break;
        }
        if (machine->commit_index > machine->last_applied) {
            pthread_mutex_lock(&machine->lock);
            ++machine->last_applied;
            rca_persist(machine);
            int err = rca_log_append(machine, last_applied);
            if (err) {
                printf("rca %d log append %d (err:%d)\n", machine->id, last_applied, err);
                // machine->suspend = true;
            }
            pthread_mutex_unlock(&machine->lock);
        }
    }
}

/*
 * Use inside a critical section. Persist state.
 *
 * RETURNS
 *
 */
int
rca_persist(rca_replicated_state_machine* machine)
{

}

/*
 * Local log append.
 * At this point, last-applied increased, after persistence, the
 * log[last-applied] is available on local file. This subroutine task should be
 * optional and the error code can be ignore.
 *
 * RETURNS
 * 0 err if success, otherwise:
 *
 */
int
rca_log_append(rca_replicated_state_machine* machine, int last_applied)
{

}
