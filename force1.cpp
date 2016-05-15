#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>

using namespace std;

const int DICT_SIZE = 310000;
const int MAXLEN = 50;
const int LIST_LEN = 10;
const char *DICT_NAME = "dict.txt";

string Word[DICT_SIZE];int dictcnt;

void GetDict()
{
	FILE *DICT = fopen(DICT_NAME,"r");
	char tmpword[MAXLEN];
	dictcnt = 0;
	
	while (fscanf(DICT,"%s",tmpword) == 1)
	{
		dictcnt++;
		Word[dictcnt] = string((const char*)tmpword);
	}
	//for (int i = 1;i <= dictcnt;i++) cout << Word[i] << endl;
	return;
}

char str[MAXLEN];int len;
int edist[DICT_SIZE];
int arr[DICT_SIZE];

int dp[MAXLEN][MAXLEN];

int Min(int x,int y) {return (x<y)?x:y;}
void DP()
{
	int i,j,k;
	
	for (i = 1;i <= dictcnt;i++)
	{
		for (j = 0;j <= len;j++)
			for (k = 0;k <= (int)Word[i].size();k++)
			{
				if (j == 0 && k == 0) {dp[j][k] = 0;continue;}
				if (j == 0) {dp[j][k] = k;continue;}
				if (k == 0) {dp[j][k] = j;continue;}
				
				dp[j][k] = Min(dp[j-1][k] + 1,dp[j][k-1] + 1);
				dp[j][k] = Min(dp[j][k],dp[j-1][k-1] + 1);
				if (str[j-1] == Word[i][k-1])
					dp[j][k] = Min(dp[j][k],dp[j-1][k-1]);
			}
		edist[i] = dp[len][(int)Word[i].size()];
	}
	
	return;
}

bool cmp(int x,int y) {return edist[x] < edist[y];}

int main()
{
	int i,j;
	
	GetDict();
	
	while (true)
	{
		scanf("%s",str);
		len = strlen(str);
		
		
		DP();
		
		for (i = 1;i <= dictcnt;i++) arr[i] = i;
		sort(arr+1,arr+dictcnt+1,cmp);
		
		for (i = 1;i <= LIST_LEN;i++)
		{
			printf("%4d.",i);
			cout << "  " << Word[arr[i]];
			for (j = 1;j <= MAXLEN - (int)Word[arr[i]].size();j++)
				cout << " ";
			cout << "Dist=" << edist[arr[i]] << endl;
		}
	}
	
	return 0;
}
