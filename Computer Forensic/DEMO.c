#include<stdio.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<assert.h>
#define  LITTLE 0
#define  BIG 	1
#define  SIGNED 0
#define  UNSIGNED 1
unsigned long getNumeric(FILE *f,
						 long offset,
						 int size,
						 char type,
						 char endian)
{
	
	assert(f!=NULL);//断言，如果f为NULL则不进行运算
	//长度超过unsigned的长度 报错 
	assert(size==1||size==2||size==4);
	//取值判断
	assert(type==SIGNED||type==UNSIGNED);
	assert(endian==BIG ||endian==LITTLE); 
	//文件指针偏移到制定位置，0为开始位置
	//如果文件偏移位置大于文件长度或者偏移加读取的数据超出文件长度，报错
	int len=0;//保存文件长度
	fseek(f,0,SEEK_END);
	len=ftell(f);
//	printf("len:%ld\n",len);//测试输出
	assert(offset<=len&&(offset+size)<=len);
	// 0x12 0xAB 0x34 0xCD 
	unsigned  char buf[size];
	memset(buf,0,sizeof(buf));
	//移动文件指针	
	fseek(f,offset,SEEK_SET); 
	//创建数据
	unsigned  long num=0; 
 	int res=fread(buf,1,size,f);
 	int i=0;
 	if(res!=size)
 	{
 		perror("error");
		assert(1==0);		
	}
	if(type== SIGNED)
	{
		if(endian== LITTLE)
		{
			int i=0;
			for(i=0;i<size;i++)
			{
				num=num|(buf[i]<<(i*8));
			}
		}
		else
		{
			if(size==1)
			{
				char temp=buf[0];
				return  temp;
			}
			else if(size==2){
				short temp=0;
				temp|=buf[0];
				temp<<=8;
				temp|=buf[1];
				return temp;
			}
			int i=0;
			for(i=0;i<size;i++)
			{
					
					num<<=8;
					num|=buf[i];			
			}
		}
	}
	if(type== UNSIGNED)
	{
		if(endian== LITTLE)
		{
			int i=0;
			for(i=0;i<size;i++)
			{
				num=num|(buf[i]<<(i*8));
			}
		}
		else
		{
			int i=0;
			for(i=0;i<size;i++)
			{
					
					num<<=8;
					num|=buf[i];			
			}
		}
	}
	return num;
}
int main()
{
	FILE * fin=NULL;
	fin = fopen("file.bin","r");
	printf("%ld\n",getNumeric(fin,0,4,SIGNED,LITTLE));
	printf("%ld\n",getNumeric(fin,0,4,SIGNED,BIG));
	printf("%ld\n",getNumeric(fin,1,2,SIGNED,LITTLE));
	printf("%ld\n",getNumeric(fin,1,2,SIGNED,BIG));
	printf("%ld\n",getNumeric(fin,1,2,UNSIGNED,BIG));
	fclose(fin);
	/*fin2 = fopen("icon.png","r");     
	  binaryDumpAsASCII(fin2);     
	  fclose(fin2);          
	*/  
	return 0;   
}
