LL exp_mod(LL a, LL b, LL p)
{
    LL tmp = a % p, ans =1;
    while(b)
    {
        if(b & 1)  ans = ans * tmp % p;
        tmp = tmp*tmp % p;
        b >>=1;
    }
    return  ans;
}

LL C(LL n, LL m, LL p)
{
    if(m > n)
    	return 0;
    return  fac[n]*exp_mod(fac[m]*fac[n-m], p-2, p) % p;//ÄæÔª
}

LL Lucas(LL n, LL m, LL p)
{
    if(m ==0)
    	return 1;
    return  (C(n%p, m%p, p)*Lucas(n/p, m/p, p))%p;
}

