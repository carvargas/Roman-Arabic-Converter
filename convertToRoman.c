#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

/* Conditions: 
  -- I placed before V or X indicates one less
  -- X placed before L or C indicates ten less
  -- C placed before D or M indicates a hundred less
 */
 
 #define MAX 25

char * convertToRoman(char * num)
{
	int number = atoi(num);
	
	int val, i, index = 0;
	
	char * numeral = (char *)malloc(MAX * sizeof(char));
	
	while(number > 0)
	{
		if(number >= 1000)
		{
			val = number / 1000;
			
			for(i = 0; i < val; i++)
			{
				numeral[index++] = 'M';
			}
			
			number = number - (val * 1000);
		}
		
		else if(number >= 500)
		{
			if(number >= 900)
			{	
				numeral[index++] = 'C';
				numeral[index++] = 'M';
				
				number -= 900;
			}
			else
			{
				val = number / 500;
				
				for(i = 0; i < val; i++)
				{
					numeral[index++] = 'D';
				}
			
				number = number - (val * 500);
			}
		}
		
		else if(number >= 100)
		{
			if(number >= 400)
			{
				numeral[index++] = 'C';
				numeral[index++] = 'D';
				
				number -= 400;
			}
			else
			{
				val = number / 100;
				
				for(i = 0; i < val; i++)
				{
					numeral[index++] = 'C';
				}
			
				number = number - (val * 100);
			}
		}
		else if(number >= 50)
		{
			if(number >= 90)
			{
				numeral[index++] = 'X';
				numeral[index++] = 'C';
				
				number -= 400;
			}
			else
			{
				val = number / 50;
				
				for(i = 0; i < val; i++)
				{
					numeral[index++] = 'L';
				}
			
				number = number - (val * 50);
			}
		}
		else if(number >= 10)
		{
			if(number >= 40)
			{
				numeral[index++] = 'X';
				numeral[index++] = 'L';
				
				number -= 400;
			}
			else
			{
				val = number / 10;
				
				for(i = 0; i < val; i++)
				{
					numeral[index++] = 'X';
				}
			
				number = number - (val * 10);
			}
		}
		else if(number >= 5)
		{
			if(number >= 9)
			{
				numeral[index++] = 'I';
				numeral[index++] = 'X';
				
				number -= 9;
			}
			else
			{
				val = number / 5;
				
				for(i = 0; i < val; i++)
				{
					numeral[index++] = 'V';
				}
			
				number = number - (val * 5);
			}
		}
		else if(number >= 1)
		{
			if(number >= 4)
			{
				numeral[index++] = 'I';
				numeral[index++] = 'V';
				
				number -= 4;
			}
			else
			{
				val = number / 1;
				
				for(i = 0; i < val; i++)
				{
					numeral[index++] = 'I';
				}
			
				number = number - (val * 1);
			}
		}
	}
	
	numeral[index++] = '\0';
	
	return numeral;
}