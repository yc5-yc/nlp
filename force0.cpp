#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <map>

#define All for(_=0;_<26;_++)
int _;

using namespace std;

const int NMAX = 100000;
const int k = 10;
const char *F_DICT = "dict.txt";

int ctoi(char x) {return x - 'a';}


struct NODE
{
	bool end;
	NODE *pre,*trans[30];
};
NODE trie[NMAX];int cnt;
NODE* New()
{
	cnt++;
	return trie + cnt;
}
NODE* Insert(NODE *it,char *x)
{
	if ((*x) == '\0')
	{
		it -> end = true;
		return it;
	}
	if (!it -> trans[ctoi(*x)])
	{
		it -> trans[ctoi(*x)] = New();
		it -> trans[ctoi(*x)] -> pre = it;
	}
	return Insert(it -> trans[ctoi(*x)],x+1);
}
void Print()
{
	int i;
	for (i = 0;i <= cnt;i++)
	{
		printf("| %d%c",i,(trie[i].end)?'E':' ');
		All if (trie[i].trans[_]) printf("  %c -> %d",'a'+_,trie[i].trans[_]-trie);
		printf("\n");
	}
	return;
}
int pretrans(NODE *x)
{
	All if (x -> pre -> trans[_] == x) return _;
}
void Printstr(NODE *x)
{
	if (x == trie) return;
	Printstr(x -> pre);
	printf("%c",pretrans(x)+'a');
	return;
}


struct ST
{
	NODE *cur;
	int len;
	double prob;
	
	ST(){}
	ST(NODE *cur_,int len_,double prob_){cur = cur_;len = len_;prob = prob_;}
	
	bool operator < (const ST &x) {return prob < x.prob;}
	bool operator > (const ST &x) {return prob > x.prob;}
	bool operator <= (const ST &x) {return prob <= x.prob;}
	bool operator >= (const ST &x) {return prob >= x.prob;}
};

struct STP
{
	NODE *cur;
	int len;
	
	STP(){}
	STP(NODE *cur_,int len_){cur = cur_;len = len_;}
	
	bool operator < (const STP &x)
	{
		if (len != x.len) return len < x.len;
		else return (cur-trie) < (x.cur-trie);
	}
	bool operator < (const STP &x) const
	{
		if (len != x.len) return len < x.len;
		else return (cur-trie) < (x.cur-trie);
	}
};
map<STP,bool> mp;

namespace HEAP
{
	ST heap[5*NMAX];int hcnt;
	
	void Up(int x)
	{
		if (x == 1) return;
		if (heap[x] > heap[x>>1])
		{
			//cout << "SWAP:" << heap[x].prob << " " << heap[x>>1].prob << endl;
			swap(heap[x],heap[x>>1]);
			Up(x>>1);
		}
		return;
	}
	void Down(int x)
	{
		int tmp = x << 1;
		if (tmp > hcnt) return;
		if (tmp + 1 <= hcnt && heap[tmp+1] > heap[tmp]) tmp++;
		if (heap[tmp] > heap[x])
		{
			swap(heap[x],heap[tmp]);
			Down(tmp);
		}
		return;
	}
	
	void Push(ST x)
	{
		
		if (mp.find(STP(x.cur,x.len)) == mp.end())
		{
			//cout << "Ins" << endl;
			hcnt++;
			heap[hcnt] = x;
			Up(hcnt);
			//cout << heap[1].prob << endl;
		}
		mp[STP(x.cur,x.len)] = true;
		
		return;
	}
	void Pop()
	{
		swap(heap[1],heap[hcnt]);
		hcnt--;
		Down(1);
		return;
	}
	ST Top()
	{
		return heap[1];
	}
	bool Empty()
	{
		return (hcnt == 0);
	}
	
	void Init()
	{
		hcnt = 0;
		return;
	}
}

char rin[NMAX];

int main()
{
	int tmp;
	FILE *f_dict = fopen(F_DICT,"r");
	
	while (tmp = fscanf(f_dict,"%s",rin) > 0)
	{
		cout << rin << " " << tmp << endl;
		Insert(trie,rin);
		//Print();
		cout << endl;
	}
	Print();
	
	int rlen,anscnt,curc; // rinlen,anscnt,curchar
	ST st;
	
	// -debug
	int heapmax;
	// ~debug
	
	while (true)
	{
		scanf("%s",rin);
		
		mp.clear();
		rlen = strlen(rin);
		anscnt = 0;
		
		
		// -debug
		heapmax = 0;
		// ~debug
		HEAP::Init();
		HEAP::Push(ST(&trie[0],0,1.0));
		
		while (!HEAP::Empty())
		{
			// -debug
			//printf("%d ",HEAP::hcnt);
			if (heapmax < HEAP::hcnt) heapmax = HEAP::hcnt;
			// ~debug
			
			st = HEAP::Top();
			
			//cout << "USE ";
			//Printstr(st.cur);
			//cout << " " << st.len << " " << st.prob << endl;
			
			HEAP::Pop();
			
			//Printstr(st.cur);cout << " " << st.len << " " << st.prob << endl;
			//cout << "!" << endl;
			
			if (st.len == rlen)
			{
				if (st.cur -> end)
				{
					printf("\n");
					Printstr(st.cur);
					printf(" %.6lf\n",st.prob);
					
					anscnt++;
					if (anscnt == k) break;
				}
				
				All
					if (st.cur -> trans[_])
						HEAP::Push(ST(st.cur -> trans[_],st.len,st.prob * 0.5));
			}
			else
			{
				curc = rin[st.len]-'a';
				
				if (st.cur -> trans[curc])
				{
					HEAP::Push(ST(st.cur -> trans[curc],st.len+1,st.prob));
					//cout << "PUSH:";
					//Printstr(st.cur -> trans[curc]);
					//cout << " " << st.len+1 << " " << st.prob << endl;
				}
				All
				{
					//if (_ == st.trans[rin[st.len]-'a']) continue;
					if (st.cur -> trans[_])
					{
						HEAP::Push(ST(st.cur -> trans[_],st.len,st.prob * 0.5));
						HEAP::Push(ST(st.cur -> trans[_],st.len+1,st.prob * 0.5));
						//cout << "PUSH:";
						//Printstr(st.cur -> trans[_]);
						//cout << " " << st.len << " " << st.prob * 0.5 << endl;
						//cout << "PUSH:";
						//Printstr(st.cur -> trans[_]);
						//cout << " " << st.len+1 << " " << st.prob * 0.5 << endl;
					}
				}
				HEAP::Push(ST(st.cur,st.len+1,st.prob * 0.5));
				//cout << "PUSH:";
				//Printstr(st.cur);
				//cout << " " << st.len+1 << " " << st.prob * 0.5 << endl;
			}
			
		}
		
		//-debug
		printf("\n\nHeapSizeMax = %d\n",heapmax);
		//~debug
		
		printf("\n");
	}
	
	return 0;
}
