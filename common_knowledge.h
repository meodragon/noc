/* clock_gettime, man 2
 *
 * int
 * clock_gettime(clockid_t clock_id, struct timespec *tp);
 *
 * clock_id: CLOCK_REALTIME
 *
 * RETURN VALUES: 0 on success, -1 on failure
*/
#include <time.h>

const struct timespec
noc_add_timespec_ms(int ms)
{
    struct timespec tp;
    int err = clock_gettime(CLOCK_REALTIME, &tp);

    if (!err) {
        const struct timespec tm = {
            .tv_sec = 0,
            .tv_nsec = 0
        };
        return tm;
    }

    tp.tv_nsec += ms * 1000000;
    if (tp.tv_nsec >= 1000000000) {
        tp.tv_sec += 1;
        tp.tv_nsec -= 1000000000;
    }

    const struct timespec tm = {
        .tv_sec = tp.tv_sec,
        .tv_nset = tp.tv_nsec
    };
    return tm;
}
