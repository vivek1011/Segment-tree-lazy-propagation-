/*
How to find the occurence of a maximum element occuring in a range using segtrees. 
*/
#include<bits/stdc++.h>
using namespace std;
#define S(x) scanf("%d",&x)
#define P(x) printf("%d",x)
#define fl(i , a, b) for(i = a; i<b; i++)
#define MOD 1000000007
#define MAX 1000000010
#define ll long long
#define mp make_pair
#define pb push_back
typedef pair<int,int> pp;
int max1 , max2 ; 
int a[123457];
struct s
{
	int maxi , c; 
}t[400002];
void build(int ss , int se, int index)
{
	if(ss==se)
	{
		t[index].maxi = a[ss];
		t[index].c = 1; 
		return ; 
	}
	int mid = (ss+se)/2; 
	build(ss , mid , 2*index+1) ;
	build(mid+1 , se, 2*index+2);
	max1 = t[2*index+1].maxi ; max2 =t[2*index+2].maxi;
	if(max1 == max2)
	{
		t[index].maxi = max1; 
		t[index].c = t[2*index+1].c + t[2*index+2].c; 
	}
	else	
	{
		if(max1>max2)
		{
			t[index].maxi = t[2*index+1].maxi ; 
			t[index].c =  t[2*index+1].c; 
		}
		else
		{
			t[index].maxi = t[2*index+2].maxi;
			t[index].c = t[2*index+2].c;  
		}
	}
}
pair<int, int> get(int qs, int qe, int ss , int se, int index)
{
	if(qs>se || qe<ss)
	{
		pp tmp = mp(0 , 0 );
		return tmp ; 
	}
	if(qs<=ss && qe>=se)
	{
		pp tmp = mp(t[index].maxi , t[index].c);
		return tmp ; 
	}
	int mid = (ss+se)/2 ;
	pp tmp1 = get(qs, qe, ss , mid , 2*index+1);
	pp tmp2 = get(qs, qe, mid+1 , se ,2*index+2);
	if(tmp1.first==tmp2.first)
	{
		return mp(tmp1.first , tmp1.second+ tmp2.second);
	}
	else if(tmp1.first>tmp2.first)
	{
		return mp(tmp1.first , tmp1.second); 
	}
	return mp(tmp2.first , tmp2.second) ; 
}
int main()
{
	//std::ios_base::sync_with_stdio(false);
	int n , m , l ,r , i ;
	pp tmp ; 
	cin>>n>>m;
	fl(i , 0 , n)cin>>a[i];
	build(0, n-1 , 0); 
	fl(i , 0, m )
	{
		cin>>l>>r; 
		l--; r--; 
		tmp = get(l , r, 0, n-1, 0);
		cout<<tmp.second<<endl;
	}
	return 0;
}
