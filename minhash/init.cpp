/*
Init all bands information.
*/
#include <cstdio>
#include <algorithm>
#include <map>
#include <vector>
#define x first
#define y second
#define mp make_pair
#define pb push_back
using namespace std;
typedef pair<int,int> pii;
const int N=235886;
pii A[500000];
map<pii,int> C;
vector<int> C1[500000];
int main()
{
	FILE *fin=fopen("matrix.txt","r");
	for(int i=1;i<=5;i++) {
		C.clear();
		for(int j=1;j<=N;j++) fscanf(fin,"%d",&A[j].x);
		for(int j=1;j<=N;j++) fscanf(fin,"%d",&A[j].y);
		for(int j=1;j<=N;j++) C[A[j]]++;
		for(map<pii,int>::iterator p=C.begin();p!=C.end();p++) printf("%d\n",p->y);
		//printf("%d\n",C.size());
		break; 
	}
	fclose(fin);
	while(1);
	return 0;
}
