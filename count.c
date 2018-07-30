#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	unsigned long long int data; 
	struct Node * next;
}Node;

#define size 1000
struct Node *table[size];

int insert(unsigned long long int);

int main(int argc, char **argv){
	if(argc != 2){
		printf("error\n");
		return 1;
	}

	FILE *fp = fopen(argv[1], "r");
		
	if (fp == NULL){
		printf("error\n");
		return 1;
	}

	if(fp){
		fseek(fp,0,SEEK_END);
		if(ftell(fp)==0){
			printf("%d\n",0);
			return 0;
		}else{
			fseek(fp,0,SEEK_SET);
		}
	} 

	int count = 0;
	char address [19];	
	while (!feof(fp)){
		
		fscanf(fp, "%s", address);
		
		unsigned long long int str=strtoull(address,NULL,16);
		
		if(insert(str)==1){
			count++;
		}
	}
	
	fclose(fp);
	printf("%d\n", count);
	return 0;
}	

int insert(unsigned long long int address){
	int spot = address%1000;
	if(table[spot]==NULL){ //if there's nothing in this spot of the hash table 
		Node *temp = (struct Node *)malloc(sizeof(struct Node));
		temp->data = address;
		temp->next = NULL;
		table[spot] = temp;
		return 1;
	} else { //if there is something in this spot of the hash table
		if(table[spot]->data == address){
			return 0; //there's a duplicate in the first chain of the spot
		} 
		Node *ptr = (struct Node *) malloc(sizeof(struct Node));
		ptr = table[spot];
		while(ptr->next != NULL){
			if(ptr->data == address){
				//this means you have a duplicate value 
				return 0;
			}
			ptr = ptr->next;
		}
		if (ptr->data == address){
			return 0;
		}
		//if you're here, that means you're at the end of a chain and there were no duplicates
		Node *newnode = (struct Node *)malloc(sizeof(struct Node));
		newnode->data = address;
		newnode->next = NULL;
		ptr->next = newnode;
		return 1; //completed 1 successful insert 
	}
	return 0;
	
}
