/*
Source problem link - HORRIBLE on spoj 
http://www.spoj.com/problems/HORRIBLE/ 
Segment tree with lazy propagation
lazy[index] - array for updating the values.
tree[index] - array for finding the sum of elements in a particular range.
Basic technique used - update the array elements range when they are required to be updated 
					   till then keep hold the sum which is to be updated in that range .
*/
#include<bits/stdc++.h>
using namespace std;
#define S(x) scanf("%d",&x)
#define fl(i , a, b) for(i = a; i<b; i++)
#define MAX 100010
ll a[MAX] , tree[4*MAX] , lazy[4*MAX];
void propagate(int ss ,int se, int index)
{
	tree[index] += lazy[index]*(se-ss+1);
	if(ss!=se)
	{
		lazy[2*index+1]+= lazy[index];
		lazy[2*index+2]+= lazy[index];
	}
	lazy[index] = 0 ;
}
void update(int ss, int se, int qs, int qe, int index ,ll value)
{
	if(lazy[index]!=0)
		propagate(ss, se, index);
	if(qs>se || qe<ss)
		return;
	if(qs<=ss && qe>=se)
	{
		lazy[index] = value;
		propagate(ss, se, index);
		return ;
	}
	int mid = (ss+se)/2;
	update(ss, mid , qs, qe, 2*index+1 , value);
	update(mid+1, se, qs ,qe ,2*index+2 , value);
	tree[index] = tree[2*index+1] + tree[2*index+2];
}
ll get(int ss, int se, int qs, int qe, int index)
{
	if(lazy[index]!=0)
		propagate(ss, se, index);
	if(qs>se || qe<ss)
		return 0;
	if(qs<=ss && qe>=se)
		return tree[index];

	int mid = (ss+se)/2;
	return get(ss, mid, qs ,qe , 2*index+1) + get(mid+1 , se, qs , qe, 2*index+2);
}
void build(int ss, int se, int index)
{
	if(ss==se)
	{
		tree[index] = a[ss];
		return;
	}
	int mid= (ss+se)/2;
	build(ss , mid , 2*index+1);
	build(mid+1, se,2*index+2);
	tree[index] = tree[2*index+1] + tree[2*index+2];
}
int main()
{
	int t , i  , type , l ,r , q , n;
	ll val , ans;  
	S(t);
	while(t--)
	{
		fl(i , 0 , 4*MAX)
			lazy[i] =0 ;
		S(n); S(q);
		build(0 , n-1, 0);
		fl(i , 0, q)
		{
			S(type) ; S(l) ; S(r);
			if(type==0)
			{
				cin>>val;
				update(0 , n-1, l-1, r-1, 0 , val);
			}
			else 
			{
				ans = get(0 , n-1, l-1 , r-1 , 0);
				cout<<ans<<endl;
			}
		}
	}
	return 0;
}
