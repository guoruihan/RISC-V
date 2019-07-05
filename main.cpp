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
    while(1)
    {
        if(IF::ext(pc)==fintag)
        {
            printf("%u\n",x[10]&255u);
            return;
        }
//			debug();
        nextstep();
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