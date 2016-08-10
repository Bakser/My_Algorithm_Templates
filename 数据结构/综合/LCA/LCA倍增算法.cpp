inline void dfs(int u){
    vis[u]=1;
    for(int i(1);i<=D;i++){//Ô¤´¦Àí 
        f[u][i]=f[f[u][i-1]][i-1];
        val[u][i]=MAX(val[u][i-1],val[f[u][i-1]][i-1]);
    }
    for(int i(point[u]);i;i=edges[i].next)
    if(!vis[edges[i].v]){
        int v(edges[i].v);
        dep[v]=dep[u]+1;
        f[v][0]=u;
        val[v][0]=edges[i].w;
        dfs(v);
    }
}
inline int query(int x,int y){//²éÑ¯ 
    if(dep[x]<dep[y])swap(x,y);
    int res(INT_MIN);
    for(int i(D);i>=0;i--)
        if(dep[f[x][i]]>=dep[y])
            res=MAX(res,val[x][i]),x=f[x][i];
    if(x==y)return res;
    for(int i(D);i>=0;i--)
        if(f[x][i]!=f[y][i])
            res=MAX(res,MAX(val[x][i],val[y][i])),x=f[x][i],y=f[y][i];
    return MAX(res,MAX(val[x][0],val[y][0]));
}

