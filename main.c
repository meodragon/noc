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

typedef struct rca {
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
} rca;

typedef struct rca_request_vote {
} rca_request_vote;

typedef struct rca_request_vote_result {
} rca_request_vote_result;

typedef struct rca_append_entries {
} rca_append_entries;

typedef struct rca_append_entries_result {
} rca_append_entries_result;

int rca_process_request_vote();
int rca_process_append_entries();

#endif


int main() {}
