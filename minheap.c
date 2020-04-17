#include"minheap.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define treeheight 100



codes ar[128];

char * getcharstr(int *temp, int n);

void printarr(int arr[], int n) 
{ 
    int i; 
    for (i = 0; i < n; ++i) 
        printf("%d", arr[i]); 
  
    printf("\n"); 
} 
  


char * getcharstr(int *temp, int n) {
	static char str[64];
	int i;
	for(i = 0; i < n; i++) {
		str[i] = temp[i] + '0';
	}
	str[i] = '\0';
	return str;
}
	
void printcodes(node* root, int arr[], int top) 
	  
{ 
  	int temp[64];
     	char *str1;
    if (root->left) { 
  
        arr[top] = 0; 
        printcodes(root->left, arr, top + 1); 
    } 

    if (root->right) { 
  
        arr[top] = 1; 
        printcodes(root->right, arr, top + 1); 
    } 
  
    
    if (isleaf(root)) { 
  
      //  printf("%c: ", root->data);
	ar[root->data].ch = root->data; 
	int j;
	for(j = 0; j < top; j++) {
		
		//ar[root->data].str[j] = arr[j];
		temp[j] = arr[j];
	}
	str1 = (char*)malloc(sizeof(char)*(j+1));
	str1 = getcharstr(temp, j);
	strcpy(ar[root->data].str, str1);
	//printf("%s\n",ar[root->data].str);
        //printarr(arr, top);
	//int j;
	/*for(j = 0; j< top; j++) {
		printf("%d ", ar[root->data].str[j]);
	}
	printf("\n"); */
    } 
} 













void code(char data[],int freq[],int size){
node* root=bht(data,freq,size);
int arr[treeheight];
int top=0;
printcodes(root,arr,top);
}








node* newnode(char data, unsigned freq){
	node *tmp;
	tmp=(node*)malloc(sizeof(node));
	tmp->left=NULL;
	tmp->right=NULL;
	tmp->data=data;
	tmp->freq=freq;
	return tmp;
}




struct minheap* createminheap(unsigned capacity){

	struct minheap* mheap;
	mheap=(struct minheap*)malloc(sizeof(struct minheap));
	mheap->size=0;
	mheap->capacity=capacity;
	mheap->arr=(node**)malloc(mheap->capacity * sizeof(node*));
	return mheap;
}





void swapnode(node**a,node**b){
	node *t;
	t=*a;
	*a=*b;
	*b=t;
}



void heapify(struct minheap* mheap, int index){
int parent = index;
int c1=2*index +1;
int c2=2*index +2;
if(c1<mheap->size && mheap->arr[c1]->freq<mheap->arr[parent]->freq)
parent=c1;
if(c2<mheap->size && mheap->arr[c2]->freq<mheap->arr[parent]->freq)
parent=c2;
if(parent!=index){
swapnode(&mheap->arr[parent],&mheap->arr[index]);
heapify(mheap,parent);
}
}






int issone(struct minheap* mheap){
return (mheap->size==1);
}




node* minimum(struct minheap* mheap){
node *tmp=mheap->arr[0];
mheap->arr[0]=mheap->arr[mheap->size-1];
--mheap->size;
heapify(mheap,0);
return tmp;
}





void insert(struct minheap* mheap,node* t){
++mheap->size;
int i=mheap->size-1;
while(i && t->freq < mheap->arr[(i-1)/2]->freq){
mheap->arr[i]=mheap->arr[(i-1)/2];
i=(i-1)/2;
}
mheap->arr[i]=t;

}







void makeheap(struct minheap* mheap){

int n = mheap->size -1;
int i;
for(i=(n-1)/2;i>=0;--i)
heapify(mheap,i);
}




struct minheap* cbm(char data[],int freq[],int size){
struct minheap* mheap=createminheap(size);
int i;
for(i=0;i<size;++i)
mheap->arr[i]=newnode(data[i],freq[i]);
mheap->size=size;
makeheap(mheap);
return mheap;

}




node* bht(char data[],int freq[],int size){
node *left,*right,*top;
struct minheap* mheap=cbm(data,freq,size);
while(!issone(mheap)){
left=minimum(mheap);
right=minimum(mheap);
top=newnode('$',left->freq+right->freq);
top->left=left;
top->right=right;
insert(mheap,top);
}
return minimum(mheap);
}




int isleaf(node* root){
return !(root->left) && !(root->right);
}





















/*

/*void print(node* root, char arr[], int top){

/*void printarr(int arr[], int n){
int i;
for(i=0;i<n;++i)
printf("%d",arr[i]);
printf("\n");
}


static int i = 0;
if(root) {
if(root->left){
arr[top]=0;
print(root->left,arr,top+1);
}

if(root->right){
arr[top]=1;
print(root->right,arr,top+1);
}

//printf("%d",top);
if(isleaf(root)){
	//arr[top] = '\0';
	ar[i].ch = root->data;
	//strcpy(ar[root->data].str, arr);
	for(int j = 0; j < top ; j++) {
		ar[i].str[j] = arr[j];	
	}
	//printf("%s\n",ar[root->data].str);
	for(int j = 0; j < top ; j++) {
		printf("%d ", ar[i].str[j]);	
	}
	printf("\n");
//printf("%c:",root->data);
//printarr(arr,top);
}
}
}
*/	




