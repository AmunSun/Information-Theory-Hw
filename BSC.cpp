#include<stdlib.h>
#include<iostream>
#include<time.h>
using namespace std;
int main(){
void bsc(int c[],float x);
float rand_num;
float p;
int input[10];
int i;
cout<<"请输入错误概率"<<endl;
cin>>p;
rand_num=100*p;
cout<<"请输入需要传输的二进制序列，长度为10，以空格分割。"<<endl;
for(i=0;i<=9;i++){
cin>>input[i];
}
cout<<"输入的二进制序列为：";
for(i=0;i<=9;i++){
cout<<input[i];
}
cout<<endl;
bsc(input,rand_num);
cout<<"—————————————————-"<<endl;
cout<<"输出的二进制序列为：";
for(i=0;i<=9;i++){
cout<<input[i];
}
cout<<endl;
};
 
void bsc(int c[], float x){
int i;
int r;
srand(time(0));
for(i=0;i<=9;i++)
{
r=rand()%100+1;
if (r>=x)
{         /*表示进入正确区间*/
c[i]=c[i];
}
else
{           /*表示进入错误区间*/
if(c[i]==0)
c[i]=1;
else c[i]=0;
}
}
}
