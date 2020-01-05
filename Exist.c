//是否存在一个只由2和0构成的身份证号

//因为身份证校验的算法GitHub上肯定有
//所以一开始打算自己造轮子的，想想这既然不是作业，那就没必要给自己找麻烦
//GitHub上现成的身份证校验且基于C语言的有：
//1. https://github.com/sincerefly/IDCardQuery/blob/master/c/query.c
//2. https://github.com/Im670/idcode_check/blob/master/id_check.c

//出于简便考虑，我们放弃了鲁棒性，使用了2

#include<stdio.h>


int id_check(char* pidcode)
//传入：char型数组，长度为18
//传出：正确则return1，错误则return0
{
	int weight[] = { 7,9,10,5,8,4,2,1,6,3,7,9,10,5,8,4,2 };    //十七位数字本体码权重
	char validate[] = { '1','0','X','9','8','7','6','5','4','3','2' };    //mod11,对应校验码字符值 

	int sum = 0;
	int mode = 0;
	int i = 0;

	for (i = 0; i < 17; i++)
	{
		sum += ((pidcode[i] - '0')*weight[i]);
	}
	mode = sum % 11;

	if (pidcode[17] == validate[mode])
	{
		return 1;
	}

	//printf("Error:%c (%c)\n", pidcode[17], validate[mode]);

	return 0;
}

int main(void)
{
	char ID[18];
	//吉林省吉林市昌邑县在2020年2月2日出生的号码220202 20200202 XXXX
	//试图求解是否存在只包含2的身份证号
	//思路1：规定前17位计算18位（我原本打算这么做然后自己再写一个int IDMOD(int *number)）
	//思路2：四个for循环（简单粗暴就是你了）
	ID[0] = '2';
	ID[1] = '2';
	ID[2] = '0';
	ID[3] = '2';
	ID[4] = '0';
	ID[5] = '2';

	ID[6] = '2';
	ID[7] = '0';
	ID[8] = '2';
	ID[9] = '0';
	ID[10] = '0';
	ID[11] = '2';
	ID[12] = '0';
	ID[13] = '2';

	int i, j, k, m;
	int flag_Exist = 0;
	for (i = 0; i <= 2; ++i)
	{
		if (i == 1)
			continue;
		ID[14] = i + '0';
		for (j = 0; j <= 2; ++j)
		{
			if (j == 1)
				continue;
			ID[15] = j + '0';
			for (k = 0; k <= 2; ++k)
			{
				if (k == 1)
					continue;
				ID[16] = k + '0';
				for (m = 0; m <= 2; ++m)
				{
					if (m == 1)
						continue;
					ID[17] = m + '0';
					//真·暴力求解
					//因为要看是不是2/0数字，所以忽略X的存在

					int n = id_check(ID);
					if (n == 1)
					{
						flag_Exist = 1;
						printf("22020220200202%d%d%d%d存在且合法\n", i, j, k, m);
					}
				}
			}
		}
	}

	if (flag_Exist==0)
	{
		printf("不存在这样一个仅由0和2构成的合法身份证号\n");
		return -1;
	}

	return 0;
}