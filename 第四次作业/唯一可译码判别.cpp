#include<stdio.h>
#include<string>
using namespace std;
char c[100][50];
char f[300][50];
int N, sum = 0; // N为输入码字的个数, sum为尼随后缀集合中码字的个数
int flag; //判断是否唯一可译标查位
void patterson(char c[],char d[]) //检测尾随后缀
{
    int i, j, k;
    for (i = 0;; i++)
    {
        if (c[i] == '\0' && d[i] == '\0')   //字符一样跳出
            break;
        if (c[i] == '\0')   //d比c长，将d的尾随后缀放入f中
        {
            for (j = i; d[j] != '\0'; j++)f[sum][j - i] = d[j];
            f[sum][j - i] = '\0';
            for (k = 0; k < sum; k++)
            {
                if (strcmp(f[sum], f[k]) == 0)   //查看当前生成的尾随后缀在f集合中是否存在
                {
                    sum--; sum--; break;
                }
            }
            sum++;
            break;
        }
        if (d[i] == '\0')  //c比d长，将c的wei'sui后缀放入f中
        {
            for (j = i; c[j] != '\0'; j++)f[sum][j - i] = c[j];
            f[sum][j - i] = '\0';
            for (k = 0; k < sum; k++)
            {
                if (strcmp(f[sum], f[k]) == 0)   //查看当前生成的尾随后缀在f集合中是否存在
                {
                    sum--; break;
                }
            }
            sum++;
            break;
        }
        if (c[i] != d[i])
            break;
    }
}
int main()
{
    int i, j;
    printf("请输入码字的个数（小于100）：");   //输入码得个数
    scanf("%d", &N,10);
    while (N > 100)
    {
        printf("输入码字得个数过大，请输入小于100的数\n");
        printf("请输入码字的个数（小于100）：");
        scanf("%d", &N,10);
    }
    flag = 0;
    printf("请分别输入码字（每个码字长度小于50个字符）:\n");
    for (i = 0; i < N; i++)
    {
        scanf("%s", &c[i],51);
    }
    for(i=0;i<N-1;i++)    //判断如果码本身是否重复
        for (j = i + 1; j < N; j++)
        {
            if (strcmp(c[i], c[j]) == 0)
            {
                flag = 1; break;
            }
        }
    if (flag == 1)
        printf("这不是唯一可译码。\n");
    else
    {
        for (i = 0; i < N ; i++)  //根据原始编码生成的尾随后缀集合s[1]放入f中
        {
            for (j = i + 1; j < N; j++)
                patterson(c[i], c[j]);
        }
        for (i = 0;; i++)
        {
            int s = 0;
            for (j = 0; j < N; j++)
            {
                if (i == sum)
                {
                    s = 1; break;
                }
                else patterson(f[i], c[j]);
            }
            if (s == 1)break;
        }
        for (i = 0; i < sum; i++)   //判断p里面的字符串是否与s中的重复，重复则不是唯一的
        {
            for (j = 0; j < N; j++)
            {
                if (strcmp(f[i], c[j]) == 0)
                {
                    flag = 1;
                    break;
                }
            }
        }
        if (flag == 1)
            printf("这不是唯一可译码的。\n");
        else
            printf("这是唯一可译码。\n");
    }
    printf("尾随后缀集合为：");
    for (i = 0; i <= sum; i++)
        printf("\n%s", f[i]);
}
