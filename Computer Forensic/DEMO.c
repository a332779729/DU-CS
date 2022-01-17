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
	
	assert(f!=NULL);//���ԣ����fΪNULL�򲻽�������
	//���ȳ���unsigned�ĳ��� ���� 
	assert(size==1||size==2||size==4);
	//ȡֵ�ж�
	assert(type==SIGNED||type==UNSIGNED);
	assert(endian==BIG ||endian==LITTLE); 
	//�ļ�ָ��ƫ�Ƶ��ƶ�λ�ã�0Ϊ��ʼλ��
	//����ļ�ƫ��λ�ô����ļ����Ȼ���ƫ�ƼӶ�ȡ�����ݳ����ļ����ȣ�����
	int len=0;//�����ļ�����
	fseek(f,0,SEEK_END);
	len=ftell(f);
//	printf("len:%ld\n",len);//�������
	assert(offset<=len&&(offset+size)<=len);
	// 0x12 0xAB 0x34 0xCD 
	unsigned  char buf[size];
	memset(buf,0,sizeof(buf));
	//�ƶ��ļ�ָ��	
	fseek(f,offset,SEEK_SET); 
	//��������
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
