#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include<math.h>
#include<stdint.h>
#include"frequency.h"
#include"minheap.h"




anode *start=NULL, *end=NULL;

	anode* frequency(int fr){
	int *frequency ,i;
	char ch; 
	frequency=(int*)calloc(sizeof(int),127);
	while(read(fr, &ch, 1)){
	frequency[(int)ch]++;
}

for(i=0;i<127;i++){
	if(frequency[i]>0){
	anode *new=(anode*)malloc(sizeof(anode));
	new->freq=frequency[i];
	new->ch=i;
	new->next=NULL;
	if(start==NULL){
	start=new;
	end=new;
}
else{
	end->next=new;
	end=new;
}
}

}

	return start;
}

	anode* sorting(anode *start)
{
	anode *tmp1,*tmp2;
	char c;
	int f,freq;
for(tmp1=start;tmp1!=NULL;tmp1=tmp1->next)
{
for(tmp2=tmp1->next;tmp2!=NULL;tmp2=tmp2->next){
	if(tmp1->freq>tmp2->freq)
{
	f=tmp1->freq;
	tmp1->freq=tmp2->freq;
	tmp2->freq=f;

	c=tmp1->ch;
	tmp1->ch=tmp2->ch;
	tmp2->ch=c;
}

}
}
	return start;
}



































