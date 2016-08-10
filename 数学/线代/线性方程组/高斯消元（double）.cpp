inline void gauss()
{
	for(int i(0);i<n;i++)
	{
		int r(i);
		for(int j(i+1);j<n;j++)
			if(abs(x[j][i])>abs(x[r][i]))
				r=j;
		if(r!=i)
			for(int j(0);j<=n;j++)
				swap(x[i][j],x[r][j]);
		for(int j(n);j>=i;j--)
			for(int k(i+1);k<n;k++)
				x[k][j]-=x[k][i]/x[i][i]*x[i][j];
	}
	for(int i(n-1);i>=0;i--)
	{
		for(int j(i+1);j<n;j++)
			x[i][n]-=x[j][n]*x[i][j];
		x[i][n]/=x[i][i];
	}
    for(int i=0;i<n-1;i++)  
    	printf("%.3lf ",(double)x[i][n]);
    printf("%.3lf",(double)x[n-1][n]);  
}
