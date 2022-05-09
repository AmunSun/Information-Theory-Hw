#include <iostream>

#include <iomanip>

using namespace std;

struct HNode

{

         int weight;   //结点权值

           int parent;   //双亲指针

         int LChild;       //左孩子指针

         int RChild ;      //右孩子指针

};

struct HCode

 {

         char data;

         char code[100];

 };

 

class Huffman

{

private:

         HNode* HTree;                   //Huffman树

         HCode*HCodeTable;               //Huffman编码表

         char str[1024];                  //输入的原始字符串

         char leaf[256];                  //叶子节点对应的字符

         int  a[256];                     //记录每个出现的字符的个数

public:

         int  n;                          //叶子节点数

         void init();                                //初始化

         void CreateHTree();                      //创建huffman树

         void CreateCodeTable();                    //创建编码表

         void Encode(char *d);                           //编码

         void Decode(char *s, char *d);               //解码

         void print(int i,int m);                   //打印Huffman树

         void SelectMin(int &x, int &y, int s, int e );    //选择两个最小的节点

         void Reverse(char* s);                    //逆转编码（代码编码为叶子结点到根，而哈夫曼编码本该是根到叶子节点，所以需要逆转）

           ~ Huffman();//析构函数

};

void Huffman::init()

{

         int nNum[256]= {0};                //记录每一个字符出现的次数

         int ch = cin.get();

         int i=0;

         while((ch!='\r')&& (ch!='\n'))

         {

                      nNum[ch]++;                   //统计字符出现的次数

                     str[i++]= ch;                   //记录原始字符串

                     ch= cin.get();                   //读取下一个字符

         }

         str[i]='\0';

         cout<<"各个字符出现的次数:"<<endl;

   n = 0;

   for ( i=0;i<256;i++)

         {

                   if(nNum[i]>0)              //若nNum[i]==0说明该字符未出现

                   {

                            leaf[n]= (char)i;

                            a[n]= nNum[i];

                            n++;

                            cout<<(char)i<<"-"<<nNum[i]<<"  ";

                   }

         }

         cout<<endl;

}

void Huffman::CreateHTree()

{

         HTree= new HNode [2*n-1];          //根据权重数组a[0..n-1]初始化Huffman树

         for(int k = 0; k < n; k++)

         {

                   HTree[k].weight= a[k];

                   HTree[k].LChild= HTree[k].RChild = HTree[k].parent = -1;

         }

    int x, y;

    for (int i = n; i < 2*n-1;i++)      //开始建Huffman树

         {

                   SelectMin(x,y, 0, i);          //从1~i中选出两个权值最小的结点

                   HTree[x].parent= HTree[y].parent = i;

                   HTree[i].weight= HTree[x].weight+ HTree[y].weight;

                   HTree[i].LChild= x;

                   HTree[i].RChild= y;

                   HTree[i].parent= -1;

         }

}

 

void Huffman::SelectMin(int &x, int&y, int s, int e )

{

         int i;

         for( i=s; i<=e;i++)

                   if(HTree[i].parent == -1)

                   {

                            x=y= i;    break;          //找出第一个有效权值x，并令y=x

                   }

   for ( ; i<e;i++)

                   if(HTree[i].parent == -1)         //该权值未使用过

                   {

                            if( HTree[i].weight< HTree [x].weight)

            {

                                     y= x;   x = i;           //迭代，依次找出前两个最小值

                            }

                            else if ((x==y) || (HTree[i].weight< HTree [y].weight) )

                                     y= i;                 //找出第2个有效权值 y

                   }

}

void Huffman::print(int i, int m)

{

         if(HTree[i].LChild == -1)

             cout<<setfill(' ')<<setw(m+1)<<leaf[i]<<setfill('-')<<setw(10-m)<<'\n';

         else

         {

                   cout<<setfill(' ')<<setw(m+1)<<HTree[i].weight<<setfill('-')<<setw(10-m)<<'\n';

                   print(HTree[i].LChild,m+1);

                   print(HTree[i].RChild,m+1);

         }

}

void Huffman::CreateCodeTable()

{

    HCodeTable = new HCode[n]; //生成编码表

         for(int i=0;i<n;i++)

         {

                   HCodeTable[i].data= leaf[i];

        int child = i;                                            //孩子结点编号

        int parent =HTree[i].parent;     //当前结点的父结点编号

        int k=0;

        while(parent!=-1)

                   {

                      if(child==HTree[parent].LChild)              //左孩子标‘0’

                           HCodeTable[i].code[k]= '0';

                      else

                            HCodeTable[i].code[k]= '1' ; //右孩子标‘1’

                      k++;

                      child = parent;                                      //迭代

                      parent =HTree[child].parent;

                   }

                   HCodeTable[i].code[k]= '\0';

                   Reverse(HCodeTable[i].code);                 //将编码字符逆置，请读者自行实现

                   cout<<HCodeTable[i].data<<'\t'<<HCodeTable[i].code<<endl;

         }

}

 

void Huffman::Encode(char *d)//d为编码后的字符串

{

                char*s = str;

                   while(*s!='\0')

                   {

                            for(int i=0;i<n;i++)

                                     if(*s == HCodeTable[i].data )

                                     {

                                               strcat(d,HCodeTable[i].code);

                                               break;

                                     }

                            s++;

                   }

}

void Huffman::Decode(char* s, char *d)         //s为编码串，d为解码后的字符串

{

         while(*s!='\0')

         {

                   int parent = 2*n-2;                                      //根结点在HTree中的下标

              while(HTree[parent].LChild!=-1)     //如果不是叶子结点

                   {

                            if(*s=='0')

                        parent = HTree[parent].LChild;

                  else

                           parent =HTree[parent].RChild;

                            s++;

                   }

                   *d= HCodeTable[parent].data;

                   d++;

         }

}

void Huffman::Reverse(char* s)

{

         char ch;

         int len = strlen(s);

 

         for(int i=0;i<len/2;i++)

         {

                   ch= s[i];

                   s[i]= s[len-i-1];

                  s[len-i-1] = ch;

         }

}

Huffman::~ Huffman()

 {

         delete  []HTree;

         delete  []HCodeTable;

 }

 //测试的主函数

int main()

{

         Huffman HFCode;

         cout<<"请输入要编码的字符串：";

         HFCode.init();

         cout<<"创建Huffman树:"<<endl;

         HFCode.CreateHTree();

         HFCode.print(2*HFCode.n-2,1);

 

         cout<<"创建Huffman编码表:"<<endl;

         HFCode.CreateCodeTable();

 

         char d[1024]={0};

         HFCode.Encode(d);

         cout<<"编码结果："<<d<<endl;

 

         char s[1024]={0};

         HFCode.Decode(d,s);

         cout<<"解码结果："<<s<<endl;
}

