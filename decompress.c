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
#include <math.h>
#include <stdint.h>
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))
#define MAX 64
#define MAX_BITS 8
int fw, fr;
long long int file_size;
typedef struct node_d
{
	char ch;
	struct node_d *left, *right;
} node_d;

node_d *root;

void init_root();
node_d *creat_node();
void readheader();
void write_decompress_file();
int isleaf(node_d *temp);
void convert_decimal_to_binary(short num, int l, char *codes);
long long int getsize(int fd);

int main(int argc, char *argv[])
{
	fr = open(argv[1], O_RDONLY);
	if (fr == -1)
	{
		perror("open failed");
		return 0;
	}
	fw = open(argv[2], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if (fw == -1)
	{
		perror("open failed");
		return 0;
	}
	init_root();
	readheader(fr);
	write_decompress_file(fr, fw);
	close(fr);
	close(fw);
	return 0;
}

node_d *creat_node()
{
	node_d *new;
	new = (node_d *)malloc(sizeof(node_d));
	new->left = new->right = NULL;
	return new;
}

void init_root()
{
	root = creat_node();
	return;
}

/*void inorder(node_d *t) {
	if(t == NULL) 
		return;
	
	inorder(t->left);
	printf("%c ", t->ch);
	inorder(t->right);
}*/

long long int getsize(int fd)
{
	long long int fs = 0;
	fs = lseek(fd, 0, SEEK_END);
	return fs;
}
void convert_decimal_to_binary(short num, int l, char *codes)
{
	int len, diff;
	char ch, temp[MAX];
	int i = 0;
	while (num)
	{
		if (num % 2)
		{
			codes[i] = '1';
		}
		else
			codes[i] = '0';
		i++;
		num = num / 2;
	}
	codes[i] = '\0';
	len = strlen(codes);
	for (i = 0; i < len / 2; i++)
	{
		SWAP(codes[i], codes[len - 1 - i], ch);
	}
	diff = l - len;
	for (i = 0; i < diff; i++)
	{
		temp[i] = '0';
	}
	temp[i] = '\0';
	strcat(temp, codes);
	strcpy(codes, temp);
	return;
}

void readheader(int fr)
{

	file_size = getsize(fr);
	printf("%lldt\n", file_size);
	lseek(fr, 0, SEEK_SET);
	short num;
	int size, l, j = 0;
	char ch, codes[MAX], len;
	node_d *currnode = root;
	read(fr, &size, sizeof(int));
	printf("%d..\n", size);
	file_size = file_size - 4;
	for (int i = 0; i < size; i++)
	{
		read(fr, &ch, sizeof(char));
		file_size = file_size - 1;
		printf("%c ", ch);
		read(fr, &len, sizeof(char));
		file_size = file_size - 1;
		printf("%d ", len);
		l = len;
		read(fr, &num, sizeof(short));
		file_size = file_size - 2;
		printf("%d\n", num);
		convert_decimal_to_binary(num, l, codes);
		//printf("%s\n", codes);
		currnode = root;
		j = 0;
		while (codes[j] != '\0')
		{
			if (codes[j] == '1')
			{
				if (currnode->right == NULL)
				{
					currnode->right = creat_node();
				}
				currnode = currnode->right;
			}
			else if (codes[j] == '0')
			{
				if (currnode->left == NULL)
				{
					currnode->left = creat_node();
				}
				currnode = currnode->left;
			}
			j++;
		}
		currnode->ch = ch;
	}
	//inorder(root);
	return;
}

int isleaf(node_d *temp)
{
	//printf("in leaf\n");
	return ((temp->left == NULL) && (temp->right == NULL));
}

void write_decompress_file(int fr, int fw)
{
	uint8_t ch, bit;
	int last_byte, left_shift;
	char c;
	node_d *temp = root;
	int i;
	temp = root;
	bit = 1 << (MAX_BITS - 1);
	printf("%lld.....\n", file_size);
	long long int read_bytes = file_size - 5;
	printf("%lld\n", read_bytes);
	while (read_bytes > 0)
	{

		read(fr, &ch, 1);

		i = 0;
		while (i != MAX_BITS)
		{
			if (ch & bit)
			{

				temp = temp->right;
				i++;
			}
			else
			{

				temp = temp->left;
				i++;
			}
			ch = ch << 1;
			if (isleaf(temp))
			{

				c = temp->ch;
				printf("%c", c);
				write(fw, &c, 1);

				temp = root;
			}
		}
		read_bytes = read_bytes - 1;
	}

	read(fr, &ch, 1);
	read(fr, &last_byte, sizeof(int));

	left_shift = MAX_BITS - last_byte;
	//printf("%d\n", left_shift);
	while (left_shift > 0)
	{
		ch = ch << 1;
		left_shift = left_shift - 1;
	}
	//printf("%d\n", last_byte);
	/*while(last_byte > 0) {
		if(ch & bit) {
			temp = temp->right;	
		}
		else {
			temp = temp->left;
		}
		ch = ch << 1;
		if(isleaf(temp)) {
					
			c = temp->ch;
			printf("%c", c);
			write(fw, &c, 1);
			temp = root;
		}
		last_byte = last_byte - 1;	
	}*/
}
