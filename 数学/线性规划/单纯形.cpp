 inline void pivot(int l,int e){
	for(int i(0);i<=m;i++)
		if(i!=e)
			a[l][i]/=a[l][e];
	a[l][e]=1/a[l][e];
	for(int i(0);i<=n;i++)
		if(l!=i){
			if(!dcmp(a[i][e]))continue;
			for(int j(0);j<=m;j++)
				if(j!=e)
					a[i][j]-=a[i][e]*a[l][j];
			a[i][e]*=-a[l][e];
		}
}
inline int simplex(){
	for(;;){
		int l=1,e=1;
		for(int i(1);i<=n;i++)if(a[i][0]<a[l][0])l=i;
		if(dcmp(a[l][0])>=0)break;
		for(int i(1);i<=m;i++)if(a[l][i]<a[l][e])e=i;
		if(dcmp(a[l][e])>=0)return -1;
		pivot(l,e);
	}
	for(;;){
		int l=1,e=1;
		for(int i(1);i<=m;i++)if(a[0][i]>a[0][e])e=i;
		if(dcmp(a[0][e])<=0)return -a[0][0];
		for(int i(1);i<=n;i++)
			if(dcmp(a[i][e])>0&&(dcmp(a[l][e])<=0||a[i][0]*a[l][e]<a[l][0]*a[i][e]))
				l=i;
		if(dcmp(a[l][e])<=0)return -1;
		pivot(l,e);
	}
}
//标准型
//a[n][m]n个约束,m个变量,a[0]表示目标函数a[i][0]表示常数,每个约束都是<=0,自带非负约束,最大化目标函数
//pivot是转轴操作,simplex第一个for是初始化,能不加就不加!