#include<time.h>
#include<stdio.h>
#include<stdlib.h>
struct dynamic_table
{
	float max_size;
	int current_size;
	float dec_factor;
	float inc_factor;
	float max_insert;
	float max_delete;
	float avg_insert;
	float avg_delete;
	float avg_operations;
	int *table_arr;
};
typedef struct dynamic_table dyn_table;
struct sequence_of_operations
{
	int num_of_ops;
	int num_of_inserts;
	int num_of_deletes;
	int *seq_arr;
};
typedef struct sequence_of_operations seq_op;
void init_table(dyn_table**,float,float);
void delete_table(dyn_table*);
void delete_seq(seq_op*);
void populate(seq_op**,int,char*);
void run_seq(dyn_table**,seq_op**);
void stats(dyn_table**);
void disp_seq(seq_op**);
double time_elapsed(struct timespec *,struct timespec *);
void insert(dyn_table **,seq_op **);
void del(dyn_table **,seq_op **);


