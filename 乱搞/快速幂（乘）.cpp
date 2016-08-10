inline int pow(int x,int k)
{
	int ans=1;
	for(;k;k>>=1)
	{
		if(k&1)(ans*=x)%=MOD;
		x*=x;
	}
	return ans;
}
inline ll mul(ll x,ll y) {
    ll ret = 0;
    for (; y; y >>= 1) {
        if (y & 1)
            (ret += x) %= MOD;
        (x <<= 1) %= MOD;
    }
    return ret;
}
