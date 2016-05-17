/*
Dealing with dictionary, computes the minhash matrix.
*/
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string.h>
#include <time.h>
#include <algorithm>
#include <map>
#define pb push_back
using namespace std;
int myrand() {
	int ret=(rand()<<16)+rand();
	if(ret<0) ret=-ret;
	return ret;
}
vector<int> A[500000];
char buf[1000];
map<int,int> hf;
int main()
{
	FILE *fin=fopen("words.txt","r");
	puts("Loading the dictionary...");
	int cnt=0;
	while(fscanf(fin,"%s",buf)!=EOF) {
		int l=strlen(buf);
		for(int i=0;i<l;i++) if(buf[i]>='A'&&buf[i]<='Z') buf[i]-='A',buf[i]+='a';
		for(int i=0;i<l;i++) {
			for(int j=i;j<l;j++) {
				int have[27];
				memset(have,0,sizeof(have));
				for(int k=i;k<=j;k++) have[buf[k]-'a']=1;
				int x=0;
				for(int k=0;k<26;k++) x=(x<<1)+have[k];
				A[cnt].pb(x);
			}
		}
		sort(A[cnt].begin(),A[cnt].end());
		unique(A[cnt].begin(),A[cnt].end());
		cnt++;
	}
	printf("%d words totally.\n",cnt);
	printf("Costs %d ms.\n",clock());
	fclose(fin);
	puts("Please input the number of hash functions:");
	int HN;
	scanf("%d",&HN);
	puts("Building the matrix...");
	int start=clock();
	FILE *fout=fopen("matrix.txt","w");
	for(int i=1;i<=HN;i++) {
		hf.clear();
		for(int j=0;j<cnt;j++) {
			int minn=1000000000;
			for(int k=0;k<A[j].size();k++) {
				int x=A[j][k];
				if(!hf[x]) hf[x]=myrand()%((1<<26)-1)+1;
				minn=min(minn,hf[x]);
			}
			fprintf(fout,"%d ",minn);
		}
		fprintf(fout,"\n");
	}
	fclose(fout);
	printf("Costs %d ms.\n",clock()-start);
	while(1);
	return 0;
}
