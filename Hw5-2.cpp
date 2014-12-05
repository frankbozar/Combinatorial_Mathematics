#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
const int n=10;

int main()
{
    vector<vector<int> > e(n, vector<int>(n, 0x3FFFFFFF));
    e[0][1]=e[1][0]=1;
    e[0][3]=e[3][0]=1;
    e[0][8]=e[8][0]=1;
    e[1][2]=e[2][1]=1;
    e[3][4]=e[4][3]=1;
    e[3][7]=e[7][3]=1;
    e[8][9]=e[9][8]=1;
    e[4][5]=e[5][4]=1;
    e[4][6]=e[6][4]=1;
    e[1][8]=e[8][1]=1;
    e[2][3]=e[3][2]=1;
    e[2][4]=e[4][2]=1;
    e[7][9]=e[9][7]=1;
    e[5][6]=e[6][5]=1;
    e[6][9]=e[9][6]=1;
    
    for(int i=0; i<n; i++)
        e[i][i]=0;
    
    vector<int> d(n, 0), p(n, -1);
    vector<bool> enqueued(n, false);
    enqueued[0]=true;
    queue<int> Q;
    
    for(Q.push(0); !Q.empty(); Q.pop())
    {
        int i=Q.front();
        
        for(int j=0; j<n; j++)
            if( e[i][j]==1 && !enqueued[j] )
            {
                Q.push(j);
                enqueued[j]=true;
                p[j]=i;
                d[j]=d[i]+1;
            }
    }
    
    vector<vector<int> > t(n, vector<int>(n));
    
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            t[i][j]=0;
            
            for(int x=i, y=j; x!=y; )
            {
                if( d[x]>d[y] )
                {
                    x=p[x];
                    t[i][j]++;
                }
                else if( d[x]<d[y] )
                {
                    y=p[y];
                    t[i][j]++;
                }
                else
                {
                    x=p[x];
                    y=p[y];
                    t[i][j]+=2;
                }
            }
        }
    }
    
    for(int k=0; k<n; k++)
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
                if( e[i][j]>e[i][k]+e[k][j] )
                    e[i][j]=e[i][k]+e[k][j];
    
    vector<vector<int> > c(n, vector<int>(n));
    
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            c[i][j]=t[i][j]-e[i][j];
    
    char s[n][n+1];
    
    for(int i=0; i<n; i++)
        for(int j=0; j<=n; j++)
            s[i][j]=0;
    
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
        {
            for(int x=i; x>=0; x=p[x])
                if( x==j )
                    s[i][j]='1';
            
            if( s[i][j]!=0 )
                continue;
            
            int diff=c[i][j]-c[i][ p[j] ];
            
            if( diff==2 || ( diff==1 && ( (i<j && !(c[i][j]&1)) || (i>j && (c[i][j]&1))) ) )
                s[i][j]='*';
            else
                s[i][j]='0';
        }
    
    for(int i=0; i<n; i++)
        printf("%d: %s\n", i, &s[i][1]);
    
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            int l=0;
            
            for(int k=1; k<n; k++)
                if( s[i][k]!='*' && s[j][k]!='*' && s[i][k]!=s[j][k] )
                    l++;
            
            if( l!=e[i][j] )
                printf("%d %d\n", i, j);
        }
    }
}