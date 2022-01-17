#include<stdio.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<assert.h>
#define  LITTLE 0
#define  BIG     1
#define  SIGNED 0
#define  UNSIGNED 1

//Computer Forensics
//ChengZhang
//Assignment 1
//For this Assignment, we need read the file, and then transfor it to the binary.
//2019/1/22

unsigned long getNumeric(FILE *f,
                         long offset,
                         int size,
                         char type,
                         char endian)
{

//GetNumeric
//For this function, we need return the number
    
    assert(f!=NULL);//if the F is null, it cannot calculate.
    //determine the size must be 1，2，4
    assert(size==1||size==2||size==4);
    //type must be signed or unsigned, if not, stop
    //endian must be big or little
    assert(type==SIGNED||type==UNSIGNED);
    assert(endian==BIG ||endian==LITTLE);
    //check pointer
    int len=0;//save the length
    fseek(f,0,SEEK_END);
    len=ftell(f);
    //    printf("len:%ld\n",len);//test output
    assert(offset<=len&&(offset+size)<=len);
    // 0x12 0xAB 0x34 0xCD
    unsigned  char buf[size];
    memset(buf,0,sizeof(buf));
    //move the pointer
    fseek(f,offset,SEEK_SET);
    //create data
    unsigned  long num=0;
    int res=fread(buf,1,size,f);
    int i=0;
    if(res!=size)
    {
        perror("error");
        assert(1==0);
    }
    //if it is signed
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
    //if it is unsigned
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

//BinaryDumpAsASCII
//For this function we need transdor file to the binary.
void  binaryDumpAsASCII(FILE *f)
{
    char buffer[16]={0};
    int len=0;//save the length
    fseek(f,0,SEEK_END);
    len=ftell(f);
    fseek(f,0,SEEK_SET);
    //    printf("len:%d\n",len);
    int num=0;
    while(1)
    {
        int res =fread(buffer,1,16,f);
        num+=res;
        //    printf("res=%d\n",res);
        int i=0;
        //print
        for(i=0;i<16;i++){
            printf("%02hhx ",buffer[i]&0xff);
        }
        printf("\t\t");
        for(i=0;i<16;i++){
            if(buffer[i]<32||buffer[i]>126)
                printf(" ");
            else
                printf("%c",buffer[i]);
        }
        printf("\n");
        if(num>=len) break;
    }
    
    
}

//this is the main
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
