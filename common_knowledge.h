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
#include <stdio.h>
#include <stdlib.h>

typedef struct noc_rca_instance_conf {
    int id;
    int url;
} noc_rca_instance_conf;

typedef struct noc_rca_conf {
    int instance_count;
    noc_rca_instance_conf *instance_conf_list;
} noc_rca_conf;

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
        .tv_nsec = tp.tv_nsec
    };
    return tm;
}

int
noc_rca_read_conf(const char* filepath)
{
    FILE* fptr = fopen(filepath, "r");
    if (fptr == NULL) {
        printf("fopen \n");
        return 1;
    }
    int err = fseek(fptr, 0L, SEEK_END);
    if (err != 0) {
        printf("fseek \n");
        fclose(fptr);
        return 1;
    }
    long pos_end = ftell(fptr);

    char *config = calloc(pos_end, sizeof(char));

    (void)rewind(fptr);
    size_t fpos = fread((void*)config, pos_end, 1, fptr);
    printf("object count %ld\n", fpos);
    printf("config %s\n", config);

    free(config);
    fclose(fptr);
    return 0;
}
