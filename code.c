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
//#include"tree.h"
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
	//printf("%c %d \n",start2->ch,start2->freq);
	start2=start2->next;
	}

	//printf("%d",count);
	


	char arr[count];
	int freq[count];

	for(int i=0;i<count;i++){
        freq[i]=tmp->freq;
	arr[i]=tmp->ch;
	tmp=tmp->next;
	}
	/*for(int i=0;i<count;i++)
	printf("%d\n",arr[i]);*/
	int size1=sizeof(arr)/sizeof(arr[0]);
	code(arr,freq,size1);




	
	
	for(int i = 0; i < 128; i++) {
		int d;
		d=strlen(ar[i].str);
		//printf("%d.... ",d);
		if(d)
			size++;
	}
	printf("....%d....\n", size);
	writeheader();
	printf("hello");
	write_compressed_file();
	printf("hello");
	//read_f();
	close(fw);
	close(fr);
	return 0;
}

short convertstoshort(char *str) {
	/*short sh;
	int len = strlen(str);
	for(int i = 0; i < len; i++) {
		if(str[i] == '1') {
			sh = sh + pow(2, len-1-i);
		}	
	}
	return sh;*/
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
	//printf("in writeheader");
	char ch;
	char len;
	char *str;
	short sh;
	int count = 0;
	//fprintf(fw, "%d\n", size);
	write(fw, &size, sizeof(int));
	for(int i = 0; i < 128; i++) {
		//printf("hi....%d\n", count++);
		//printf("%s\n", array[i].str);
		if(strlen(ar[i].str)) {
			//printf("1");
			ch = ar[i].ch;
			printf("%c ", ch);
			write(fw, &ch, sizeof(char));
			//fprintf(fw, "%c", ch);
			len = strlen(ar[i].str);
			printf("%d ", len);
			write(fw, &len, sizeof(char));
			sh = convertstoshort(ar[i].str);
			printf("%s ", ar[i].str);
			printf("%d\n", sh);
			write(fw, &sh, sizeof(short));
			/*fprintf(fw, "%c", len);
			str = (char*)malloc(sizeof(char)*(l+1));
			strcpy()
			
			printf("%s\n", array[i].str);
			fprintf(fw, "%c %d %s ", ch, len, array[i].str);
			printf("%c %d %s \n", ch, len, array[i].str);	*/
			printf("6...");	
		}
	}
	printf("outside loop\n");
	return;
	
}
/*int decimal(char *str1) {
	//printf("indecimal\n");
	int sum = 0, len, j = 0;
	len = strlen(str1);
	//printf(".......%d\n", len);
	for(int i = 0; str1[i] != '\0'; i++) {
		printf("..%c...\n", str1[i]);
		sum = sum + ((str1[(len - 1) - i] - '0') * pow(2, i));
	}
	//printf("%d.......\n", sum);
	return sum;
}*/

void getcode(char ch, char *str){
	strcpy(str, ar[ch].str);
	return;
}

void write_compressed_file() {
	uint8_t temp = 0;
	char ch, str[32];
	//char temp = 0;
	int l, count = 0;
	int i;
	printf("ghj");
	lseek(fr,0,SEEK_SET);
	while(read(fr, &ch, 1)) {
	printf("fghjk");
		getcode(ch, str);
		l = strlen(str);
		for(i = 0; i < l; i++) {
			temp = temp<<1;
			temp = (temp) | (str[i] - '0');
			count++;
			if(count == 8) {
				//printf("%d\n", temp);
				printf("8");
				write(fw, &temp, 1);
				count = 0;
				temp = 0;
				//break;			
			}
		}
		/*if(count == 8){
			write(fw, &temp, 1);
			count = 0;
			temp = 0;		
		}
		if(i+1 < l) {
			while(i+1 < l) {
				temp = temp<<1;
				temp = (temp) | (str[i+1] - '0');
				count++;
				i++;
				if(count == 8) {
					write(fw, &temp, 1);
					count = 0;
					temp = 0;
				}
							
			}						
		}*/
	}
	if(count != 8 ) {
		if(count != 0) {
			write(fw, &temp, 1);
			write(fw, &count, sizeof(int));
		}	
	}
}
/*void write_f() {
	/*char ch;
	while((ch = getc(fr)) != EOF) {
		printf("%c = %s\n", ch, array[ch].str);
	}*/	
	/*char ch, *str, *str1, character;
	unsigned int m = 0, n = 0, dec, k, i, j, rem, p;
	//printf("hey");
	str1 = (char*)malloc(sizeof(char)*8);
	str1[8] = '\0';
	while((ch = getc(fr)) != EOF) {
		//printf("hello");
		int len = strlen(array[ch].str);
		str = (char*)malloc(sizeof(char) + len);
		getcode(ch, str);
		printf("%d = %s\n", ch, str);
		n = strlen(str);
		printf("str len :%d\n", n);
		//printf("%s\n", str1);
		printf("str1 len: %ld\t\n\n", strlen(str1));
		if((m = strlen(str1)) <= 8) {
			//printf("\t%ld\t\n", strlen(str1));
			k = 8 - m;
			for(i = m, j = 0; j < k && j < n; i++, j++) {
				str1[i] = str[j];
				//printf("%c  ", str1[i]);						
			}
			//str1[i] = '\0';
			//printf("\n");
			printf("in while %ld\n\n", strlen(str1));
			if(strlen(str1) == 8) {	
				str1[8] = '\0';//test
				dec = decimal(str1);
				printf(".............................%d\t%c sid sid\n", dec, dec);
				//character = (char)dec;
				//printf("%c", character);
				fprintf(fw, "%c ", dec);
				fseek(fw, 0, SEEK_END);
				free(str1);
				str1 = (char*)malloc(sizeof(char)*8);
				str1[8] = '\0';
				/*for(int x = 0; x < 8; x++) {
					str1[x] = '0';	
				}
				str1[8] = '\0'; 
				free(str1);*/
				//str1 = (char*)calloc(sizeof(char), 8);			
			/*}
			if(j != n) {
				printf("in remainder bits");
				p = n - j;
				for(i = 0; i < p/*test*//*j <= p*//*; i++, j++) {
					str1[i] = str[j];		
				}			
			}
			if(rem = strlen(str1) < 8) {
				free(str);//test
				continue;		
			}
				
		}
	free(str);	
	}
	if(strlen(str1) != 8){
		amb = i;
		printf("outside while eq to 8 %d\n", amb);
		while(i < 8) {
			str1[i] = '0';
			i++;		
		}
		str1[8] = '\0';//test
		dec = decimal(str1);
		//printf(".............................%d\t%c\n", dec, dec);
		//character = (char)dec;
		//printf("%c", character);
		fprintf(fw, "%c ", dec);
		fprintf(fw, "%c ", amb);
	}
	else if(strlen(str1) == 8) {
		amb = i;
		printf("outside while eq to 8 %d\n", amb);
		str1[8] = '\0';//test
		dec = decimal(str1);
		//printf(".............................%d\t%c\n", dec, dec);
		//character = (char)dec;
		//printf("%c", character);
		fprintf(fw, "%c ", dec);
		fprintf(fw, "%c ", amb);
	}
}

void read_f() {
	FILE *fp;
	fp = fopen("compre2", "w+");
	int size_r, len_r, i = 0;
	unsigned char ch_r, *str_r, num;
	fseek(fw, 0, SEEK_SET);
	fscanf(fw, "%d", &size_r);
	printf("%d\n", size_r);
	while(i < size_r) {
		
		fscanf(fw, "%c %d ", &ch_r, &len_r);
		str_r = (char*)malloc(sizeof(char)*len_r);
		fscanf(fw, " %s ", str_r);
		printf("%c\t%d\t%s\n", ch_r, len_r, str_r);
		free(str_r);
		i++;
	}
	while(fscanf(fw, "%c ", &num) != EOF) {
		fprintf(fp, "%d ", num);
	}
	fclose(fp);
	return;
}*/



