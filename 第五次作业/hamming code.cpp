#include<iostream>
 
using namespace std;

void BSC(int c[],float x){//BSC信道
    int i;
    int r;
    srand(time(0));
    for(i=0;i<=6;i++)
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
void decode(int d[]){//译码器
    int c1 = d[4] ^ d[0] ^ d[1] ^ d[3];
            int c2 = d[5] ^ d[0] ^ d[2] ^ d[3];
            int c3 = d[6] ^ d[1] ^ d[2] ^ d[3];
            if (c1 + c2 + c3 == 3) d[3] = 1 ^ d[3];
            else if (c1 + c2 == 2) d[0] = 1 ^ d[0];
            else if (c1 + c3 == 2) d[1] = 1 ^ d[1];
            else if (c2 + c3 == 2) d[2] = 1 ^ d[2];
    int results[4];
    results[0]=d[0];
    results[1]=d[1];
    results[2]=d[2];
    results[3]=d[3];
    
}
int main() {
    int data[10];
    int dataatrec[10],c,c1,c2,c3,i;
 
    cout<<"Enter 4 bits of data one by one\n";//输入二进制序列
    cin>>data[0];
    cin>>data[1];
    cin>>data[2];
    cin>>data[4];
 
    //Calculation of even parity
    data[6]=data[0]^data[2]^data[4];
data[5]=data[0]^data[1]^data[4];
data[3]=data[0]^data[1]^data[2];
 
cout<<"\nEncoded data is\n";//编码
for(i=0;i<7;i++)
        cout<<data[i];
    

    cout << endl;
    BSC(data,10);
    decode(data);
    cout << "译码结果为：";
    for(int i=0;i<4;i++){
        cout << data[i];
    }
    cout << endl;
return 0;
}
