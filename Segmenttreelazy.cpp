/*
Source problem link - HORRIBLE on spoj 
http://www.spoj.com/problems/HORRIBLE/ 
Segment tree with lazy propagation
lazy[index] - array for updating the values.
tree[index] - array for finding the sum of elements in a particular range.
Basic technique used - update the array elements range when they are required to be updated 
					   till then keep hold the sum which is to be updated in that range .
qs - query starting
qe - query ending
ss - segment starting
se - segment ending
2*index+1 and 2*index+2 as childs and index as their parent.
*/
/*
Source problem link - HORRIBLE on spoj 
http://www.spoj.com/problems/HORRIBLE/ 
Segment tree with lazy propagation
lazy[index] - array for updating the values.
tree[index] - array for finding the sum of elements in a particular range.
Basic technique used - update the array elements range when they are required to be updated 
                       till then keep hold the sum which is to be updated in that range .
qs - query starting
qe - query ending
ss - segment starting
se - segment ending
2*index+1 and 2*index+2 as childs and index as their parent.
*/
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define S(x) scanf("%d",&x)
#define fl(i , a, b) for(i = a; i<b; i++)
#define MAX 100010
ll a[MAX] , t[4*MAX] , lazy[4*MAX];
void propagate(int ss ,int se, int idx)
{
    t[idx] += lazy[idx]*(se-ss+1);
    if(ss!=se)
    {
        lazy[2*idx+1]+= lazy[idx];
        lazy[2*idx+2]+= lazy[idx];
    }
    lazy[idx] = 0 ;
}
void update(int ss, int se, int qs, int qe, int idx ,ll value)
{
    if(lazy[idx]!=0)
        propagate(ss, se, idx);
    if(qs>se || qe<ss)
        return;
    if(qs<=ss && qe>=se)
    {
        lazy[idx] = value;
        propagate(ss, se, idx);
        return ;
    }
    int mid = (ss+se)/2;
    update(ss, mid , qs, qe, 2*idx+1 , value);
    update(mid+1, se, qs ,qe ,2*idx+2 , value);
    t[idx] = t[2*idx+1] + t[2*idx+2];
}
ll get(int ss, int se, int qs, int qe, int idx)
{
    if(lazy[idx]!=0)
        propagate(ss, se, idx);
    if(qs>se || qe<ss)
        return 0;
    if(qs<=ss && qe>=se)
        return t[idx];

    int mid = (ss+se)/2;
    return get(ss, mid, qs ,qe , 2*idx+1) + get(mid+1 , se, qs , qe, 2*idx+2);
}
void build(int ss, int se, int idx)
{
    if(ss==se)
    {
        t[idx] = a[ss];
        return;
    }
    int mid= (ss+se)/2;
    build(ss , mid , 2*idx+1);
    build(mid+1, se,2*idx+2);
    t[idx] = t[2*idx+1] + t[2*idx+2];
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
