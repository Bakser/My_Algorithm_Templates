struct stack
{
	int s[N],top;
	inline void clr(){top=0;}
	inline void push(int x){s[top++]=x;}
	inline int front(){return s[--top];}
	inline bool emp(){return !(top);}
}s1,s2;
inline void tarjan(int x)
{
	s1.clr();
	s1.push(x);
	while(!s1.emp())
	{
		x=s1.front();
		if(!dfn[x])
		{
			dfn[x]=low[x]=++index;
			cur[x]=point[x];
			s2.push(x);in[x]=1;
		}
		bool finish(1);
		for(int i(point[x]);i;i=edges[i].next)
		if(!dfn[edges[i].v]){
			s1.push(x);
			cur[x]=edges[i].next;
			s1.push(edges[i].v);
			edges[i].tag=1;
			finish=0;
			break;
		}
		else if(in[edges[i].v])low[x]=MIN(low[x],dfn[edges[i].v]);
		if(finish)
		{
			for(int i(point[x]);i;i=edges[i].next)
				if(edges[i].tag)
					low[x]=MIN(low[x],low[edges[i].v]);
			if(low[x]==dfn[x])
			{
				int t;cnt++;
				do
				{
					in[t=s2.front()]=0;
					scc[t]=cnt;
				}while(t!=x);
			}
		}
	}
}
