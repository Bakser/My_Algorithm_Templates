inline void build(){
	sort(h+1,h+m+1,cmp);//dfn
	point=head2;en=0;edges=e2;s[top=1]=1;
	for(int i(1);i<=m;i++)
	{
		int p(h[i]),x(LCA(p,s[top]).x);
		for(;dep[x]<dep[s[top]];top--)
			if(dep[x]>=dep[s[top-1]])addedge(x,s[top]);
			else addedge(s[top-1],s[top]);
		if(s[top]!=x)s[++top]=x;
		if(s[top]!=p)s[++top]=p;
	}
	while(--top)addedge(s[top],s[top+1]);
}
