#include<cstdio>

bool test(char* ABD[8])
{
    for(int i=0; i<8; i++)
        for(int j=0; j<i; j++)
        {
            int dist=0;
            
            for(int k=0; k<4; k++)
                if( ABD[i][k]!='*' && ABD[j][k]!='*' && ABD[i][k]!=ABD[j][k] )
                    dist++;
            
            if( dist<1 )
                return false;
        }
    
    return true;
}

int main()
{
    char s[4][8][5];
    char* ABD[8];
    
    for(int i=0; i<4; i++)
        for(int j=0; j<8; j++)
        {
            for(int l=0, k=0; k<4; k++)
            {
                if( k==i )
                    s[i][j][k]='*';
                else
                    s[i][j][k]=j&(1<<l++) ? '1' : '0';
            }
            
            s[i][j][4]=0;
        }
    
    int cnt=0;
    
    for(int i[4]={0}; i[0]<8; i[0]++)
    for(int j[4]={0}; j[0]<i[0]; j[0]++)
        for(i[1]=0; i[1]<8; i[1]++)
        for(j[1]=0; j[1]<i[1]; j[1]++)
            for(i[2]=0; i[2]<8; i[2]++)
            for(j[2]=0; j[2]<i[2]; j[2]++)
                for(i[3]=0; i[3]<8; i[3]++)
                for(j[3]=0; j[3]<i[3]; j[3]++)
                {
                    for(int k=0; k<4; k++)
                    {
                        ABD[k  ]=s[k][ i[k] ];
                        ABD[k+4]=s[k][ j[k] ];
                    }
                    
                    if( test(ABD) )
                    {
                        for(int k=0; k<8; k++)
                            printf("%s\n", ABD[k]);
                        
                        cnt++;
                        printf("\n");
                    }
                }
    
    printf("%d\n", cnt);
}