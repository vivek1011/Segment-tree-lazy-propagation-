void propagate(int ss ,int se, int idx)
{
	t[idx] += lazy[idx] ;
	if(ss!=se)
	{
		lazy[2*idx+1]+= (-1)*lazy[idx];
		lazy[2*idx+2]+= (-1)*lazy[idx];
	}
	lazy[idx] = 0 ;
}
void update(int qs , int qe , int ss , int se ,ll val, int idx)
{
	if(lazy[idx]!=0)
		propagate(ss, se, idx);
	if(qs>se || qe<ss)
		return;
	if(qs<=ss && qe>=se)
	{
		lazy[idx] = val;
		propagate(ss, se, idx);
		return ;
	}
	int mid = (ss+se)/2;
	update(qs, qe, ss , mid , val , 2*idx+1 );
	update(qs, qe , mid+1, se , val , 2*idx+2 );
	t[idx] = t[2*idx+1] + t[2*idx+2];
}
