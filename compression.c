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

void writeheader();
void write_compressed_file();
void getcode(char ch, char *str);
int decimal(char *str1);
void read_f();
short int convertstoshort(char *str);
extern codes ar[128];
int size = 0, amb;
int fr, fw;
int main(int argc, char *argv[]) {
	
	fr = open(argv[1], O_RDONLY);
	if(fr == -1) {
		printf("open failed:::");
		exit(1);
	}
	fw = open(argv[2], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if(fw == -1){
		printf("open failed:::");
		exit(1);
	}
	int count=0;
	anode *start1,*start2,*tmp;
	start1=frequency(fr);
	start2=sorting(start1);
	tmp=start2;
	while(start2!=NULL){
	count++;
	
	start2=start2->next;
	}	
	char arr[count];
	int freq[count];

	for(int i=0;i<count;i++){
        freq[i]=tmp->freq;
	arr[i]=tmp->ch;
	tmp=tmp->next;
	}

	int size1=sizeof(arr)/sizeof(arr[0]);
	code(arr,freq,size1);
	for(int i = 0; i < 128; i++) {
		int d;
		d=strlen(ar[i].str);
		
		if(d)
			size++;
	}
	
	writeheader();
	write_compressed_file();
	close(fw);
	close(fr);
	return 0;
}

short convertstoshort(char *str) {
	
	short sh = 0;
	int i, l = strlen(str);
	for(i = 0; i < l; i++){
		if(str[i] == '1'){
			sh = sh + pow(2, l - 1 - i);
		}
	}
	return sh;

}

void writeheader() {
	
	char ch;
	char len;
	char *str;
	short sh;
	int count = 0;
	
	write(fw, &size, sizeof(int));
	for(int i = 0; i < 128; i++) {
		
		if(strlen(ar[i].str)) {
			
			ch = ar[i].ch;
			
			write(fw, &ch, sizeof(char));
			
			len = strlen(ar[i].str);
			
			write(fw, &len, sizeof(char));
			sh = convertstoshort(ar[i].str);
			
			write(fw, &sh, sizeof(short));
			
		}
	}
	
	return;
	
}


void getcode(char ch, char *str){
	strcpy(str, ar[ch].str);
	return;
}

void write_compressed_file() {
	uint8_t temp = 0;
	char ch, str[32];
	
	int l, count = 0;
	int i;
	
	lseek(fr,0,SEEK_SET);
	while(read(fr, &ch, 1)) {
	
		getcode(ch, str);
		l = strlen(str);
		for(i = 0; i < l; i++) {
			temp = temp<<1;
			temp = (temp) | (str[i] - '0');
			count++;
			if(count == 8) {
				
				
				write(fw, &temp, 1);
				count = 0;
				temp = 0;
						
			}
		}
		
	}
	if(count != 8 ) {
		if(count != 0) {
			write(fw, &temp, 1);
			write(fw, &count, sizeof(int));
		}	
	}
}

