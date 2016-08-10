inline ll bsgs(ll a,ll b,ll p)//a^x=b(mod p)
{
    ll m((ceil)(sqrt(p))),e(1),v;
    v=inv(pow(a,m,p),p);
    if(v==-1)return -1;
    x.clear();
    x[1]=0;
    for(int i(1);i<m;i++)
    {
        e=mul(e,a,p);
        if(!x.count(e))x[e]=i;
    }
    for(int i(0);i<m;i++)
    {
        if(x.count(b))return i*m+x[b];
        b=mul(b,v,p);
    }
    return -1;
}

