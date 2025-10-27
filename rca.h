/*
 * Raft Consensus Algorithm
*/
#ifndef RCA_H
#define RCA_H

#include <pthread.h>

enum RCA_REPLICATED_STATE_MACHINE_STATE { FOLLOWER, CANDIDATE, LEADER };

typedef struct rca_log {
	int text_size;
	char *text;
	int term;
	int index;
} rca_log;

typedef struct rca_replicated_state_machine {
	int current_term;
	int voted_for;
	struct {
		int log_offset;
		int log_size;
		rca_log *log;
	};

	int commit_index;
	int last_applied;

	int server_count;
	int *next_index;
	int *match_index;

	/* noc defines */
	enum RCA_REPLICATED_STATE_MACHINE_STATE state;
    pthread_mutex_t lock;
    pthread_cond_t elect;
    int id;

} rca_replicated_state_machine;

typedef struct rca_request_vote_in {
    int term;
    int candidate_id;
    int last_log_index;
    int last_log_term;
} rca_request_vote_in;

typedef struct rca_request_vote_ou {
    int term;
    int vote_granted;
} rca_request_vote_ou;

typedef struct rca_append_entries_in {
    int term;
    int leader_id;
    int prev_log_index;
    int prev_log_term;
    struct {
        int entry_count;
        rca_log entries;
    };
    int leader_commit;
} rca_append_entries_in;

typedef struct rca_append_entries_ou {
    int term;
    bool success;
};

rca_request_vote_ou rca_process_request_vote(rca_request_vote_in);
rca_append_entries_ou rca_process_append_entries(rca_append_entries_in);

#endif
