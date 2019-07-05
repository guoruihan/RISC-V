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
    IF::pro();x[0]=0;
    ID::pro();x[0]=0;
    EX::pro();x[0]=0;
    MEM::pro();x[0]=0;
    WB::pro();x[0]=0;
}
void pro()
{
    int tmp=0;
    while(1)
    {
        if(IF::ext(pc)==fintag)
        {
            printf("%u\n",x[10]&255u);
            return;
        }
//			debug();
        nextstep();
        tmp++;
 /*       if(tmp<=100)
            printf("%d %d %d\n",pc,IF::ext(pc),st[4464]);
        if(tmp<=100) {
            for (int i = 0; i < 32; i++)
                printf("%d ", x[i]);
            printf(" %d\n",tmp);
        }
        else
            return;*/
//			for(int i=0;i<32;i++)
//				printf("%d ",x[i]);printf("\n");
    }
}
int main() {
    Init::pro();
    pro();
    return 0;
}