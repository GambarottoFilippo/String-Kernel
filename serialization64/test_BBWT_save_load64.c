#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <string.h>
#include"mt19937ar.h"
#include"DNA5_Basic_BWT64.h"
#define textsize ((1<<20))
//#define textsize (1024)
static void naive_str_print(unsigned char * str1, unsigned long long str_len)
{
	unsigned long long i;
	for(i=0;i<str_len;i++)
		printf("%c",str1[i]);

};

static unsigned char local_DNA_trans_table[5]={'A','C','G','T','Z'};

int main()
{
	unsigned char * text;
	unsigned long long textlen;
	unsigned long long i;
	unsigned char tmp_char;
	unsigned int print_string=0;
	int read_bytes,written_bytes;
	int err_code;
	Basic_BWT64_t * BBWT;
	Basic_BWT64_t * BBWT2;
	textlen=textsize;
	text=(unsigned char *)malloc(textlen+1);
	text[textlen]='0';
// Generate a random text.
	init_genrand(time(0));
	for(i=0;i<textlen;i++)
	{
		tmp_char=genrand_int32()%4;
		text[i]=local_DNA_trans_table[tmp_char];
	};
	printf("Text len is %llu\n",textlen);
	if(print_string)
	{
		printf("Input string is : ");
		naive_str_print(text,textlen);
		printf("\n");
	};
// Build a BWT index on the text. 
//	BBWT=Build_BWT_index_from_text(text,textlen,Basic_bwt_no_free_text);
	BBWT=Build_BWT_index_from_text64(text,textlen,Basic_bwt_free_text);
	written_bytes=save_Basic_BWT64_to_file(BBWT,"BBWT_file.bbwt");
	read_bytes=load_Basic_BWT64_from_file(&BBWT2,"BBWT_file.bbwt");
	printf("written bytes %d\n",written_bytes);
	printf("read bytes %d\n",read_bytes);
	if((err_code=cmp_BBWT64s(BBWT,BBWT2))!=0)
		printf("Error in load/save BBWT mechanism with error code %d\n",err_code);
	else
		printf("success in load/save BBWT mechanism\n");
	free_Basic_BWT64(BBWT);
	free_Basic_BWT64(BBWT2);
//	free(text);
	return 0; 
};