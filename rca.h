/*
 * Raft Consensus Algorithm
*/
#ifndef RCA_H
#define RCA_H

typedef struct rca_log {
	int text_size;
	char *text;
	int term;
	int index;
} rca_log;

typedef struct rca_state {
	int current_term;
	int voted_for;
	struct {
		int log_size;
		rca_log *log;
	};
	
	int commit_index;
	int last_applied;


	int server_count;
	int *next_index;
	int *match_index;	
} rca_state;

typedef struct rca_request_vote_in {
} rca_request_vote_in;

typedef struct rca_request_vote_ou {
} rca_request_vote_ou;

typedef struct rca_append_entries_in {
} rca_append_entries_in;

int rca_process_request_vote();
int rca_process_append_entries();

#endif
