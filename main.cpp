#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include"init.h"
#include"IF.h"
#include"ID.h"
#include"EX.h"
#include"MEM.h"
#include"WB.h"
using namespace std;
void nextstep()
{
/*    IF::pro();x[0]=0;
    ID::pro();x[0]=0;
    EX::pro();x[0]=0;
    MEM::pro();x[0]=0;
    WB::pro();x[0]=0;*/
    WB::pro();x[0]=0;
    MEM::pro();x[0]=0;
    EX::pro();x[0]=0;
    ID::pro();x[0]=0;
    IF::pro();x[0]=0;
}
void pro()
{
    int tmp=0;
    while(1)
    {
  /*      tmp++;
        if(tmp<=100) {
            printf("%d %d\n",pc,IF::ext(pc));
        }*/
        if(s[4].exe==fintag&&s[4].exist)
        {
            printf("%u\n",x[10]&255u);

 /*           for (int i = 0; i < 32; i++)
                printf("%d ", x[i]);
            printf("%d\n",tmp);*/
            return;
        }
//			debug();
        nextstep();
  /*      if(tmp<=100){
            s[1].prt();s[2].prt();s[3].prt();s[4].prt();
            for (int i = 0; i < 32; i++)
                printf("%d ", x[i]);
            printf(" %d\n",tmp);
        }*/
//			for(int i=0;i<32;i++)
//				printf("%d ",x[i]);printf("\n");
    }
}
int main() {
    freopen("try.in","r",stdin);
    Init::pro();
    pro();
    return 0;
}