#include <stdio.h>

int subOrAdd(int n, char post)
{	
	if(n == 1)
	{
		switch(post)
			{
				case 'v':
				case 'V': 
				case 'x':
				case 'X':
					return 1;
				default:
					return 0;
			}
	}
	else if(n == 10)
	{
		switch(post)
			{
				case 'l':
				case 'L':
				case 'c':
				case 'C':
					return 1;
				default:
					return 0;
			}
	}
	else if(n == 100)
	{
		switch(post)
		{			
				case 'd':
				case 'D':
				case 'm':
				case 'M':
					return 1;
				default:
					return 0;
		}
	}
}

int sub(int value, char post)
{
	if(value == 1)
	{
		if(post == 'v' || post == 'V')
		{
			value = 5 - 1;	
			
			return value;
		}
		
		else if(post == 'x' || post == 'X')
		{
			value = 10 - 1;	
			
			return value;
		}
	}
	if(value == 10)
	{
		if(post == 'l' || post == 'L')
		{
			value = 50 - 10;	
			
			return value;
		}
		
		else if(post == 'c' || post == 'C')
		{
			value = 100 - 10;	
			
			return value;
		}
	}
	if(value == 100)
	{
		if(post == 'd' || post == 'D')
		{
			value = 500 - 100;	
			
			return value;
		}
		
		else if(post == 'm' || post == 'M')
		{
			value = 1000 - 100;	
			
			return value;
		}
	}
}