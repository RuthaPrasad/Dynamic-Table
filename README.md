# Dynamic-Table-Experimentation
To implement and experiment with Dynamic Tables data structure based on the following guidelines:

Language restriction : C 

1. Create a data structure to hold all information required for a dynamic table.
   - pointer to the data 
   - max size of the table
   - current size
   - factor by which to increase the table size on insertion into a table, which is full
   - factor at which to decrease the size on deletion

2. Create a data structure to hold the sequence of operations to be performed.

3. Populate the sequence of operations - insert and delete.

4. Initialize the dynamic table data structure

5. Apply the sequence of operations on this dynamic table and record the time for each insertion and deletion.

6. Find the statistics.
   a) max time for insertion
   b) max time for deletion
   c) average of all operations
   d) average of insertions
   e) average of deletions.

7. Repeat these steps with
   a) Various factors for increasing the size; 2, 3, 1.75, 1.5, 1.25.
	  Find which one seems to give better statistical measure?
   b) Various factors for decreasing the size on deletion; 0.25, 0.5, 0.75. 
	  Find which one seems to give better statistical measure.
   You should produce a matrix of statistical values.
	
8. Repeat these steps for sequence of operators with insert:delete operations in the ratio:
	a) 3:2
	b) 4:2
	Note your findings.
	

