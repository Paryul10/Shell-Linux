#include "variables.h"
#include "header.h"

void overkill(){
	int i;
	for (i = 1; i <= back_c; i++) 
	{
		if(background[i].state==1)
		{
			kill(background[i].pi,9);
			background[i].state = 0;
		}
	}
}
