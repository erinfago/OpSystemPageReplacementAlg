/* pra.c */

/* Use this file to implement your page replacement algorithm! */

#include "machine.h"
#include <limits.h>
#include <stdlib.h> 
#include <stdio.h>


// This function is run by the machine before any addresses are accessed.
void initialize_student_code(){
	// n/a
}

unsigned int select_frame()
{  // Selects a frame to use (implements sme page replacement algorithm)
	//page replacement alg : least recently used
	
	//get info
	unsigned int numPages = get_num_pages();
	unsigned int numFrames = get_num_frames();

	//sets min
	int min = UINT_MAX;
	
	//where it is in the page table
	int idx = 0;
	
	//if the page is present in the frame table
	_Bool isPresent = 0;
	
	//how many are currently present 
	int numPres = 0;
	

	//go through each of the pages
	for(int i=0; i<numPages; i++){
		//check to see if this entry is present
		if(get_page_table_entry(i)->present){
			//if so, make note of it
			isPresent = 1;
			numPres++;
		}
	}

	// make sure we have enough present to choose from and do this if below threshold
	if(numPres<= 3){
		//decide what frame will be used randomly
		int frameChoice = rand() % numFrames+1;
		return frameChoice;
	}

	// otherwise go through the table and pick the page table entry with 
	//  fewest hits that is also present
	for(int i=0; i<numPages; i++){
		if ((get_page_table_entry(i)->C < min) && (get_page_table_entry(i)->present)){
			min = get_page_table_entry(i)->C; //new least recently used
			idx = i; //position of page table entry to be returned
		}
	}

	//return the frame number of the page table entry that was least recently used
	return get_page_table_entry(idx)->frame_number;
}
