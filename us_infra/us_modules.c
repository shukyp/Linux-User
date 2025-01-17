/*---------------------------------------------------------------------------------
 * us_modules.c
 * 
 * The module holds the information about the various modules of the project.
 * By using the term module, I refer to a specific issues that is being covered.
 * The term 'us' stands for 'user space'
 *  
 * Header file(s):
 * 	- us_modules.h
 *
 * 
 * 
 * Evolution table:
 * 
 * Version	Date			Action
 * ---------------------------------------------------------------------------------
 * 		1	Oct. 15, 2019	Created
 * 
 * 
 * 
 *
 * 
 *** Author: Shuky Persky
 *
 * -----------------------------------------------------------------------------------*/

// includes
#include <stdio.h>

#include "prcs_mng.h"
#include "prcs_sched.h"
#include "prcs_ipcitc.h"

#include "us_infra_inner.h"

// extern objects


// defines


// types
typedef struct us_mdl_info
{
	char* descr;
	int (*entry_func)(bool);
} US_MDL_INFO; 


// local objects 
static US_MDL_INFO const us_mdls[] = 
	{
		{"Processes Manage (Create, Manage, Destroy)", 	(int (*)(bool))prcs_mng_menu},
		{"Processes Scheduling & Priorities", 				(int (*)(bool))prcs_sched_menu}, 		
		{"Inter Process/Thread Communication", 			(int (*)(bool))prcs_ipcitc_menu}, 
		{"Files IO", 												(int (*)(bool))NULL}
	};

static UINT num_of_modules = (sizeof(us_mdls)/sizeof(US_MDL_INFO));	
 		

// protoypes



/*------------------------------------------------------------
description: 
	returns the number of supported modules 
	
input:	
	None
	
returns: 
	int - number of supported modules 
  ------------------------------------------------------------*/
 UINT get_num_of_us_modules(void)
 {
	 return (num_of_modules);
 }
 
 
/*------------------------------------------------------------
description: 
	returns specifc us_module description if input module number
	is valid. otherwise, NULL is returned.
	
input:	
	us_mdl_num - module number
	
returns: 
	char* - requested module info
  ------------------------------------------------------------*/
const char* const get_us_module_topics(UINT us_mdl_num)
{
	// valid module number
	if (us_mdl_num <= num_of_modules)
		return (us_mdls[us_mdl_num-1].descr);

	// invalid module number
	return (NULL); 
 }


/*------------------------------------------------------------
description:
	displays the modules supported by the program

input:
	None

returns: 
	None
  ------------------------------------------------------------*/
void show_us_modules (void)
{
	UINT num_of_modules;
	const char* mdl_topics;
	 
	// get nm of modules
	num_of_modules = get_num_of_us_modules();
	
	// print table title
	printf ("\n Modules Table");
	printf ("\n ---------------");
	
	// print modules list
	for (UINT i=1; i<=num_of_modules; i++)
	{
		mdl_topics = get_us_module_topics(i);
		printf ("\n [%d] - %s", i, mdl_topics);
	}
	
	// print table title
	printf ("\n\n");
}
 
 
/*------------------------------------------------------------
description: 
	returns specifc us_module description if input module number
	is valid. otherwise, NULL is returned.
	
input:	
	us_mdl_num - module number
	verbose 	  - is verbose mode enabled
	
returns: 
	int - return code 
  ------------------------------------------------------------*/
int call_module (UINT us_mdl_num, bool verbose)
{
	int rc;
	
	// if valid module number
	if (us_mdl_num <= num_of_modules)
	{
	    rc = (*us_mdls[us_mdl_num-1].entry_func)(verbose);
	    return (rc);
	}

	// invalid us_module number
	return (EXIT_FAILURE);		
}
