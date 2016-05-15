#include <cstdio>
#include <vector>
#include <string>
#include <cstdlib>
#define pb push_back
using namespace std;
int myrand() {
	int ret=(rand()<<15)+rand();
	if(ret<0) ret=-ret;
	return ret;
}
vector<string> A;
int main()
{
	puts("Please input the filename of the dict you want to load:");
	char dict[1000];
	scanf("%s",dict);
	FILE *fin=fopen(dict,"r");
	char temp[1000];
	int cnt=0;
	while(fscanf(fin,"%s",temp)!=EOF) {
		A.pb(string(temp));
		cnt++;
	}
	fclose(fin);
	puts("Loading...");
	puts("Please input the maximal number of edits:");
	int dis;
	scanf("%d",&dis);
	int N;
	puts("Please input the number of word you want to generate:");
	scanf("%d",&N);
	char file[1000];
	puts("Please input the filename:");
	scanf("%s",file);
	FILE *fout=fopen(file,"w");
	for(int i=1;i<=N;i++) {
		int x=myrand()%cnt;
		for(int j=0;j<A[x].size();j++) temp[j]=A[x][j];
		temp[A[x].size()]=0;
		fprintf(fout,"%s ",temp);
		int step=myrand()%dis+1;
		fprintf(fout,"%d ",step);
		int len=A[x].size();
		while(step--) {
			int pos=rand()%len;
			int t=rand()%3;
			if(t==0) {
				for(int j=len-1;j>pos;j--) temp[j+1]=temp[j];
				temp[pos+1]=myrand()%26+'a';
				len++;
				temp[len]=0;
			}else if(t==1) {
				for(int j=pos;j<len-1;j++) temp[j]=temp[j+1];
				len--;
				temp[len]=0;
			}else temp[pos]=myrand()%26+'a';
		}
		fprintf(fout,"%s\n",temp);
	}
	fclose(fout);
	getchar();getchar();
	return 0;
}
