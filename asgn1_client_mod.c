#include<stdio.h>
#include "asgn1_header_mod.h"
int main()
{
	//create dyn_table
	dyn_table *ptr_mytable;
	//initialize dyn_table
	float dec_factor=0.25;
	float inc_factor=1.25;
	init_table(&ptr_mytable,dec_factor,inc_factor);
	//create sequence of operations	
	seq_op *ptr_myseq;
	int num_of_ops=100;
	char ratio[3]="4:2";	
	//populate sequence
	populate(&ptr_myseq,num_of_ops,ratio);
	//run the sequence on dynamic table
	//disp_seq(&ptr_myseq);
	run_seq(&ptr_mytable,&ptr_myseq);
	//statistics on the operations performed 
	//disp_seq(&ptr_myseq);
	printf("ratio:%s\n",ratio);
	stats(&ptr_mytable);
	delete_table(ptr_mytable);
	delete_seq(ptr_myseq);
	return 0;
}
