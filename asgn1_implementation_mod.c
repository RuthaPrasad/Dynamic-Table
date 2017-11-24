#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include "asgn1_header_mod.h"
struct timespec start, end;
double time_elapsed(struct timespec *start,struct timespec *end)
{
	double time =0.0;
	time = (end->tv_sec - start->tv_sec )*1000;
	time += (end->tv_nsec - start->tv_nsec )*0.000001;
	return time;
}
void init_table(dyn_table **ptr_ptr,float dec_factor,float inc_factor)
{
	float maximum_size=10;
	dyn_table* ptr_table=(dyn_table*)malloc(sizeof(dyn_table));
	ptr_table->table_arr=(int*)malloc(sizeof(int)*maximum_size);
	ptr_table->max_size=maximum_size;
	ptr_table->current_size=0;
	ptr_table->dec_factor=dec_factor;
	ptr_table->inc_factor=inc_factor;
	ptr_table->max_insert=0;
	ptr_table->max_delete=0;
	ptr_table->avg_insert=0;
	ptr_table->avg_delete=0;
	ptr_table->avg_operations=0;
	*ptr_ptr=ptr_table;
}
void delete_table(dyn_table *ptr_table)
{
	free(ptr_table->table_arr);
	free(ptr_table);
}
void delete_seq(seq_op *ptr_seq)
{
	free(ptr_seq->seq_arr);
	free(ptr_seq);
}
void disp_seq(seq_op **ptr_ptr_seq)
{
	int i;
	printf("%d\n",(*ptr_ptr_seq)->num_of_ops);
	for(i=0;i<((*ptr_ptr_seq)->num_of_ops);i++)
	{
		printf("%d:%d\n",i,(*ptr_ptr_seq)->seq_arr[i]);
	}
	printf("inserts:%d\ndeletes:%d\n",(*ptr_ptr_seq)->num_of_inserts,(*ptr_ptr_seq)->num_of_deletes);
}
void populate(seq_op **ptr_ptr,int num,char* ratio)
{
	//finding number of inserts and deletes from ratio
	float no_of_inserts=ratio[0]-48;
	float no_of_deletes=ratio[2]-48;
	float total=no_of_inserts+no_of_deletes;
	no_of_inserts=((no_of_inserts/total)*num);
	no_of_deletes=num-no_of_inserts;
	seq_op* ptr_seq=(seq_op*)malloc(sizeof(seq_op));
	ptr_seq->seq_arr=(int*)malloc(sizeof(int)*num);
	//initialize members of sequence 
	ptr_seq->num_of_ops=num;
	ptr_seq->num_of_inserts=no_of_inserts;
	ptr_seq->num_of_deletes=no_of_deletes;
	//insert 1s and 0s as operations
	//1 for insert 
	//0 for delete
	int i;
	for(i=0;i<no_of_inserts;i++)
	{
		ptr_seq->seq_arr[i]=1;		
	}
	int j;
	for(j=0;j<no_of_deletes;j++)
	{
		ptr_seq->seq_arr[i+j]=0;		
	}
	//random permutation of inserts and deletes
	srand(getpid());
	int m;
	for(m=0;m<ptr_seq->num_of_ops;m++)
	{
		int k=rand()%ptr_seq->num_of_ops;
		int temp=ptr_seq->seq_arr[m];
		ptr_seq->seq_arr[m]=ptr_seq->seq_arr[k];
		ptr_seq->seq_arr[k]=temp;	
	}
	*ptr_ptr=ptr_seq;
}
void insert(dyn_table **ptr_ptr_table,seq_op **ptr_ptr_seq)
{
	(*ptr_ptr_seq)->num_of_inserts--;
	if((*ptr_ptr_table)->current_size<(*ptr_ptr_table)->max_size)//not-filled
	{
		//simple insertion
		(*ptr_ptr_table)->table_arr[(*ptr_ptr_table)->current_size]=1;
	}
	else//filled
	{
		//enlarge max_size
		(*ptr_ptr_table)->max_size+=((*ptr_ptr_table)->max_size)*((*ptr_ptr_table)->inc_factor);
		//enlarge table
		dyn_table* new_ptr_table=(dyn_table*)malloc(sizeof(dyn_table));
		new_ptr_table->table_arr=(int*)malloc(sizeof(int)*((*ptr_ptr_table)->max_size));
		//copy contents
		(new_ptr_table)->max_size=(*ptr_ptr_table)->max_size;
		(new_ptr_table)->current_size=(*ptr_ptr_table)->current_size;
		(new_ptr_table)->dec_factor=(*ptr_ptr_table)->dec_factor;
		(new_ptr_table)->inc_factor=(*ptr_ptr_table)->inc_factor;
		(new_ptr_table)->max_insert=(*ptr_ptr_table)->max_insert;
		(new_ptr_table)->max_delete=(*ptr_ptr_table)->max_delete;
		(new_ptr_table)->avg_insert=(*ptr_ptr_table)->avg_insert;
		(new_ptr_table)->avg_delete=(*ptr_ptr_table)->avg_delete;
		(new_ptr_table)->avg_operations=(*ptr_ptr_table)->avg_operations;
		dyn_table *free_ptr=(*ptr_ptr_table);
		(*ptr_ptr_table)=new_ptr_table;
		delete_table(free_ptr);
		//simple insertion
		(*ptr_ptr_table)->table_arr[(*ptr_ptr_table)->current_size]=1;
	}
	(*ptr_ptr_table)->current_size++;
}
void del(dyn_table **ptr_ptr_table,seq_op **ptr_ptr_seq)
{
	(*ptr_ptr_seq)->num_of_deletes--;
	if((*ptr_ptr_table)->current_size>((*ptr_ptr_table)->max_size/2))//more than half the table
	{
		//simple deletion
		(*ptr_ptr_table)->table_arr[(*ptr_ptr_table)->current_size]=0;
	}
	else//less than half the table
	{
		//shrink max_size
		(*ptr_ptr_table)->max_size-=((*ptr_ptr_table)->max_size)*((*ptr_ptr_table)->dec_factor);
		//shrink table
		dyn_table* new_ptr_table=(dyn_table*)malloc(sizeof(dyn_table));
		new_ptr_table->table_arr=(int*)malloc(sizeof(int)*((*ptr_ptr_table)->max_size));
		//copy contents
		(new_ptr_table)->max_size=(*ptr_ptr_table)->max_size;
		(new_ptr_table)->current_size=(*ptr_ptr_table)->current_size;
		(new_ptr_table)->dec_factor=(*ptr_ptr_table)->dec_factor;
		(new_ptr_table)->inc_factor=(*ptr_ptr_table)->inc_factor;
		(new_ptr_table)->max_insert=(*ptr_ptr_table)->max_insert;
		(new_ptr_table)->max_delete=(*ptr_ptr_table)->max_delete;
		(new_ptr_table)->avg_insert=(*ptr_ptr_table)->avg_insert;
		(new_ptr_table)->avg_delete=(*ptr_ptr_table)->avg_delete;
		(new_ptr_table)->avg_operations=(*ptr_ptr_table)->avg_operations;
		dyn_table *free_ptr=(*ptr_ptr_table);
		(*ptr_ptr_table)=new_ptr_table;
		delete_table(free_ptr);
		//simple insertion
		(*ptr_ptr_table)->table_arr[(*ptr_ptr_table)->current_size]=0;
	}
	(*ptr_ptr_table)->current_size--;
}
void run_seq(dyn_table **ptr_ptr_table,seq_op **ptr_ptr_seq)
{
	int i=0;
	float inserts=(*ptr_ptr_seq)->num_of_inserts;
	float deletes=(*ptr_ptr_seq)->num_of_deletes;
	while(i<(*ptr_ptr_seq)->num_of_ops)
	{
		if(((*ptr_ptr_seq)->seq_arr[i]==1)&&((*ptr_ptr_seq)->num_of_inserts!=0))//if insert and inserts not exhausted
		{
			clock_gettime(CLOCK_REALTIME,&start);
			insert(ptr_ptr_table,ptr_ptr_seq);
			clock_gettime(CLOCK_REALTIME,&end);
			float time=time_elapsed(&start,&end);//record time for operation
			if((*ptr_ptr_table)->max_insert<=time)
			{
				(*ptr_ptr_table)->max_insert=time;//change max insertion time if needed
			}
			(*ptr_ptr_table)->avg_insert+=time/inserts;//include into avg insertion time
		}		
		else if(((*ptr_ptr_seq)->seq_arr[i]==0)&&((*ptr_ptr_seq)->num_of_deletes!=0))//if delete and deletes not exhausted
		{
			
			if((*ptr_ptr_seq)->num_of_inserts<(*ptr_ptr_seq)->num_of_deletes)//non-empty table
			{	
				clock_gettime(CLOCK_REALTIME,&start);
				del(ptr_ptr_table,ptr_ptr_seq);
				clock_gettime(CLOCK_REALTIME,&end);
				float time=time_elapsed(&start,&end);//record time for operation
				if((*ptr_ptr_table)->max_delete<=time)
				{
					(*ptr_ptr_table)->max_delete=time;//change max deletion time if needed
				}
				(*ptr_ptr_table)->avg_delete+=time/deletes;//include into avg deletion time
					
			}
			else if((*ptr_ptr_seq)->num_of_inserts>(*ptr_ptr_seq)->num_of_deletes)//empty table
			{
				//make appear that an insert is always present before a delete
				clock_gettime(CLOCK_REALTIME,&start);
				insert(ptr_ptr_table,ptr_ptr_seq);//using a future insert so as to delete now
				clock_gettime(CLOCK_REALTIME,&end);
				float time=time_elapsed(&start,&end);//record time for operation
				if((*ptr_ptr_table)->max_insert<=time)
				{
					(*ptr_ptr_table)->max_insert=time;//change max insertion time if needed
				}
				(*ptr_ptr_table)->avg_insert+=time/inserts;//include into avg insertion time
				//use delete now on non-empty table
				clock_gettime(CLOCK_REALTIME,&start);
				del(ptr_ptr_table,ptr_ptr_seq);//record time for operation
				clock_gettime(CLOCK_REALTIME,&end);
				time=time_elapsed(&start,&end);
				if((*ptr_ptr_table)->max_delete<=time)
				{
					(*ptr_ptr_table)->max_delete=time;//change max deletion time if needed
				}
				(*ptr_ptr_table)->avg_delete+=time/deletes;//include into avg deletion time
			
			}	
		}
		i++;
	}
	(*ptr_ptr_table)->avg_operations=((*ptr_ptr_table)->avg_delete+(*ptr_ptr_table)->avg_insert)/(*ptr_ptr_seq)->num_of_ops;
	
}
void stats(dyn_table **ptr_ptr_table)
{
	printf("increase factor:%lf\n",(*ptr_ptr_table)->inc_factor);
	printf("decrease factor:%lf\n",(*ptr_ptr_table)->dec_factor);
	//printf("current size:%d\n",(*ptr_ptr_table)->current_size);
	printf("maximum time for a insertion: %lf\n",(*ptr_ptr_table)->max_insert);
	printf("maximum time for a deletion: %lf\n",(*ptr_ptr_table)->max_delete);
	printf("average time for insertions: %lf\n",(*ptr_ptr_table)->avg_insert);
	printf("average time for deletions: %lf\n",(*ptr_ptr_table)->avg_delete);
	printf("average time for all operations: %lf\n",(*ptr_ptr_table)->avg_operations);	
}
